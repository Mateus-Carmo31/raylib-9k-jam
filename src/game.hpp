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

    extern Color white;

    // Levels
    extern int currentScene;
    extern LevelScene* scenes[9];

    // Textures
    extern Texture2D logo;
    extern Texture2D bg;
    void LoadTextures();
    void UnloadTextures();

    // SFX
    extern Sound stepSounds[3];
    extern Sound bigStepSound;
    extern Sound shiftSound;
    void LoadSFX();
    void UnloadSFX();
    void PlayStepSound();

    // Text
    void DrawTextCentered(const char* text, int posX, int posY, int fontSize, Color color);
};

#endif // GAME_H_
