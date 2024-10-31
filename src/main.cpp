#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <chrono>
#include <stdio.h>
#include <thread>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <filesystem>

#include <gdpadui.hpp>
#include <gdpadresources.hpp>
#include <shared.hpp>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int argc, char** argv)
{
    try
    {
#ifdef FOR_FLATPAK
#else
        std::filesystem::current_path(std::filesystem::path(argv[0]).parent_path());
        fmt::println("Now current dir is: {}", std::filesystem::current_path().string());
#endif

        glfwSetErrorCallback(glfw_error_callback);

        auto init_result = glfwInit();

        if (!init_result)
        {
            throw std::runtime_error("Failed to initialize GLFW:  " + std::to_string(init_result));
        }

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

        GLFWwindow* window = glfwCreateWindow(
            GDPadShared::minWindowSize.x,
            GDPadShared::minWindowSize.y,
            "GDPad Tool",
            nullptr,
            nullptr
        );

        if (window == nullptr)
        {
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);

        glfwSetWindowSizeLimits(
            window,
            GDPadShared::minWindowSize.x,
            GDPadShared::minWindowSize.y,
            GLFW_DONT_CARE, GLFW_DONT_CARE
        );

        glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.IniFilename = NULL;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        GDPadResources::load_textures();

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        GDPadResources::load_fonts();

        ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0);

        fmt::println("Textures map:");

        for (auto& texture : GDPadShared::textures)
        {
            fmt::println(
                "Texture {} #{}, {}x{}",
                texture.first,
                (long)texture.second->out_texture,
                texture.second->size.x,
                texture.second->size.y
            );
        }

        GDPadUI::set_style();

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            GDPadUI::draw_main_window();

            ImGui::Render();

            int display_w, display_h;

            glfwGetFramebufferSize(window, &display_w, &display_h);

            glViewport(0, 0, display_w, display_h);
            glClearColor(
                clear_color.x * clear_color.w,
                clear_color.y * clear_color.w,
                clear_color.z * clear_color.w,
                clear_color.w
            );
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            GDPadShared::windowSize = {
                display_w + .0f,
                display_h + .0f
            };

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
    }
    catch (const std::exception& e)
    {
        fmt::println("Error: {}", e.what());
        return 1;
    }

    return 0;
}