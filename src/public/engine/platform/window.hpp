#pragma once

#include <string_view>

class GLFWwindow;

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

        void *GetWindowHandle();

        ~Window();

    private:
        Window() {};
        GLFWwindow *m_Window = nullptr;
    };
    void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void MouseInputCallback(GLFWwindow *window, double xpos, double ypos);
    void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    void MouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
}