#ifndef TWEEN_H_
#define TWEEN_H_

#include<functional>
#include "raylib.h"

class Tween
{
public:
    template <typename T>
    void InterpolateValue(T& property, T startVal, T endVal, float duration);

    void UpdateTweens(float delta);
    void StopAllTweens();

private:
    struct TweenEntry
    {
        std::function<void(float)> action;
        float duration;
        float elapsed;
    };

    std::vector<TweenEntry> activeEntries {0};
};

// ====================== DEFINITIONS ======================

template <typename T>
void Tween::InterpolateValue(T& property, T startVal, T endVal, float duration)
{
    std::function<void(float)> interpolator = [&, startVal, endVal](float t) {
        property = (1 - t) * startVal + t * endVal;
    };

    TweenEntry newEntry {interpolator, duration, 0};
    activeEntries.emplace_back(newEntry);
};

#endif // TWEEN_H_
