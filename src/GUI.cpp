#include <GUI.h>

GUI& GUI::getInstance() {
    static GUI instance;
    return instance;
}

void GUI::ActivateShaderLoaderMode() {
    mPanel = new ShaderLoaderPanel(Panel::SHADER_LOADER, *mShaderProgram);
    std::cout << "Shader Loader Mode Activated\n";
}

void GUI::ActivateShaderEditorMode(){
    mPanel = new ShaderEditorPanel(Panel::SHADER_EDITOR, *mShaderProgram);
    std::cout << "Shader Editor Mode Activated\n";
}

void GUI::Initialize(ShaderProgram& shaderProgram, Panel::PanelType type) {
    mShaderProgram = &shaderProgram;
    SwitchMode(type);
}

void GUI::SwitchMode(Panel::PanelType type) {
    std::cout << "Switching panel\n";
    if(mPanel != nullptr) {
        std::cout << "Deleting panel.\n";
        delete mPanel;
        mPanel = nullptr;
    }
    switch (type)
    {
    case Panel::SHADER_EDITOR:
        ActivateShaderEditorMode();
        break;
    case Panel::SHADER_LOADER:
        ActivateShaderLoaderMode();
        break;
    default:
        std::cerr << "NO PANEL\n";
        break;
    }
}

void GUI::RenderMainMenu(ShaderProgram& shaderProgram) {
    if (ImGui::BeginMainMenuBar()){
        if (ImGui::BeginMenu("Options")){
            if (ImGui::MenuItem( mShaderEditorModeActive ? "Shader Loader Mode" : "Shader Editor Mode")) {
                
                mShaderEditorModeActive = !mShaderEditorModeActive;
                SwitchMode(Panel::PanelType(mShaderEditorModeActive));

                // shaderProgram.EnterShaderEditorMode();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void GUI::RenderUI(){
    mPanel->RenderPanel();
}