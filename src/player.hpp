#ifndef PLAYER_H_
#define PLAYER_H_

#include "raylib.h"

struct Player
{
    Player(Vector2 pos, Vector2 size, char playerTexId) : pos(pos), size(size), playerTexId(playerTexId) {}

    Vector2 pos;
    Vector2 size; // Multiplier over tilesize

    char playerTexId;
};

#endif // PLAYER_H_
