#pragma once

#include "engine/events/event_dispatcher.hpp"
#include "engine/events/event_queue.hpp"

namespace engine
{
    class Application
    {
    public:
        // Builder
        static Application *New();
        Application *WithWindowSpec(class WindowSpec *Spec);

        virtual void Run();

        EventDispatcher *m_EventDispatcher = nullptr;
        EventQueue *m_EventQueue = nullptr;

    private:
        class Window *m_Window = nullptr;

    public:
        Application(Application &other) = delete;
        void operator=(const Application &other) = delete;

        static Application *GetApplication();

    private:
        Application() {};

        static Application *p_Singleton;
    };
}