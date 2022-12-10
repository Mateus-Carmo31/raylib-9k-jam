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

    Color white = Color {207, 198, 184, 255};

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
                    { pos.x * tileSize.x + tileSize.x/2, pos.y * tileSize.y + tileSize.y/2, actualSize.x, actualSize.y},
                    { actualSize.x/2, actualSize.y/2 }, rotation, WHITE);
    }

    // Scenes
    int currentScene = -1;
    LevelScene* scenes[9];

    // SFXs
    Sound stepSounds[3];
    Sound bigStepSound;
    Sound shiftSound;

    void LoadSFX()
    {
        stepSounds[0] = LoadSound("./assets/audio/step1.wav");
        stepSounds[1] = LoadSound("./assets/audio/step2.wav");
        stepSounds[2] = LoadSound("./assets/audio/step3.wav");

        SetSoundVolume(stepSounds[0], 0.2);
        SetSoundVolume(stepSounds[1], 0.2);
        SetSoundVolume(stepSounds[2], 0.2);

        bigStepSound = LoadSound("./assets/audio/big_step.wav");
        SetSoundVolume(bigStepSound, 0.15);

        shiftSound = LoadSound("./assets/audio/big_shift.wav");
        SetSoundVolume(shiftSound, 0.15);
    }

    void UnloadSFX()
    {
        UnloadSound(stepSounds[0]);
        UnloadSound(stepSounds[1]);
        UnloadSound(stepSounds[2]);

        UnloadSound(bigStepSound);
        UnloadSound(shiftSound);
    }

    void PlayStepSound()
    {
        PlaySound(stepSounds[rand() % 3]);
    }

    Texture2D logo;
    Texture2D bg;

    void LoadTextures()
    {
        logo = LoadTexture("./assets/textures/title.png");
        bg = LoadTexture("./assets/textures/bg.png");
        SetTextureFilter(bg, TEXTURE_FILTER_BILINEAR);
    }

    void UnloadTextures()
    {
        UnloadTexture(logo);
        UnloadTexture(bg);
    }

    void DrawTextCentered(const char* text, int posX, int posY, int fontSize, Color color)
    {
        float textSize = MeasureText(text, fontSize);
        DrawText(text, posX - textSize/2, posY - fontSize / 2, fontSize, color);
    }
}
