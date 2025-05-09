#include <iostream>
#include <cmath>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

int main() {
    std::cout << "RudeRacoon @_@\n"; 
    
    Window& window{Window::getInstance()};
    window.Initialize();

    window.Run();
    return 0;
}
