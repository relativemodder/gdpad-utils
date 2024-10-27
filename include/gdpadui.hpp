#pragma once
#include <shared.hpp>
#include <imgui.h>
#include <fmt/format.h>
#include <gdpadsettingsui.hpp>
#include "IconsFontAwesome6.h"


namespace GDPadUI {
    inline constexpr float padding = 20;

    void draw_main_window();
    void HelpMarker(const char* desc);
    void CenteredTitle(std::string text, float text_y = 0);
    void draw_centered_image();
    void draw_bottom_ui();
    void set_style();
}