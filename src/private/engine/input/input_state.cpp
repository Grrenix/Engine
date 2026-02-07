#include "engine/input/input_state.hpp"

namespace engine::input
{
    KeyState InputState::GetState(Key key)
    {
        auto it = m_States.find(key);
        if (it != m_States.end())
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
        m_States.insert_or_assign(key, state);
    }

}
