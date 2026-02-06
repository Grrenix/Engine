#include "engine/application/application.hpp"

#include "engine/application/window.hpp"

namespace engine
{
    Application *Application::New()
    {
        return new Application();
    }

    Application *Application::WithWindowSpec(WindowSpec *Spec)
    {
        m_Window = new Window(Spec);
        return this;
    }

    void Application::Run()
    {
        while (!m_Window->WindowShouldClose())
        {
            glfwPollEvents();
        }
    }
}