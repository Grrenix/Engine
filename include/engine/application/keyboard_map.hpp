#pragma once

#include <unordered_map>
#include <string>

#include "GLFW/glfw3.h"

namespace engine
{
    namespace input
    {
        enum class Key
        {
            k0,
            k1,
            k2,
            k3,
            k4,
            k5,
            k6,
            k7,
            k8,
            k9,

            kA,
            kB,
            kC,
            kD,
            kE,
            kF,
            kG,
            kH,
            kI,
            kJ,
            kK,
            kL,
            kM,
            kN,
            kO,
            kP,
            kQ,
            kR,
            kS,
            kT,
            kU,
            kV,
            kW,
            kX,
            kY,
            kZ,

            kApostrophe,
            kBackslash,
            kComma,
            kEqual,
            kGraveAccent,
            kLeftBracket,
            kMinus,
            kPeriod,
            kRightBracket,
            kSemicolon,
            kSlash,
            kWorld2,

            kBackspace,
            kDelete,
            kEnd,
            kEnter,
            kEscape,
            kHome,
            kInsert,
            kMenu,
            kPageDown,
            kPageUp,
            kPause,
            kSpace,
            kTab,
            kCapsLock,
            kNumLock,
            kScrollLock,
            kF1,
            kF2,
            kF3,
            kF4,
            kF5,
            kF6,
            kF7,
            kF8,
            kF9,
            kF10,
            kF11,
            kF12,
            kF13,
            kF14,
            kF15,
            kF16,
            kF17,
            kF18,
            kF19,
            kF20,
            kF21,
            kF22,
            kF23,
            kF24,
            kLeftAlt,
            kLeftControl,
            kLeftShift,
            kLeftSuper,
            kPrintScreen,
            kRightAlt,
            kRightControl,
            kRightShift,
            kRightSuper,
            kDown,
            kLeft,
            kRight,
            kUp,

            kKeypad0,
            kKeypad1,
            kKeypad2,
            kKeypad3,
            kKeypad4,
            kKeypad5,
            kKeypad6,
            kKeypad7,
            kKeypad8,
            kKeypad9,
            kKeypadAdd,
            kKeypadDecimal,
            kKeypadDivide,
            kKeypadEnter,
            kKeypadEqual,
            kKeypadMultiply,
            kKeypadSubtract,

            kUnknown

        };

        extern const std::unordered_map<int, Key> GlfwKeycodeToEngineKey;

        extern const std::unordered_map<Key, int> EngineKeyToGlfwKeycode;

        const std::string KeyToString(Key key);

    }
}
