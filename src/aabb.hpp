#ifndef AABB_H_
#define AABB_H_

#include "raylib.h"

struct AABB
{
    float x, y, height, width;
    AABB(float x, float y, float width, float height) : x(x), y(y), height(height), width(width) {}
    AABB(Vector2 origin, Vector2 size) : x(origin.x), y(origin.y), height(size.y), width(size.x) {}

    bool isPointIn(Vector2 point);
    bool Collide(AABB other);
};

inline bool AABB::Collide(AABB other)
{
    if (x + width < other.x)
        return false;

    if (x > other.x + other.width)
        return false;

    if (y + height < other.y)
        return false;

    if (y > other.y + other.height)
        return false;

    return true;
}

#endif // AABB_H_
