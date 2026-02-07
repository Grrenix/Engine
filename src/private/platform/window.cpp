#include "platform/window.hpp"

#include "application/application.hpp"
#include "events/window_events.hpp"
#include "events/input_events.hpp"

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

        glfwSetKeyCallback(m_Window, KeyCallback);

        Application::GetApplication()->m_EventQueue->Push(WindowOpenedEvent(this));
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        Application::GetApplication()->m_EventQueue->Push(WindowDestroyedEvent(this));
    }

    bool Window::WindowShouldClose()
    {
        return glfwWindowShouldClose(m_Window);
    }

    const GLFWwindow *Window::GetWindowHandle()
    {
        return m_Window;
    }
    void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            Application::GetApplication()->m_EventQueue->Push(KeyPressedEvent(key));
        }
        else if (action == GLFW_RELEASE)
        {
            Application::GetApplication()->m_EventQueue->Push(KeyReleasedEvent(key));
        }
    }
}