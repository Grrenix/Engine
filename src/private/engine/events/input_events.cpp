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
}