#include "raylib.h"
#include "tilemap.hpp"

void Tilemap::DrawTile(char id, Vector2 pos, Vector2 customSize)
{
    Vector2 tile = tilePositions[id];
    DrawTexturePro(_tileSheet,
                   { tile.x, tile.y, tileSize.x, tileSize.y },
                   { pos.x * tileSize.x, pos.y * tileSize.y, tileSize.x, tileSize.y},
                   {0}, 0, WHITE);
}
