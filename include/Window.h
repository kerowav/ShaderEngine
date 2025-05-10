#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui-docking/imgui.h>
#include <imgui-docking/imgui_internal.h>
#include <imgui-docking/imgui_impl_glfw.h>
#include <imgui-docking/imgui_impl_opengl3.h>
#include <imgui-docking/TextEditor.h>
#include <imgui-docking/imstb_textedit.h>

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
    GLFWwindow* window = nullptr;
    ShaderProgram shaderProgram;

    bool stayOnTop = false;
    bool fullscreen = false;

    void processInput();
    bool shaderEditorMode = false;
};