#ifndef PLAYER_H_
#define PLAYER_H_

#include "raylib.h"

struct Player
{
    Player(Vector2 pos, Vector2 size) : pos(pos), size(size) {}

    void Update(Vector2 input, float delta);
    void Draw();

    Vector2 pos;
    Vector2 size;
};

#endif // PLAYER_H_
