#pragma once
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui-docking/imgui.h>
#include <filesystem>
#include <fstream>
#include <stdio.h>

#include "Shader.h"

class Panel {
public:
    enum PanelType {SHADER_EDITOR, SHADER_LOADER};
    Panel(PanelType pt, ShaderProgram& shaderProgram): 
        type{pt}, 
        mShaderProgram{&shaderProgram} 
    {};
    virtual void RenderPanel() {};
    virtual void UpdateShaderEditorCode() {};
    virtual void LoadShaderEditorCode() {};
    // virtual void InsertShaderTemplate(); // MOVE INTO PANEL
    inline void coutType() {
        std::cout << type << "\n";
    }
    inline Panel::PanelType GetType() { return type; }
    inline void UpdateName(std::string name) { 
        strcpy(shaderName, name.c_str());
        mShaderProgram->SetShaderEditorName(name);
    }
protected:
    char shaderName[128] = "";
    PanelType type;
    ShaderProgram* mShaderProgram;
};    

class ShaderLoaderPanel: public Panel {
public:
    ShaderLoaderPanel(PanelType pt, ShaderProgram& shaderProgram): 
        Panel::Panel(pt, shaderProgram)
    {
        mShaderProgram->LoadNewFragmentShader(mShaderProgram->GetShaderSrc().c_str());
        mShaderProgram->EnterShaderLoaderMode();
    }
    void RenderPanel() override;
private: 
    std::string mFileNameToDelete;
};

class ShaderEditorPanel: public Panel {
public:
    ShaderEditorPanel(PanelType pt, ShaderProgram& shaderProgram, bool openingFile): 
        Panel::Panel(pt, shaderProgram)
    {
        
        std::cout << "Shader editor name: " << mShaderProgram->GetShaderEditorName().c_str() << "\n";
        strcpy(shaderName, mShaderProgram->GetShaderEditorName().c_str());
        strcpy(textBox, mShaderProgram->GetShaderEditorCode().c_str());
        mShaderProgram->EnterShaderEditorMode();
    }
    void RenderPanel() override;
    void UpdateShaderEditorCode() override;
    void LoadShaderEditorCode() override;
private:
    char textBox[1024 * 16];
    char errorMessage[1024 * 16];
    bool liveUpdates = false;
};
            