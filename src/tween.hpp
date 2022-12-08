#ifndef TWEEN_H_
#define TWEEN_H_

#include<functional>
#include<forward_list>
#include "raylib.h"

class Tween
{
public:
    template <typename T>
    void InterpolateValue(T& property, T startVal, T endVal, float duration, std::function<void()> callback = nullptr);

    void UpdateTweens(float delta);
    void StopAllTweens();
    bool isActive() const;

private:
    struct TweenEntry
    {
        std::function<void(float)> action;
        std::function<void()> finishCallback;
        float duration;
        float elapsed;
    };

    std::forward_list<TweenEntry> activeEntries;
};

// some peeps over on raylib said that this might increase class instance size
// (various template instances in the class), but some sources like
// https://stackoverflow.com/questions/8058213/do-class-methods-increase-the-size-of-the-class-instances
// https://www.cprogramming.com/tutorial/size_of_class_object.html
// claim otherwise. I will leave it like this.
template <typename T>
void Tween::InterpolateValue(T& property, T startVal, T endVal, float duration, std::function<void()> callback)
{
    std::function<void(float)> interpolator = [&, startVal, endVal](float t) {
        property = (1 - t) * startVal + t * endVal;
    };

    TweenEntry newEntry {interpolator, callback, duration, 0};
    activeEntries.emplace_front(newEntry);
};

template <>
inline void Tween::InterpolateValue<Vector2>(Vector2& property, Vector2 startVal, Vector2 endVal, float duration, std::function<void()> callback)
{
    std::function<void(float)> interpolator = [&, startVal, endVal](float t) {
        property.x = (1 - t) * startVal.x + t * endVal.x;
        property.y = (1 - t) * startVal.y + t * endVal.y;
    };

    TweenEntry newEntry {interpolator, callback, duration, 0};
    activeEntries.emplace_front(newEntry);
}

inline bool Tween::isActive() const
{
    return !activeEntries.empty();
}

#endif // TWEEN_H_
