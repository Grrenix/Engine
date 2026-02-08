#pragma once

namespace engine::input
{
    enum class MouseButton
    {
        bLeft,
        bRight,
        bMiddle,
        bBack,
        bForward,
        bUnknown
    };

    extern const std::unordered_map<int, MouseButton> GlfwButtonToEngine;
    extern const std::unordered_map<MouseButton, int> EngineButtonToGlfw;

    const std::string MouseButtonToString(MouseButton button);
}