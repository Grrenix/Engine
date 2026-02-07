#pragma once

#include "event.hpp"

namespace engine
{
    class UpdateEvent : public Event<UpdateEvent>
    {
    public:
        explicit UpdateEvent(float inDeltaTime);

        float DeltaTime = 0.0f;
    };
}
