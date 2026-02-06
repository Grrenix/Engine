#pragma once

#include <queue>

#include "event.hpp"

namespace engine
{
    struct QueuedEvent
    {
        EventType type;
        void *event;
        void (*destroy)(void *);
    };
    class EventQueue
    {
    public:
        EventQueue() = default;
        EventQueue(const EventQueue &) = delete;
        EventQueue &operator=(const EventQueue &) = delete;

        template <typename EventT>
        void Push(EventT event)
        {
            static_assert(std::is_base_of_v<Event<EventT>, EventT>, "EventT must derive from Event<EventT>");

            EventT *heapEvent = new EventT(std::move(event));

            queue.push({EventT::GetStaticType(),
                        heapEvent,
                        [](void *e)
                        { delete static_cast<EventT *>(e); }});
        }

        bool Empty() const
        {
            return queue.empty();
        }

        void Clear()
        {
            while (!queue.empty())
            {
                auto &q = queue.front();
                q.destroy(q.event);
                queue.pop();
            }
        }

        template <typename DispatcherT>
        void DispatchAll(DispatcherT &dispatcher)
        {
            while (!queue.empty())
            {
                auto &q = queue.front();
                dispatcher->DispatchRaw(q.type, q.event);
                q.destroy(q.event);
                queue.pop();
            }
        }

        ~EventQueue()
        {
            Clear();
        }

    private:
        std::queue<QueuedEvent> queue;
    };

}