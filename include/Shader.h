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
    void EnterShaderEditorMode();
    void EnterShaderLoaderMode();
    inline std::string GetErrorMessage() { return errorMessage; };
    void UseProgram(int, int);
    inline std::string GetShaderName() {
        return shaderName;
    }
    inline std::string GetShaderSrc() {
        return shaderSrc;
    }
    void ReloadShader();
    void LoadNewFragmentShader(const char* src);
    void UpdateShaderEditorCode(const char* code);
    void InsertShaderTemplate();
    void OpenShaderInEditor(std::string name, std::string src);
    inline std::string GetShaderEditorCode() { return shaderEditorCode; }
    inline std::string GetShaderEditorName() { return shaderEditorName; }
    inline void SetShaderEditorName(std::string name) { shaderEditorName = name; }
private:
    std::string shaderSrc;
    std::string shaderName = "";
    std::string shaderEditorCode = "";
    std::string shaderEditorName = "";
    bool fragShaderCompileError = false;
    std::string errorMessage = "Error";
    bool shaderEditorMode = false;
    void CompileFragmentShader(const char* src);
    void LoadShaderEditorMode();
    void CompileShaderEditorCode();
    // const char* shaderEditorCode = "";  
};

std::string loadShaderSrc(const char* filename);