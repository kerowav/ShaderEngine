#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderProgram {
public:
    unsigned int vertexShader;
    const GLchar* vertShader = nullptr;

    unsigned int fragmentShader;
    const GLchar* fragShader = nullptr;
    
    unsigned int shaderProgram;

    unsigned int VAO, VBO, EBO;
    
    int success;
    char infoLog[512];
    ShaderProgram() = default;
    ShaderProgram(const char* src);
    void EnterShaderMakerMode();
    void UseProgram(int, int);
    inline std::string GetShaderName() {
        return shaderName;
    }
    inline std::string GetShaderSrc() {
        return shaderSrc;
    }
    void ReloadShader();
    void LoadNewFragmentShader(const char* src);
    void UpdateShaderMakerBody(std::string body);
private:
    std::string shaderSrc;
    std::string shaderName;
    bool shaderMakerMode = false;
    void CompileFragmentShader(const char* src);
    void LoadShaderMakerMode();
    void CompileShaderMaker();
    std::string shaderMakerBody = "";
    std::string loadShaderSrc(const char* filename);
};