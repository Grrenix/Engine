#pragma once

#include "engine/application/keyboard_map.hpp"

#include <unordered_map>

namespace engine::input
{
    enum class KeyState
    {
        Unpressed,
        Pressed
    };
    class InputState
    {
    public:
        KeyState GetState(Key key);
        void SetState(Key key, KeyState state);

    private:
        std::unordered_map<Key, KeyState> m_States;
    };
}
