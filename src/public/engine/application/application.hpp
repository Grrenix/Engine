#pragma once

#include <chrono>
#include <memory>

#include "engine/events/event_dispatcher.hpp"
#include "engine/events/event_queue.hpp"
#include "engine/graphics/renderer.hpp"
#include "engine/input/input_state.hpp"

namespace engine
{
    class Application
    {
    public:
        // Builder
        static Application *New();
        Application *WithWindowSpec(class WindowSpec *Spec);

        void Run();

        std::unique_ptr<EventDispatcher> m_EventDispatcher = nullptr;
        std::unique_ptr<EventQueue> m_EventQueue = nullptr;

        std::unique_ptr<input::InputState> m_InputStates = nullptr;

        std::unique_ptr<graphics::Renderer> m_Renderer = nullptr;

        float GetDeltaTime() const;

    private:
        std::shared_ptr<class Window> m_Window = nullptr;

        std::chrono::high_resolution_clock::time_point m_PreviousTime;
        float m_DeltaTime;

    public:
        Application(Application &other) = delete;
        void operator=(const Application &other) = delete;

        static Application *GetApplication();

    private:
        Application() {};

        static Application *s_Singleton;
    };
}