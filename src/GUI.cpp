#include "GUI.h"

GUI& GUI::getInstance() {
    static GUI instance;
    return instance;
}

void GUI::ActivateShaderLoaderMode() {
    mPanel = new ShaderLoaderPanel(Panel::SHADER_LOADER, *mShaderProgram);
    std::cout << "Shader Loader Mode Activated\n";
}

void GUI::ActivateShaderEditorMode(bool openingFile){
    mPanel = new ShaderEditorPanel(Panel::SHADER_EDITOR, *mShaderProgram, openingFile);
    std::cout << "Shader Editor Mode Activated";
}

void GUI::Initialize(ShaderProgram& shaderProgram, Panel::PanelType type) {
    mShaderProgram = &shaderProgram;
    SwitchMode(type, false);
}

void GUI::SwitchMode(Panel::PanelType type, bool openingFile) {
    std::cout << "Switching panel\n";
    if(mPanel != nullptr) {
        std::cout << "Deleting panel.\n";
        delete mPanel;
        mPanel = nullptr;
    }
    switch (type)
    {
    case Panel::SHADER_EDITOR:
        ActivateShaderEditorMode(openingFile);
        break;
    case Panel::SHADER_LOADER:
        ActivateShaderLoaderMode();
        break;
    default:
        std::cerr << "NO PANEL\n";
        break;
    }
}

void GUI::OpenFileInShaderEditor(std::string name, std::string filePath) {
    SwitchMode(Panel::SHADER_EDITOR, true);
    mShaderProgram->OpenShaderInEditor(name, "../assets/frag/" + name + ".glsl");
    mPanel->UpdateName(name);
    mPanel->LoadShaderEditorCode();
}

void GUI::RenderMainMenu(ShaderProgram& shaderProgram) {
    if (ImGui::BeginMainMenuBar()){
        if (ImGui::BeginMenu("Options")){
            if(mPanel->GetType() != Panel::SHADER_EDITOR)
                if (ImGui::MenuItem("Shader Editor")) {
                    SwitchMode(Panel::SHADER_EDITOR, false);
                }
                
            if(mPanel->GetType() != Panel::SHADER_LOADER)
                if (ImGui::MenuItem("Shader Loader")) {
                    SwitchMode(Panel::SHADER_LOADER, false);
                }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void GUI::RenderUI(){
    mPanel->RenderPanel();
}