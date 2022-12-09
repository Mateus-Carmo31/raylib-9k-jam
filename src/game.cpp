#include "game.hpp"

namespace cge
{
    int screenW = 256 * 3, screenH = 256 * 3;
    int renderW = 256, renderH = 256;

    float playerSpeed = 50;

    // Tilemap-related actions
    bool tilemapSet = false;
    Texture2D _tilemapTex;
    Vector2 tileSize {0};
    std::unordered_map<char, Vector2> tilePositions;

    void LoadTilemap(const char* filePath, int tileSizeX, int tileSizeY)
    {
        if (tilemapSet)
            UnloadTilemap();

        _tilemapTex = LoadTexture(filePath);
        tileSize = { (float) tileSizeX, (float) tileSizeY };
        tilemapSet = true;
    }

    void UnloadTilemap()
    {
        if (tilemapSet)
        {
            UnloadTexture(_tilemapTex);
            tileSize = {0};
            tilemapSet = false;
        }
    }

    void RegisterTiles()
    {
        tilePositions[GROUND] = {0,0};
        tilePositions[WALL]   = {10,17};
        tilePositions[PLAYER] = {28,1};
        tilePositions[DOOR]   = {2, 9};
        tilePositions[BOX]    = {15, 14};
    }

    void DrawTile(char id, Vector2 pos)
    {
        Vector2 tile = tilePositions[id];
        tile.x *= tileSize.x;
        tile.y *= tileSize.y;
        DrawTexturePro(_tilemapTex,
                    { tile.x, tile.y, tileSize.x, tileSize.y },
                    { pos.x * tileSize.x, pos.y * tileSize.y, tileSize.x, tileSize.y},
                    {0}, 0, WHITE);
    }

    void DrawTileCentered(char id, Vector2 pos, float rotation, Vector2 customScaling)
    {
        Vector2 tile = tilePositions[id];
        tile.x *= tileSize.x;
        tile.y *= tileSize.y;
        Vector2 actualSize = tileSize;
        actualSize.x *= customScaling.x;
        actualSize.y *= customScaling.y;
        DrawTexturePro(_tilemapTex,
                    { tile.x, tile.y, tileSize.x, tileSize.y },
                    { pos.x * tileSize.x + actualSize.x / 2, pos.y * tileSize.y + actualSize.y / 2, tileSize.x, tileSize.y},
                    { actualSize.x/2, actualSize.y/2 }, rotation, WHITE);
    }


    size_t currentScene = 0;
    Scene* scenes[4];
}
