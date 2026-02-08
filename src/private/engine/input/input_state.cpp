#include "engine/input/input_state.hpp"

namespace engine::input
{
    KeyState InputState::GetState(Key key)
    {
        auto it = m_KeyboardStates.find(key);
        if (it != m_KeyboardStates.end())
        {
            return it->second;
        }
        else
        {
            return KeyState::Unpressed;
        }
    }

    KeyState InputState::GetState(MouseButton button)
    {
        auto it = m_MouseStates.find(button);
        if (it != m_MouseStates.end())
        {
            return it->second;
        }
        else
        {
            return KeyState::Unpressed;
        }
    }

    void InputState::SetState(Key key, KeyState state)
    {
        m_KeyboardStates.insert_or_assign(key, state);
    }

    void InputState::SetState(MouseButton button, KeyState state)
    {
        m_MouseStates.insert_or_assign(button, state);
    }

}