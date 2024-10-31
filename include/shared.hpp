#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <map>
#include "gdpadimages.hpp"

namespace GDPadShared {
    inline GLFWwindow* window;
    const ImVec2 minWindowSize = { 680, 650 };
    inline ImVec2 windowSize;
    
    inline ImVec2 mainFramePos;
    inline ImVec2 mainFrameSize;

    inline std::map<std::string, GDPadImages::GDPadTexture*> textures = {};
    inline std::map<std::string, ImFont*> fonts = {};
    inline int bitrate = 8000;
    inline float gdpadLight[] = { .0f, .0f, .0f };
}