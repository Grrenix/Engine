#pragma once

#include "event.hpp"
#include "engine/application/keyboard_map.hpp"

namespace engine
{
    class KeyPressedEvent : public Event<KeyPressedEvent>
    {
    public:
        input::Key Data = input::Key::kUnknown;
        explicit KeyPressedEvent(int GlfwKey);
        explicit KeyPressedEvent(input::Key EngineKey);

        KeyPressedEvent(const KeyPressedEvent &) = default;
        KeyPressedEvent(KeyPressedEvent &&) = default;

    private:
        KeyPressedEvent() = delete;
    };

    class KeyReleasedEvent : public Event<KeyReleasedEvent>
    {
    public:
        input::Key Data = input::Key::kUnknown;
        explicit KeyReleasedEvent(int GlfwKey);
        explicit KeyReleasedEvent(input::Key EngineKey);

        KeyReleasedEvent(const KeyReleasedEvent &) = default;
        KeyReleasedEvent(KeyReleasedEvent &&) = default;

    private:
        KeyReleasedEvent() = delete;
    };
}
