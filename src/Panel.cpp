#include "GUI.h"
#include "Panel.h"

// SHADER EDITOR PANEL
void ShaderEditorPanel::RenderPanel(){
    static float my_color[4] = {0.0f, 0.0f, 0.0f, 1.0f}; // Default color (red with full opacity)
    ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_FirstUseEver); // Optional: Set initial position

    ImGui::Begin("Shader Editor", nullptr, ImGuiWindowFlags_MenuBar);
    bool valuesChanged = false;

    if(ImGui::BeginMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("Load")) {

            }

            if(ImGui::MenuItem("Save")) {
                std::string name = shaderName;
                if(name != "") {
                    std::string shaderFileName = name + ".glsl";
                    std::cout << shaderFileName << "\n";
                    std::filesystem::path filePath = "../assets/frag/" + shaderFileName;

                    std::ofstream outputFile;
                    outputFile.open(filePath);

                    if (outputFile.is_open()) {
                        std::string code = textBox;
                        std::cout << code << "\n"; 
                        outputFile << code << "\n"; 
                        outputFile.close();
                        std::cout << "File saved: " << filePath << "\n";
                    } else {
                        std::cerr << "Error saving file";
                    }
                }
            }

            if(ImGui::BeginMenu("Options")){
                std::string updateStatus = (liveUpdates ? "ON" : "OFF");
                if(ImGui::MenuItem(("Live Update: " + updateStatus).c_str())){
                    liveUpdates = !liveUpdates;
                    std::cout << "Live Update toggled: " << updateStatus << "\n";
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Add")) {
            if(ImGui::MenuItem("Template")) {
                std::cout << "Adding Template\n";
                mShaderProgram->InsertShaderTemplate();
                strncpy(textBox, mShaderProgram->GetShaderEditorCode().c_str(), sizeof(textBox) - 1);
                textBox[sizeof(textBox) - 1] = '\0';
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    if(ImGui::InputText("Name", shaderName, IM_ARRAYSIZE(shaderName))){
        std::string name = shaderName;
        for (int i = 0; i < name.length(); i++) {
            // std::cout << name[i] << "\n";
            if(name[i] == ' ') {
                name[i] = '_';
            }
        }
        strcpy(shaderName, name.c_str());
        mShaderProgram->SetShaderEditorName(name);

        std::cout << shaderName << "\n";
        valuesChanged = true;
    };

    if(ImGui::InputTextMultiline("##code", textBox, IM_ARRAYSIZE(textBox), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 24), ImGuiInputTextFlags_AllowTabInput)){
        valuesChanged = true;
        ImVec2 cursor_pos = ImGui::GetCursorPos();
    };

    
    std::string errMsgString = mShaderProgram->GetErrorMessage();
    
    strcpy(errorMessage, errMsgString.c_str());

    ImGui::InputTextMultiline("##errorMsg", errorMessage, IM_ARRAYSIZE(errorMessage),ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 6), ImGuiInputTextFlags_ReadOnly );

    if (valuesChanged){
        if(liveUpdates) mShaderProgram->UpdateShaderEditorCode(textBox);
    }



    ImGui::End();
}

void ShaderEditorPanel::UpdateShaderEditorCode() {
    mShaderProgram->UpdateShaderEditorCode(textBox);
}

void ShaderEditorPanel::LoadShaderEditorCode() {
    strcpy(textBox, mShaderProgram->GetShaderEditorCode().c_str());
}

// SHADER LOADER PANEL
void ShaderLoaderPanel::RenderPanel() {
    ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_FirstUseEver); // Optional: Set initial position
    ImGui::Begin("Shader Loader");

    std::string shaderName = mShaderProgram->GetShaderName();
    ImGui::Text(("Loaded: " + shaderName).c_str());
        ImGui::Separator();
    bool popupModal = false;
    std::string nameToDelete;
    for(const auto & entry : std::filesystem::directory_iterator("../assets/frag")) {
        std::string name = entry.path().stem().string();
        
        if(ImGui::Button(name.c_str())) {
            std::string source = "../assets/frag/" + name + ".glsl";
            mShaderProgram->LoadNewFragmentShader(source.c_str());
        }

        if (ImGui::BeginPopupContextItem(name.c_str())) {
            if (ImGui::MenuItem("Delete")) {
                ImGui::OpenPopup("popupModal");
                nameToDelete = name;
                popupModal = true;
                std::cout << "Delete shader: " << name << "\n";
            }
            if (ImGui::MenuItem("Rename")) {
                std::cout << "Rename shader: " << name << "\n";
            }
            if (ImGui::MenuItem("Open")) {
                GUI::getInstance().OpenFileInShaderEditor(name, "../assets/frag/" + name + ".glsl");
            }
            ImGui::EndPopup();
        }
    }

    // Confirmation dialog Doesn't work!
    if (ImGui::BeginPopupModal("popupModal")) {

        ImGui::Text("Are you sure you want to delete this shader?\n\n");
        ImGui::Separator();

        if (ImGui::Button("Yes", ImVec2(120, 0))) {
            std::cout << "Deleting shader: " << "test" << "\n";
            // Add your delete logic here
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("No", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }

        popupModal = false;
        ImGui::EndPopup();
    }
    ImGui::End();
}