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
    void DrawTileCentered(char id, Vector2 pos, Vector2 customScaling);

    // Tile Registry
    const char GROUND = ' ';
    const char WALL   = '#';
    const char PLAYER = 'P';
    void RegisterTiles();

    // Player values
    extern float playerSpeed;

    // Globals
    extern Scene* currentScene;
};

#endif // GAME_H_
