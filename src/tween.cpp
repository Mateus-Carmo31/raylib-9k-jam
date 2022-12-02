#include "tween.hpp"

template <>
void Tween::InterpolateValue<Vector2>(Vector2& property, Vector2 startVal, Vector2 endVal, float duration)
{
    std::function<void(float)> interpolator = [&, startVal, endVal](float t) {
        property.x = (1 - t) * startVal.x + t * endVal.x;
        property.y = (1 - t) * startVal.y + t * endVal.y;
    };

    TweenEntry newEntry {interpolator, duration, 0};
    activeEntries.emplace_back(newEntry);
}

void Tween::UpdateTweens(float delta)
{
    bool shouldErase = false;
    for(auto& entry : activeEntries)
    {
        entry.elapsed += delta;
        entry.action(std::min(entry.elapsed / entry.duration, 1.0f));

        if (entry.elapsed >= entry.duration)
            shouldErase = true;
    }

    if (shouldErase)
        std::remove_if(activeEntries.begin(), activeEntries.end(), [](TweenEntry entry) {
            return entry.elapsed >= entry.duration;
        });
}
