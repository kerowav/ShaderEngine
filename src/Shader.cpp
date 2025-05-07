#include <iostream>
#include <fstream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

ShaderProgram::ShaderProgram(const char* src)  : 
    vertexShader{ glCreateShader(GL_VERTEX_SHADER) },
    fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) },
    shaderProgram{ glCreateProgram() }  
{   
    shaderSrc = src;
    std::cout << "New ShaderProgram - source: " << src << "\n";

    // Compile Vertex Shader
    std::string vertexShaderSrc = loadShaderSrc("../assets/vertex_core2.glsl");
    vertShader = vertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);

    // Catch Error
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error with vertex shader compilation.\n" << infoLog << "\n";
    }

    CompileFragmentShader(src);

    // Compile Shader Program
    glAttachShader(shaderProgram, vertexShader);
    
    glLinkProgram(shaderProgram);

    // Catch Error
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "Error with shader program linking.\n" << infoLog << "\n";
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);

    float vertices[] = {
        -1.0f, -1.0f, 0.0f, // bottom left
        1.0f, -1.0f, 0.0f, // top left
        -1.0f, 1.0f, 0.0f, // bottom right
        1.0f, 1.0f, 0.00f, // top right
      };
  
    unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3, 
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void ShaderProgram::UseProgram(int width, int height) {
    glUseProgram(shaderProgram);

    float timeValue = glfwGetTime();

    float shaderTimeValue = glGetUniformLocation(shaderProgram, "inTime");
    glUniform1f(shaderTimeValue, timeValue);
    
    int shaderResolutionLocation = glGetUniformLocation(shaderProgram, "iResolution");
    glUniform2f(shaderResolutionLocation, width, height);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void ShaderProgram::ReloadShader(){
    if(shaderMakerMode) {
        LoadShaderEditorMode();
    }
    else {
        CompileFragmentShader(shaderSrc.c_str());
    }
}

void ShaderProgram::EnterShaderEditorMode(){
    std::cout << "Shader maker mode initialized.\n";
    shaderMakerMode = true;
    ReloadShader();
}

void ShaderProgram::InsertShaderTemplate() {
    std::string templateSrc = loadShaderSrc("../assets/Frag_Template.glsl");
    shaderEditorCode = templateSrc.c_str();
    ReloadShader();
    // shaderEditorCode = (shaderMakerHeader + shaderEditorCode).c_str();
}

void ShaderProgram::LoadShaderEditorMode(){
    CompileShaderEditorCode();
    
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error with shader program linking after fragment shader change.\n" << infoLog << "\n";
    }
    
    glDetachShader(shaderProgram, fragmentShader);
}

void ShaderProgram::CompileShaderEditorCode(){
    std::cout << "Compiling shader maker.\n";

    fragShader = shaderEditorCode;

    glShaderSource(fragmentShader, 1, &fragShader, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "Error with fragment shader compilation.\n" << infoLog << "\n";
    }

    glAttachShader(shaderProgram, fragmentShader);
}

void ShaderProgram::UpdateShaderEditorCode(const char* code){
    shaderEditorCode = code;
    ReloadShader();
}

void ShaderProgram::LoadNewFragmentShader(const char* src) {
    std::cout << "Changing shader: " << src << "\n";
    
    CompileFragmentShader(src);
    
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error with shader program linking after fragment shader change.\n" << infoLog << "\n";
    }
    
    glDetachShader(shaderProgram, fragmentShader);
    
}

void ShaderProgram::CompileFragmentShader(const char* src) {
    shaderSrc = src;
    std::string source_string = src;
    std::string base_filename = source_string.substr(source_string.find_last_of("/\\") + 1);
    std::string::size_type const p(base_filename.find_last_of('.'));
    shaderName = base_filename.substr(0, p);


    std::string fragShaderSrc = loadShaderSrc(src);
    fragShader = fragShaderSrc.c_str();

    glShaderSource(fragmentShader, 1, &fragShader, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "Error with fragment shader compilation.\n" << infoLog << "\n";
    }

    glAttachShader(shaderProgram, fragmentShader);
}

std::string ShaderProgram::loadShaderSrc(const char* filename) {
    std::ifstream file;
    std::stringstream buf;
    
    std::string ret = "";

    file.open(filename);
    if (file.is_open()) {
        buf << file.rdbuf();
        ret = buf.str();
    } else {
        std::cout << "could not open " << filename << "\n";
    }
    file.close();

    return ret;
}
