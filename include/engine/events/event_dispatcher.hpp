#pragma once

#include <functional>

#include "event.hpp"

namespace engine
{
    class EventDispatcher
    {
        using HandlerFn = std::function<void(const void *)>;

    public:
        template <typename EventT>
        void Subscribe(std::function<void(const EventT &)> handler)
        {
            auto wrapper = [handler](const void *e)
            {
                handler(*static_cast<const EventT *>(e));
            };

            m_Handlers[EventT::GetStaticType()].push_back(std::move(wrapper));
        };

        template <typename EventT>
        void Dispatch(const EventT &event) const
        {
            DispatchRaw(event.GetType(), &event);
        };

        template <typename EventT>
        void DispatchRaw(EventType type, const EventT &event) const
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
        };

    private:
        std::unordered_map<EventType, std::vector<HandlerFn>> m_Handlers;
    };
}