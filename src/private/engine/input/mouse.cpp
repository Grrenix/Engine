#include "engine/input/mouse.hpp"

#include "GLFW/glfw3.h"

namespace engine::input
{
    const std::unordered_map<int, MouseButton> GlfwButtonToEngine = {{GLFW_MOUSE_BUTTON_LEFT, MouseButton::bLeft},
                                                                     {GLFW_MOUSE_BUTTON_RIGHT, MouseButton::bRight},
                                                                     {GLFW_MOUSE_BUTTON_MIDDLE, MouseButton::bMiddle},
                                                                     {GLFW_MOUSE_BUTTON_4, MouseButton::bBack},
                                                                     {GLFW_MOUSE_BUTTON_5, MouseButton::bForward}};

    const std::unordered_map<MouseButton, int> EngineButtonToGlfw = {{MouseButton::bLeft, GLFW_MOUSE_BUTTON_LEFT},
                                                                     {MouseButton::bRight, GLFW_MOUSE_BUTTON_RIGHT},
                                                                     {MouseButton::bMiddle, GLFW_MOUSE_BUTTON_MIDDLE},
                                                                     {MouseButton::bBack, GLFW_MOUSE_BUTTON_4},
                                                                     {MouseButton::bForward, GLFW_MOUSE_BUTTON_5}};

    const std::string MouseButtonToString(MouseButton button)
    {
        switch (button)
        {
        case MouseButton::bLeft:
            return "Left";
        case MouseButton::bRight:
            return "Right";
        case MouseButton::bMiddle:
            return "Middle";
        case MouseButton::bBack:
            return "Back";
        case MouseButton::bForward:
            return "Forward";
        default:
            return "Unknown";
        }
    }
}