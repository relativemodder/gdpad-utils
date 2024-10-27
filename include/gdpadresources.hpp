#pragma once
#include "shared.hpp"
#include "fmt/format.h"


#ifdef GDPAD_LOAD_RESOURCE_OR_DIE
#else
#define GDPAD_LOAD_RESOURCE_OR_DIE(name, file_name) \
    GDPadShared::textures[name] = GDPadImages::load_texture(file_name); \
    IM_ASSERT(GDPadShared::textures[name] != nullptr); \
    fmt::println("Loaded texture {}", file_name); \
    fmt::println("Pointer is: {}", (long)GDPadShared::textures[name]);
#endif


namespace GDPadResources {
    void load_textures();
    void load_fonts();
}