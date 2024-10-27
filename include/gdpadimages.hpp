#pragma once
#include <GL/gl.h>
#include <cstddef>
#include <imgui.h>
#include <string>


namespace GDPadImages {
    struct GDPadTexture {
        GLuint out_texture;
        ImVec2 size;
    };

    bool load_texture_from_memory(
        const void* data, 
        size_t data_size, 
        GLuint* out_texture, 
        int* out_width, 
        int* out_height
    );


    bool load_texture_from_file(
        const char* file_name, 
        GLuint* out_texture, 
        int* out_width, 
        int* out_height
    );


    GDPadTexture* load_texture(std::string file_name);
}