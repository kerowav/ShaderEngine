#pragma once
#include <iostream>

#include "Panel.h"
#include "Shader.h"

class Panel;

class GUI {
public:
    static GUI& getInstance();
    GUI() = default;
    void RenderMainMenu(ShaderProgram&);
    void Initialize(ShaderProgram&, Panel::PanelType type);
    void RenderUI();
    inline Panel::PanelType getPanelType() {
        return mPanel->GetType();
    }
    inline void UpdateShaderEditorCode() {
        if (mPanel->GetType() == Panel::SHADER_EDITOR) {
            std::cout << "Updating code\n";
            mPanel->UpdateShaderEditorCode();
        }
    }
    inline void ReloadShader() { mShaderProgram->ReloadShader(); }
private:
    GUI* mGui = nullptr;
    Panel* mPanel = nullptr;
    ShaderProgram* mShaderProgram = nullptr;
    void ActivateShaderLoaderMode();
    void ActivateShaderEditorMode();
    void SwitchMode(Panel::PanelType);
};

