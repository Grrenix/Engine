#pragma once

#include "engine/input/keyboard_map.hpp"
#include "event.hpp"

namespace engine
{
    class KeyPressedEvent : public Event<KeyPressedEvent>
    {
    public:
        input::Key Data = input::Key::kUnknown;
        explicit KeyPressedEvent(int GlfwKey);
        explicit KeyPressedEvent(input::Key EngineKey);

    private:
        KeyPressedEvent() = delete;
    };

    class KeyReleasedEvent : public Event<KeyReleasedEvent>
    {
    public:
        input::Key Data = input::Key::kUnknown;
        explicit KeyReleasedEvent(int GlfwKey);
        explicit KeyReleasedEvent(input::Key EngineKey);

    private:
        KeyReleasedEvent() = delete;
    };
}
