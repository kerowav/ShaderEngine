#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui-docking/imgui.h>
#include <imgui-docking/imgui_impl_glfw.h>
#include <imgui-docking/imgui_impl_opengl3.h>

#include "Shader.h"

class Window {
public:
    static Window& getInstance();
    Window() = default;
    int width = 960, height = 540;
    void Initialize();
    void Run();
    GLFWwindow* getWindow();
private:
    void ChangeShader(const char* src);
    void ReloadShader();
    GLFWwindow* window = nullptr;
    ShaderProgram shaderProgram;
    bool stayOnTop = true;
    bool fullscreen = false;
    bool fullscreenKeyPressed = false;
    bool reloadShaderKeyPressed = false;
    void processInput();
    void ShaderLoaderPanel();
    void ShaderEditorPanel();
    bool shaderEditorMode = false;
};