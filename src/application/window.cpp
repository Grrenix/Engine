#include "engine/application/window.hpp"

namespace engine
{
    Window::Window(WindowSpec *Spec)
    {
        if (!glfwInit())
        {
            const char *description;
            glfwGetError(&description);
            printf("Error: %s\n", description);
            exit(EXIT_FAILURE);
        }
#ifndef _WINDOWS
        // This is necessary to get correct window decorations on Wayland
        glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        if (Spec->Borderless)
        {
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        }

        m_Window = glfwCreateWindow(Spec->Width, Spec->Height, Spec->Title.data(), Spec->Fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    }

    bool Window::WindowShouldClose()
    {
        return glfwWindowShouldClose(m_Window);
    }
}