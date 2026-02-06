#pragma once

#include <string_view>

#include <GLFW/glfw3.h>

namespace engine
{

    struct WindowSpec
    {
        std::string_view Title;
        int32_t Width;
        int32_t Height;
        bool Fullscreen;
        bool Borderless;
    };

    class Window
    {
    public:
        Window(WindowSpec *Spec);
        bool WindowShouldClose();

    private:
        Window() {};
        ~Window() {};

        GLFWwindow *m_Window = nullptr;
    };
}