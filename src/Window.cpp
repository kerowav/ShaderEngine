#include "Window.h"
#include "Shader.h"

#include <filesystem>
#include <string>

class Window;
void framebuffer_size_callback(GLFWwindow*, int, int);

Window& Window::getInstance() {
    static Window instance;
    return instance;
}

void Window::Initialize() {
    glfwInit(); 
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n";
        return;
    }

    window = glfwCreateWindow(
        width, height,
        "ShaderEngine",
        NULL,
        NULL );
    
    if (window == NULL) {
        std::cout << "Failed to open GLFW window\n";
        return;
    }
    
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return;
    }

    // USE BOOLEAN
    glfwSetWindowAttrib(window, GLFW_FLOATING, stayOnTop);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    shaderProgram = ShaderProgram("../assets/frag/fragment_core1.glsl");
}



/* TABLE OF USER VARIABLES


VARIABLE TYPE - USER MADE VARIABLE NAME -  VARIABLE VALUE         -> Output

vec4            my_color                  [0.0, 0.0, 0.0, 0.0]    -> "vec4 my_color = vec4(0.0, 0.0, 0.0, 0.0);\n"
float           distance                  my_color                -> "float distance = length(my_color);\n"


*/



void Window::Run() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool showPopout = true;

    while(!glfwWindowShouldClose(window)) {
        processInput();

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        width = w;
        height = h;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (ImGui::BeginMainMenuBar()){
            if (ImGui::BeginMenu("Options")){
                if (ImGui::MenuItem( shaderEditorMode ? "Shader Loader Mode" : "Shader Editor Mode")) {
                    shaderEditorMode = !shaderEditorMode;
                    shaderProgram.EnterShaderEditorMode();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (!shaderEditorMode) ShaderLoaderPanel();
        if (shaderEditorMode) ShaderEditorPanel();
        shaderProgram.UseProgram(width, height);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::ShaderLoaderPanel() {
    ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_FirstUseEver); // Optional: Set initial position
    ImGui::Begin("Shader Loader");

    std::string shaderName = shaderProgram.GetShaderName();
    ImGui::Text(("Curent Shader: " + shaderName).c_str());

    for(const auto & entry : std::filesystem::directory_iterator("../assets/frag")) {
        std::string name = entry.path().stem().string();
        if(ImGui::Button(name.c_str())) {
            ChangeShader(("../assets/frag/" + name + ".glsl").c_str());
        };
    }
    ImGui::Text("Completed");
    for(const auto & entry : std::filesystem::directory_iterator("../assets/complete")) {
        std::string name = entry.path().stem().string();
        if(ImGui::Button(name.c_str())) {
            ChangeShader(("../assets/complete/" + name + ".glsl").c_str());
        };
    }

    ImGui::Text("Imported");
    for(const auto & entry : std::filesystem::directory_iterator("../assets/import")) {
        std::string name = entry.path().stem().string();
        if(ImGui::Button(name.c_str())) {
            ChangeShader(("../assets/import/" + name + ".glsl").c_str());
        };
    }

    ImGui::End();
}

bool popoutMode = false;

std::string vecToString(float vec[4], int size){
    std::string stringify;
    for(int i = 0; i < 4; i++) {
        if(i == size - 1) stringify += std::to_string(i);
        else stringify += std::to_string(vec[i]) + ",";
    }
    
    stringify = "vec" + std::to_string(size) + "(" + stringify + ")";
    std::cout << "Stringify: " << stringify << "\n";
    return stringify;
}

void Window::ShaderEditorPanel() {
    static float my_color[4] = {0.0f, 0.0f, 0.0f, 1.0f}; // Default color (red with full opacity)
    ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_FirstUseEver); // Optional: Set initial position
    std::string body[128];
    char textBox[1024 * 16];
    ImGui::Begin("Shader Editor", &popoutMode, ImGuiWindowFlags_MenuBar);
    bool valuesChanged = false;

    if(ImGui::BeginMenuBar()) {
        if(ImGui::BeginMenu("Add")) {
            if(ImGui::MenuItem("Generic Header")) {
                std::cout << "Adding generic header\n";
                shaderProgram.InsertShaderHeader();
                strncpy(textBox, shaderProgram.GetShaderEditorCode().c_str(), sizeof(textBox) - 1);
                textBox[sizeof(textBox) - 1] = '\0';
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    static char shaderName[128] = "";
    if(ImGui::InputText("Name", shaderName, IM_ARRAYSIZE(shaderName))){
        std::cout << shaderName << "\n";
        valuesChanged = true;
    };
    
    if(ImGui::InputTextMultiline("##code", textBox, IM_ARRAYSIZE(textBox), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_AllowTabInput)){
        valuesChanged = true;
    };

    if (valuesChanged){
        // shaderProgram.UpdateShaderMakerBody(body);
        shaderProgram.UpdateShaderEditorCode(textBox);
        std::cout << textBox << "\n";
    }

    ImGui::End();
}

GLFWwindow* Window::getWindow(){
    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (!reloadShaderKeyPressed) ReloadShader();
        reloadShaderKeyPressed = true;       
    }
    else reloadShaderKeyPressed = false;

    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        if(!fullscreenKeyPressed) fullscreen = !fullscreen;
        fullscreenKeyPressed = true;
        std::cout << "Fullscreen: " << fullscreen << "\n";
    }
    else fullscreenKeyPressed = false;
}

void Window::ChangeShader(const char* src) {
    shaderProgram.LoadNewFragmentShader(src);
}

void Window::ReloadShader() {
    shaderProgram.ReloadShader();
}