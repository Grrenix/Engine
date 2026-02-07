#pragma once

#include <chrono>

#include "events/event_dispatcher.hpp"
#include "events/event_queue.hpp"
#include "input/input_state.hpp"

namespace engine
{
    class Application
    {
    public:
        // Builder
        static Application *New();
        Application *WithWindowSpec(class WindowSpec *Spec);

        void Run();

        EventDispatcher *m_EventDispatcher = nullptr;
        EventQueue *m_EventQueue = nullptr;

        input::InputState *m_InputStates = nullptr;

        float GetDeltaTime() const;

    private:
        class Window *m_Window = nullptr;

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