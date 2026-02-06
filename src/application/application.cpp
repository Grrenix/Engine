#include "engine/application/application.hpp"

#include "engine/application/window.hpp"
#include "engine/events/window_events.hpp"

namespace engine
{

    Application *Application::p_Singleton = nullptr;

    Application *Application::GetApplication()
    {
        return p_Singleton;
    }

    Application *Application::New()
    {
        p_Singleton = new Application();
        p_Singleton->m_EventDispatcher = new EventDispatcher();
        p_Singleton->m_EventQueue = new EventQueue();
        return p_Singleton;
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
            m_EventQueue->DispatchAll(m_EventDispatcher);
        }

        // Window Destroyed
        Application::GetApplication()->m_EventQueue->Push(WindowDestroyedEvent(m_Window));
        m_EventQueue->DispatchEventType<WindowDestroyedEvent>(m_EventDispatcher);
    }
}