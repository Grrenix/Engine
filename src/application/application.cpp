#include "engine/application/application.hpp"

#include "engine/application/window.hpp"
#include "engine/events/window_events.hpp"
#include "engine/events/input_events.hpp"
#include "engine/application/input_state.hpp"
#include "engine/events/update_event.hpp"

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
        p_Singleton->m_InputStates = new input::InputState();
        return p_Singleton;
    }

    Application *Application::WithWindowSpec(WindowSpec *Spec)
    {
        m_Window = new Window(Spec);
        return this;
    }

    void Application::Run()
    {
        m_EventDispatcher->Subscribe<engine::KeyPressedEvent>([&](const engine::KeyPressedEvent &e)
                                                              { m_InputStates->SetState(e.Data, input::KeyState::Pressed); });
        m_EventDispatcher->Subscribe<engine::KeyReleasedEvent>([&](const engine::KeyReleasedEvent &e)
                                                               { m_InputStates->SetState(e.Data, input::KeyState::Unpressed); });
        while (!m_Window->WindowShouldClose())

        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            m_DeltaTime = std::chrono::duration<float>(currentTime - m_PreviousTime).count();
            m_PreviousTime = currentTime;

            m_EventQueue->Push(UpdateEvent(m_DeltaTime));

            glfwPollEvents();

            m_EventQueue->DispatchAll(m_EventDispatcher);
        }

        // Window Destroyed
        Application::GetApplication()->m_EventQueue->Push(WindowDestroyedEvent(m_Window));
        m_EventQueue->DispatchEventType<WindowDestroyedEvent>(m_EventDispatcher);
    }
    float Application::GetDeltaTime() const
    {
        return m_DeltaTime;
    }
}