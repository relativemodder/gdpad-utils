#include "shared.hpp"
#include <IconsFontAwesome6.h>
#include <fa.h>
#include <gdpadresources.hpp>

void GDPadResources::load_textures() {
    GDPAD_LOAD_RESOURCE_OR_DIE("gdpad", "resources/images/gdpad.png");
}

void GDPadResources::load_fonts() {
    ImGuiIO& io = ImGui::GetIO();

    ImFontConfig icons_config;
    ImFontConfig font_config;
    icons_config.MergeMode = true;

    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

    GDPadShared::fonts["regular"] = io.Fonts->AddFontFromFileTTF(
        "resources/fonts/Roboto-Regular.ttf", 
        19.0f,  
        &font_config, 
        io.Fonts->GetGlyphRangesCyrillic()
    );

    GDPadShared::fonts["fa"] = io.Fonts->AddFontFromMemoryCompressedTTF(
        FA_compressed_data, 
        FA_compressed_size,
        16.0f,  
        &icons_config, 
        icons_ranges
    );

    ImFontConfig title_icons_config;
    ImFontConfig title_font_config;
    title_icons_config.MergeMode = true;

    GDPadShared::fonts["title"] = io.Fonts->AddFontFromFileTTF(
        "resources/fonts/Roboto-Black.ttf", 
        40.0f,  
        &title_font_config, 
        io.Fonts->GetGlyphRangesCyrillic()
    );

    GDPadShared::fonts["fa"] = io.Fonts->AddFontFromMemoryCompressedTTF(
        FA_compressed_data, 
        FA_compressed_size,
        30.0f,  
        &title_icons_config, 
        icons_ranges
    );

    io.Fonts->Build();
}