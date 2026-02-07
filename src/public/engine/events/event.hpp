#pragma once

namespace engine
{
    using EventType = std::size_t;

    inline EventType NextEventType()
    {
        static EventType counter = 0;
        return counter++;
    }

    template <typename Derived>
    class Event
    {
    public:
        static EventType GetStaticType()
        {
            static EventType type = NextEventType();
            return type;
        }

        EventType GetType() const
        {
            return GetStaticType();
        }
    };

}