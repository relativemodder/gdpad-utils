#include <gdpadimages.hpp>
#include <imgui.h>

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool GDPadImages::load_texture_from_memory(
    const void* data, 
    size_t data_size, 
    GLuint* out_texture, 
    int* out_width, 
    int* out_height
) {
    int image_width = 0;
    int image_height = 0;
    int image_channels = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, &image_channels, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

bool GDPadImages::load_texture_from_file(
    const char* file_name, 
    GLuint* out_texture, 
    int* out_width, 
    int* out_height
) {
    FILE* file = fopen(file_name, "rb");
    
    if (file == NULL) {
        return false;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);

    if (file_size == -1) {
        fclose(file);
        return false;
    }

    fseek(file, 0, SEEK_SET);
    void* file_data = IM_ALLOC(file_size);

    if (fread(file_data, 1, file_size, file) != file_size) {
        IM_FREE(file_data);
        fclose(file);
        return false;
    }

    bool ret = load_texture_from_memory(file_data, file_size, out_texture, out_width, out_height);
    IM_FREE(file_data);
    fclose(file);

    return ret;
}

GDPadImages::GDPadTexture* GDPadImages::load_texture(std::string file_name) {
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    bool ret = GDPadImages::load_texture_from_file(
        file_name.c_str(), 
        &my_image_texture, 
        &my_image_width, 
        &my_image_height
    );

    IM_ASSERT(ret);
    
    if (!ret) {
        return nullptr;
    }

    ImVec2 res_size = {
        my_image_width + .0f, 
        my_image_height + .0f
    };

    return new GDPadTexture({
        .out_texture=my_image_texture, 
        .size=res_size
    });
}