#include "events/update_event.hpp"

namespace engine
{
    UpdateEvent::UpdateEvent(float inDeltaTime)
    {
        DeltaTime = inDeltaTime;
    }
}