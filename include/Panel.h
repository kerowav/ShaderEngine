#pragma once
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui-docking/imgui.h>
#include <filesystem>
#include <fstream>

#include <Shader.h>

class Panel {
public:
    enum PanelType {SHADER_EDITOR, SHADER_LOADER};
    Panel(PanelType pt, ShaderProgram& shaderProgram): 
        type{pt}, 
        mShaderProgram{&shaderProgram} 
    {};
    virtual void RenderPanel() {};
    virtual void UpdateShaderEditorCode() {};
    // virtual void InsertShaderTemplate(); // MOVE INTO PANEL
    inline void coutType() {
        std::cout << type << "\n";
    }
    inline Panel::PanelType GetType() { return type; }
protected:
    PanelType type;
    ShaderProgram* mShaderProgram;
};    

class ShaderLoaderPanel: public Panel {
public:
    ShaderLoaderPanel(PanelType pt, ShaderProgram& shaderProgram): 
        Panel::Panel(pt, shaderProgram)
    {
        mShaderProgram->LoadNewFragmentShader(mShaderProgram->GetShaderSrc().c_str());
    }
    void RenderPanel() override;
};

class ShaderEditorPanel: public Panel {
public:
    ShaderEditorPanel(PanelType pt, ShaderProgram& shaderProgram): 
        Panel::Panel(pt, shaderProgram)
    {
        mShaderProgram->EnterShaderEditorMode();
    }
    void RenderPanel() override;
    void UpdateShaderEditorCode() override;
    // void InsertShaderTemplate() override;
private:
    char textBox[1024 * 16];
    bool liveUpdates = false;
};
            