#pragma once

#include "engine/input/keyboard_map.hpp"
#include "engine/input/mouse.hpp"
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

    class MouseMovedEvent : public Event<MouseMovedEvent>
    {
    public:
        double PosX = 0.0;
        double PosY = 0.0;

        explicit MouseMovedEvent(double inPosX, double inPosY);

    private:
        MouseMovedEvent() = delete;
    };

    class MouseButtonClickEvent : public Event<MouseButtonClickEvent>
    {
    public:
        input::MouseButton Button;

        explicit MouseButtonClickEvent(int inButton);
        explicit MouseButtonClickEvent(input::MouseButton inButton);

    private:
        MouseButtonClickEvent() = delete;
    };

    class MouseButtonReleaseEvent : public Event<MouseButtonReleaseEvent>
    {
    public:
        input::MouseButton Button;

        explicit MouseButtonReleaseEvent(int inButton);
        explicit MouseButtonReleaseEvent(input::MouseButton inButton);

    private:
        MouseButtonReleaseEvent() = delete;
    };

    class MouseScrollEvent : public Event<MouseScrollEvent>
    {
    public:
        double DirX = 0.0;
        double DirY = 0.0;

        explicit MouseScrollEvent(double inDirX, double inDirY);

    private:
        MouseScrollEvent() = delete;
    };
}
