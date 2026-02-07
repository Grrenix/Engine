#pragma once

#include <list>
#include <functional>

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

            queue.emplace_back(QueuedEvent{EventT::GetStaticType(),
                                           heapEvent,
                                           [](void *e)
                                           { delete static_cast<EventT *>(e); }});
        }

        template <typename DispatcherT>
        void DispatchAll(DispatcherT &dispatcher)
        {
            for (auto &q : queue)
            {
                dispatcher->DispatchRaw(q.type, q.event);
                q.destroy(q.event);
            }
            queue.clear();
        }

        template <typename EventT, typename DispatcherT>
        void DispatchEventType(DispatcherT &dispatcher)
        {
            static_assert(std::is_base_of_v<Event<EventT>, EventT>,
                          "EventT must derive from Event<EventT>");

            EventType type = EventT::GetStaticType();

            auto it = queue.begin();
            while (it != queue.end())
            {
                if (it->type == type)
                {
                    dispatcher->DispatchRaw(it->type, it->event);
                    it->destroy(it->event);

                    it = queue.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        bool Empty() const
        {
            return queue.empty();
        }

        size_t Size() const { return queue.size(); }

        void Clear()
        {
            for (auto &q : queue)
            {
                q.destroy(q.event);
            }
            queue.clear();
        }

        ~EventQueue()
        {
            Clear();
        }

    private:
        std::list<QueuedEvent> queue;
    };

}