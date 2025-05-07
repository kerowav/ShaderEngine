#include "Window.h"
#include "Shader.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "GUI.h"

class Window;
void framebuffer_size_callback(GLFWwindow*, int, int);

Window& Window::getInstance() {
    static Window instance;
    return instance;
}

GLFWwindow* Window::getWindow(){
    return window;
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
    GUI::getInstance().Initialize(shaderProgram, Panel::SHADER_LOADER);
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

        GUI::getInstance().RenderMainMenu(shaderProgram);

        GUI::getInstance().RenderUI();
        // if (shaderEditorMode) ShaderEditorPanel();
        
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

class Keybinds {
public:
    inline static bool reloadShaders = false;
    inline static bool reloadShaderEditor = false;
    inline static bool fullscreen = false;
    inline static bool rightclick = false;
};

void Window::processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetMouseButton(window, ImGuiMouseButton_Right) == GLFW_PRESS){
        if(!Keybinds::rightclick) {
            std::cout << "Right click!\n";
            Keybinds::rightclick = true;
        }
    }
    else Keybinds::rightclick = false;

    if(shaderEditorMode) {
        //SHADER EDITOR SPECIFIC
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            if (!Keybinds::reloadShaderEditor) {
                // GUI::getInstance().UpdateShaderEditorCode(textBox);
                GUI::getInstance().UpdateShaderEditorCode();
                Keybinds::reloadShaderEditor = true;
                std::cout << "Saving and Reloading shader program.\n";
            }
        }
        else Keybinds::reloadShaderEditor = false;

        //OTHER
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            if (!Keybinds::reloadShaders) {
                GUI::getInstance().ReloadShader();
                Keybinds::reloadShaders = true;     
                std::cout << "Reloading shaders.\n";  
            }
        }
        else Keybinds::reloadShaders = false;
    
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            if(!Keybinds::fullscreen) {
                fullscreen = !fullscreen;
                Keybinds::fullscreen = true;
                std::cout << "Fullscreen: " << fullscreen << "\n";
            }
        }
        else Keybinds::fullscreen = false;
    }
    else {
        //OTHER
        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            if (!Keybinds::reloadShaderEditor) {
                GUI::getInstance().ReloadShader();
                std::cout << "Reloading shaders.\n";
                Keybinds::reloadShaderEditor = true;
            }
        }
        else Keybinds::reloadShaderEditor = false;
    
        if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            if(!Keybinds::fullscreen) {
                fullscreen = !fullscreen;
                Keybinds::fullscreen = true;
                std::cout << "Fullscreen: " << fullscreen << "\n";
            }
            
        }
        else Keybinds::fullscreen = false;
    }


}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
