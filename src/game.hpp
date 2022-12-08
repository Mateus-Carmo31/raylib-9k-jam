#ifndef GAME_H_
#define GAME_H_

#include "scene.hpp"
#include "raylib.h"

namespace cge
{
    // Game-wise values
    extern int screenW, screenH;
    extern int renderW, renderH;

    // Global Tilemap
    extern Vector2 tileSize;
    void LoadTilemap(const char* filePath, int tileSizeX, int tileSizeY);
    void UnloadTilemap();
    void DrawTile(char id, Vector2 pos);
    void DrawTileCentered(char id, Vector2 pos, float rotation = 0, Vector2 customScaling = {1,1});

    // Tile Registry
    const char GROUND = ' ';
    const char WALL   = '#';
    const char PLAYER = 'P';
    const char DOOR   = 'D';
    const char BOX    = 'B';
    void RegisterTiles();

    // Levels
    extern size_t currentScene;
    extern Scene* scenes[3];

    // Player values
    extern float playerSpeed;
};

#endif // GAME_H_
