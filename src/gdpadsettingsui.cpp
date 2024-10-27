#include "gdpadui.hpp"
#include <gdpadsettingsui.hpp>


void GDPadSettingsUI::draw() {
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 3);

    if (ImGui::BeginTabBar("##settings_categories")) {
        if (ImGui::BeginTabItem(" База ")) {
            {
                ImGui::Text(" " ICON_FA_BOLT_LIGHTNING "  Частота опроса ");

                GDPadUI::help_marker(
                    fmt::format(
                        "{}\n{}\n\n{}\n{}\n{}", 
                        "   Частота опроса - это то, насколько быстро общаются",
                        "компьютер и GDPad между собой. ",
                        "   Стоит учитывать, что ресурс вашего устройства",
                        "может быть ограничен, и если наблюдается потеря",
                        "производительности, то стоит снизить частоту опроса."
                    ).c_str()
                );

                ImGui::SetNextItemWidth(400);

                int buffer = GDPadShared::bitrate / 1000;
                ImGui::SliderInt("##bitrate", &buffer, 1, 8, "%d000");
                GDPadShared::bitrate = buffer * 1000;

                ImGui::SameLine(.0f, -1.f);
                ImGui::SetNextItemWidth(-1);

                ImGui::Button("Применить", { 200, 0 });
            }


            {
                ImGui::Text(" " ICON_FA_LIGHTBULB "  Цвет подсветки ");

                ImGui::SetNextItemWidth(400);

                ImGui::ColorEdit3("##light", GDPadShared::gdpadLight);

                ImGui::SameLine(.0f, -1.f);
                ImGui::SetNextItemWidth(-1);

                ImGui::Button("Применить", { 200, 0 });
            }

            ImGui::EndTabItem();

        }

        if (ImGui::BeginTabItem(" Дополнительно ")) {
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::PopStyleVar(4);
}