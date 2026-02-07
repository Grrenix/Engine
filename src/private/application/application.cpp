#include "application/application.hpp"

#include "platform/window.hpp"
#include "events/window_events.hpp"
#include "events/input_events.hpp"
#include "events/update_event.hpp"
#include "input/input_state.hpp"

namespace engine
{

    Application *Application::s_Singleton = nullptr;

    Application *Application::GetApplication()
    {
        return s_Singleton;
    }

    Application *Application::New()
    {
        s_Singleton = new Application();
        s_Singleton->m_EventDispatcher = new EventDispatcher();
        s_Singleton->m_EventQueue = new EventQueue();
        s_Singleton->m_InputStates = new input::InputState();
        return s_Singleton;
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
            glfwPollEvents();
            auto currentTime = std::chrono::high_resolution_clock::now();
            m_DeltaTime = std::chrono::duration<float>(currentTime - m_PreviousTime).count();
            m_PreviousTime = currentTime;

            m_EventQueue->Push(UpdateEvent(m_DeltaTime));

            m_EventQueue->DispatchAll(m_EventDispatcher);
        }

        // Window Destroyed
        m_EventQueue->Push(WindowDestroyedEvent(m_Window));
        m_EventQueue->DispatchEventType<WindowDestroyedEvent>(m_EventDispatcher);
    }
    float Application::GetDeltaTime() const
    {
        return m_DeltaTime;
    }
}