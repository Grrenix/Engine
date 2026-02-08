#include "engine/application/application.hpp"

#include "engine/events/input_events.hpp"
#include "engine/events/update_event.hpp"
#include "engine/events/window_events.hpp"
#include "engine/input/input_state.hpp"
#include "engine/platform/window.hpp"

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
        s_Singleton->m_EventDispatcher = std::make_unique<EventDispatcher>();
        s_Singleton->m_EventQueue = std::make_unique<EventQueue>();
        s_Singleton->m_InputStates = std::make_unique<input::InputState>();
        return s_Singleton;
    }

    Application *Application::WithWindowSpec(WindowSpec *Spec)
    {
        m_Window = std::make_shared<Window>(Spec);
        return this;
    }

    void Application::Run()
    {

        m_Renderer = std::make_unique<graphics::Renderer>();

        m_EventDispatcher->Subscribe<engine::KeyPressedEvent>(
            [&](const engine::KeyPressedEvent &e)
            { m_InputStates->SetState(e.Data, input::KeyState::Pressed); });
        m_EventDispatcher->Subscribe<engine::KeyReleasedEvent>(
            [&](const engine::KeyReleasedEvent &e)
            { m_InputStates->SetState(e.Data, input::KeyState::Unpressed); });

        m_EventDispatcher->Subscribe<engine::MouseButtonClickEvent>(
            [&](const engine::MouseButtonClickEvent &e)
            { m_InputStates->SetState(e.Button, input::KeyState::Pressed); });
        m_EventDispatcher->Subscribe<engine::MouseButtonReleaseEvent>(
            [&](const engine::MouseButtonReleaseEvent &e)
            { m_InputStates->SetState(e.Button, input::KeyState::Unpressed); });

        while (!m_Window->WindowShouldClose())
        {
            glfwPollEvents();
            auto currentTime = std::chrono::high_resolution_clock::now();
            m_DeltaTime = std::chrono::duration<float>(currentTime - m_PreviousTime).count();
            m_PreviousTime = currentTime;

            m_EventQueue->Push(UpdateEvent(m_DeltaTime));

            m_EventQueue->DispatchAll(m_EventDispatcher);
        }

        m_Renderer.reset();

        // Window Destroyed
        m_Window.reset();
        m_EventQueue->DispatchEventType<WindowDestroyedEvent>(m_EventDispatcher);
    }

    float Application::GetDeltaTime() const
    {
        return m_DeltaTime;
    }

    const std::shared_ptr<Window> Application::GetWindow() const
    {
        return m_Window;
    };
}