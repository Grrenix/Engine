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

        m_Window = glfwCreateWindow(Spec->Width, Spec->Height, Spec->Title.data(), NULL, NULL);
    }

    bool Window::WindowShouldClose()
    {
        glfwMakeContextCurrent(m_Window);
        return glfwWindowShouldClose(m_Window);
    }
}