#define STB_C_LEXER_IMPLEMENTATION
#include <stb/stb_c_lexer.h>

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
        // Define token buffer
        // char token_text_buffer[256];
        // stb_lexer lexer;
        
        // // Initialize lexer
        // stb_c_lexer_init(&lexer,
        //                 textBox, // input
        //                 textBox + IM_ARRAYSIZE(textBox), // end of input
        //                 token_text_buffer,
        //                 sizeof(token_text_buffer));


        // while (true) {
        //     int token = stb_c_lexer_get_token(&lexer);
        //     if (token == CLEX_eof) break;

        //     std::cout << "Token: ";
        //     if (token == CLEX_id) {
        //         std::cout << "Identifier: " << lexer.string << "\n";
        //     } else if (token == CLEX_intlit) {
        //         std::cout << "Integer: " << lexer.int_number << "\n";
        //     } else if (token == CLEX_floatlit) {
        //         std::cout << "Float: " << lexer.real_number << "\n";
        //     } else {
        //         std::cout << "Symbol: '" << lexer.string << "'\n";
        //     }
        // }


        ImGui::Text("{#fff}Row {#f00}%d {#fff}is {#0000ff}%s {#fff}and {#ff880088}orange transparent", 2, "blue");

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
    std::string source;



    for(const auto & entry : std::filesystem::directory_iterator("../assets/frag")) {
        std::string name = entry.path().stem().string();
        
        if(ImGui::Button(name.c_str())) {
            source = "../assets/frag/" + name + ".glsl";
            mShaderProgram->LoadNewFragmentShader(source.c_str());
        }

        if (ImGui::BeginPopupContextItem(name.c_str())) {
            if (ImGui::MenuItem("Delete")) {
                source = "../assets/frag/" + name + ".glsl";
                mFileNameToDelete = entry.path().string();
                popupModal = true;
                std::cout << mFileNameToDelete << "\n";
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

    if (popupModal) ImGui::OpenPopup("popupModal");

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("popupModal")) {

        ImGui::Text(("Are you sure you want to delete: " + mFileNameToDelete + "?\n\n").c_str());
        ImGui::Separator();

        if (ImGui::Button("Yes", ImVec2(120, 0))) {
            std::cout << "Deleting shader: " << mFileNameToDelete << "\n";
            
            std::remove((mFileNameToDelete).c_str());
            ImGui::CloseCurrentPopup();
            mFileNameToDelete = "";
            popupModal = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("No", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
            popupModal = false;
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}