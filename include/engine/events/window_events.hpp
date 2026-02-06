#pragma once

#include "event.hpp"

namespace engine
{
    class Window;

    class WindowOpenedEvent : public Event<WindowOpenedEvent>
    {
    public:
        explicit WindowOpenedEvent(Window *inWindow);

        Window *Data;

    private:
        WindowOpenedEvent() {};
    };

    class WindowDestroyedEvent : public Event<WindowDestroyedEvent>
    {
    public:
        explicit WindowDestroyedEvent(Window *inWindow);

        Window *Data;

    private:
        WindowDestroyedEvent() {};
    };
}
