#include "engine/events/input_events.hpp"

namespace engine
{
    KeyPressedEvent::KeyPressedEvent(int GlfwKey)
    {
        auto it = input::GlfwKeycodeToEngineKey.find(GlfwKey);
        if (it != input::GlfwKeycodeToEngineKey.end())
        {
            Data = it->second;
        }
        else
        {
            Data = input::Key::kUnknown;
        }
    }

    KeyPressedEvent::KeyPressedEvent(input::Key EngineKey)
    {
        Data = EngineKey;
    }

    KeyReleasedEvent::KeyReleasedEvent(int GlfwKey)
    {
        auto it = input::GlfwKeycodeToEngineKey.find(GlfwKey);
        if (it != input::GlfwKeycodeToEngineKey.end())
        {
            Data = it->second;
        }
        else
        {
            Data = input::Key::kUnknown;
        }
    }

    KeyReleasedEvent::KeyReleasedEvent(input::Key EngineKey)
    {
        Data = EngineKey;
    }

    MouseMovedEvent::MouseMovedEvent(double inPosX, double inPosY)
    {
        PosX = inPosX;
        PosY = inPosY;
    }

    MouseButtonClickEvent::MouseButtonClickEvent(int inButton)
    {
        auto it = input::GlfwButtonToEngine.find(inButton);
        if (it != input::GlfwButtonToEngine.end())
        {
            Button = it->second;
        }
        else
        {
            Button = input::MouseButton::bUnknown;
        }
    }

    MouseButtonClickEvent::MouseButtonClickEvent(input::MouseButton inButton)
    {
        Button = inButton;
    }

    MouseButtonReleaseEvent::MouseButtonReleaseEvent(int inButton)
    {
        auto it = input::GlfwButtonToEngine.find(inButton);
        if (it != input::GlfwButtonToEngine.end())
        {
            Button = it->second;
        }
        else
        {
            Button = input::MouseButton::bUnknown;
        }
    }

    MouseButtonReleaseEvent::MouseButtonReleaseEvent(input::MouseButton inButton)
    {
        Button = inButton;
    }

    MouseScrollEvent::MouseScrollEvent(double inDirX, double inDirY)
    {
        DirX = inDirX;
        DirY = inDirY;
    }
}