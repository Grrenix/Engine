#pragma once

#include "engine/input/keyboard_map.hpp"
#include "engine/input/mouse.hpp"

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
    KeyState GetState(MouseButton button);
    void SetState(Key key, KeyState state);
    void SetState(MouseButton button, KeyState state);

  private:
    std::unordered_map<Key, KeyState> m_KeyboardStates;
    std::unordered_map<MouseButton, KeyState> m_MouseStates;
  };
}