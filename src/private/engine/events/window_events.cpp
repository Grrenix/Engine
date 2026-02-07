
#include "engine/events/window_events.hpp"

namespace engine
{
    WindowOpenedEvent::WindowOpenedEvent(Window *inWindow)
    {
        Data = inWindow;
    }

    WindowDestroyedEvent::WindowDestroyedEvent(Window *inWindow)
    {
        Data = inWindow;
    }
};