#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <string>
#include <unordered_map>
#include "raylib.h"

struct Tilemap
{
    Tilemap(const std::string& filePath, Vector2 tileSize) : tileSize(tileSize)
    {
        _tileSheet = LoadTexture(filePath.c_str());
    }

    ~Tilemap()
    {
        UnloadTexture(_tileSheet);
    }

    void RegisterTile(char id, Vector2 sheetPos);
    void DrawTile(char id, Vector2 pos, Vector2 customSize = {1,1});
    Vector2 tileSize;

private:
    Texture2D _tileSheet;
    std::unordered_map<char, Vector2> tilePositions;
};

inline void Tilemap::RegisterTile(char id, Vector2 sheetPos)
{
    tilePositions[id] = {sheetPos.x * tileSize.x, sheetPos.y * tileSize.y};
}


#endif // TILEMAP_H_
