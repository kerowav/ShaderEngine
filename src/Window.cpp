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
                if (ImGui::MenuItem( shaderMakerMode ? "Shader Loader Mode" : "Shader Maker Mode")) {
                    shaderMakerMode = !shaderMakerMode;
                    shaderProgram.EnterShaderMakerMode();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (!shaderMakerMode) ShaderLoaderPanel();
        if (shaderMakerMode) ShaderMakerPanel();
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

void Window::ShaderMakerPanel() {
    static float my_color[4] = {0.0f, 0.0f, 0.0f, 1.0f}; // Default color (red with full opacity)
    ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_FirstUseEver); // Optional: Set initial position
    std::string body = "";
    ImGui::Begin("Shader Maker", &popoutMode, ImGuiWindowFlags_NoDocking);
    bool bodyChanged = false;

    static char shaderName[128] = "";
    if(ImGui::InputText("Name", shaderName, IM_ARRAYSIZE(shaderName))){
        std::cout << shaderName << "\n";
        bodyChanged = true;
    };

    if(ImGui::ColorEdit4("Color", my_color)){
        bodyChanged = true;
    }

    static bool dist = false;
    if (ImGui::Checkbox("Distance", &dist)){
        bodyChanged = true;

    } 

    if (bodyChanged){
        body += "vec4 my_color = " + vecToString(my_color, 4) + ";\n";
        if(dist) body += "my_color.r = length(uv);\n";
        body += 
            "FragColor = my_color;\n"
            
            ;
        shaderProgram.UpdateShaderMakerBody(body);

        std::cout << body;
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