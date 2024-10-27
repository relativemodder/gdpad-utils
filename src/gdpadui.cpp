#include "gdpadui.hpp"
#include "shared.hpp"
#include <imgui.h>


void GDPadUI::centered_title(std::string text, float text_y)
{
    float win_width = GDPadShared::mainFrameSize.x;
    ImGui::PushFont(GDPadShared::fonts["title"]);
    float text_width = ImGui::CalcTextSize(text.c_str()).x;

    float text_indentation = (win_width - text_width) * 0.5f;

    float min_indentation = 20.0f;
    if (text_indentation <= min_indentation) {
        text_indentation = min_indentation;
    }

    ImGui::BeginChild(text.c_str());

    ImGui::SetWindowPos({
        text_indentation + GDPadShared::mainFramePos.x, text_y
    });

    ImGui::TextWrapped("%s", text.c_str());

    ImGui::PopFont();

    ImGui::EndChild();
}


void GDPadUI::draw_centered_image() {
    auto gdpad = GDPadShared::textures["gdpad"];

    ImGui::SetNextWindowPos(
        {
            GDPadShared::windowSize.x / 2 - gdpad->size.x / 2, 
            GDPadShared::windowSize.y / 2 - gdpad->size.y / 2 - 70
        }
    );

    ImGui::BeginChild("gdpad_image", gdpad->size);

    {
        ImGui::Image(
            (ImTextureID)(intptr_t)gdpad->out_texture,
            gdpad->size
        );
    }

    ImGui::EndChild();
}


void GDPadUI::help_marker(const char* desc)
{
    ImGui::SameLine(0 ,0);
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}


void GDPadUI::draw_bottom_ui() {
    ImGui::BeginChild("gdpad_bottom");

    ImGui::SetWindowPos(
        {
            GDPadShared::mainFramePos.x + padding,
            GDPadShared::mainFramePos.y + GDPadShared::mainFrameSize.y - 248.f
        }
    );

    ImGui::SetWindowSize({
        GDPadShared::mainFrameSize.x, 250
    });

    GDPadSettingsUI::draw();
    
    ImGui::EndChild();
}


void GDPadUI::draw_main_window() {
    ImGui::Begin(
        "pizdec", 
        NULL, 
        ImGuiWindowFlags_NoBackground
        | ImGuiWindowFlags_NoDecoration
        | ImGuiWindowFlags_NoMove
    ); 
    {
        ImGui::SetWindowPos({
            (GDPadShared::windowSize.x - GDPadShared::minWindowSize.x + padding) * 0.5f,
            (GDPadShared::windowSize.y - GDPadShared::minWindowSize.y + padding) * 0.5f
        });

        ImGui::SetWindowSize(
            {
                GDPadShared::minWindowSize.x - padding, 
                GDPadShared::minWindowSize.y - padding
            }
        );

        GDPadShared::mainFramePos = ImGui::GetWindowPos();
        GDPadShared::mainFrameSize = ImGui::GetWindowSize();

        centered_title(
            fmt::format("{}  Настройки GDPad", ICON_FA_GEARS), 
            GDPadShared::mainFramePos.y + 25
        );
        draw_centered_image();
        draw_bottom_ui();
    }
    ImGui::End();

    // ImGui::ShowDemoWindow();
}


void GDPadUI::set_style() {
    auto colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_FrameBg]                = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.58f, 0.58f, 0.58f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.67f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.67f, 0.67f, 0.67f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.37f, 0.37f, 0.37f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.4f, 0.4f, 0.4f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.5f, 0.5f, 0.5f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.55f, 0.55f, 0.55f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.67f, 0.67f, 0.67f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.45f, 0.45f, 0.45f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.58f, 0.58f, 0.58f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.55f, 0.55f, 0.55f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.43f, 0.44f, 0.44f, 0.95f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.50f, 0.50f, 0.50f, 0.80f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.22f, 0.22f, 0.22f, 0.86f);
    colors[ImGuiCol_TabSelected]            = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
    colors[ImGuiCol_TabSelectedOverline]    = ImVec4(0.81f, 0.81f, 0.81f, 1.00f);
    colors[ImGuiCol_TabDimmed]              = ImVec4(0.12f, 0.12f, 0.12f, 0.97f);
    colors[ImGuiCol_TabDimmedSelected]      = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);

    auto style = ImGui::GetStyle();
    style.FrameRounding = 5;
};