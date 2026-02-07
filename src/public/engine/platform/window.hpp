#pragma once

#include <string_view>

#include <GLFW/glfw3.h>

namespace engine
{

    struct WindowSpec
    {
        std::string_view Title = "New Window";
        int32_t Width = 640;
        int32_t Height = 480;
        bool Fullscreen = false;
        bool Borderless = false;
    };

    class Window
    {
    public:
        Window(WindowSpec *Spec);
        bool WindowShouldClose();

        const GLFWwindow *GetWindowHandle();

        ~Window();

    private:
        Window() {};
        GLFWwindow *m_Window = nullptr;
    };
    void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
}