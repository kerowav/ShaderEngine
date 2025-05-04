cmake_minimum_required(VERSION 3.26.0)
project(ShaderEngine VERSION 1.0.0)
# cmake_policy(SET CMP0072 NEW)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)

set(IMGUI_DIR dependencies/imgui-docking)
add_library(ImGui STATIC
    dependencies/imgui-docking/imgui.cpp
    dependencies/imgui-docking/imgui_draw.cpp
    dependencies/imgui-docking/imgui_widgets.cpp
    dependencies/imgui-docking/imgui_tables.cpp
    dependencies/imgui-docking/imgui_impl_glfw.cpp
    dependencies/imgui-docking/imgui_impl_opengl3.cpp
)
target_include_directories(ImGui PUBLIC dependencies/imgui-docking)

add_executable(ShaderEngine src/main.cpp lib/glad.c lib/stb.cpp src/Window.cpp src/Shader.cpp)

add_library(Includes STATIC src/Window.cpp src/Shader.cpp)
target_include_directories(Includes PRIVATE dependencies include )

target_include_directories(ShaderEngine PRIVATE dependencies include  )

target_link_libraries(ShaderEngine ImGui GLFW3 OpenGL::GL Includes)