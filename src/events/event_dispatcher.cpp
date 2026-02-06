#include "engine/events/event_dispatcher.hpp"

namespace engine
{
    void EventDispatcher::DispatchRaw(EventType type, const void *event) const
    {
        auto it = m_Handlers.find(type);
        if (it == m_Handlers.end())
        {
            return;
        }

        for (auto &handler : it->second)
        {
            handler(&event);
        }
    }
}
