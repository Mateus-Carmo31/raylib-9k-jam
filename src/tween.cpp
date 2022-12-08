#include "tween.hpp"

void Tween::UpdateTweens(float delta)
{
    bool shouldErase = false;
    for(auto& entry : activeEntries)
    {
        entry.elapsed += delta;
        entry.action(std::min(entry.elapsed / entry.duration, 1.0f));

        if (entry.elapsed >= entry.duration)
        {
            if (entry.finishCallback != nullptr)
                entry.finishCallback();
            shouldErase = true;
        }
    }

    if (shouldErase)
        activeEntries.remove_if([](TweenEntry entry) {
            return entry.elapsed >= entry.duration;
        });
}
