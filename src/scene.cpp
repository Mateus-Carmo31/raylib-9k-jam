#include "scene.hpp"
#include <fstream>
#include "game.hpp"
#include "raylib.h"

LevelScene::LevelScene(int width, int height, const char* mapFile) :
    mapW(width),
    mapH(height),
    sceneRig(
        { Camera2D {
        { (float) cge::renderH/2, (float) cge::renderW/2 },
        { (float) mapW / 2 * cge::tileSize.x, (float) mapH / 2 * cge::tileSize.y},
        0, 1.0f }, 1.0})
{
    exitDoor.texId = cge::DOOR;
    map = new char[width * height]();
    LoadMap(mapFile);
}

LevelScene::~LevelScene()
{
    delete[] map;
}

Vector2 ToTile(Vector2 worldPos);
Vector2 ToWorld(Vector2 tilePos);

void LevelScene::LoadMap(const char *mapFile)
{
    std::ifstream fileStream { mapFile };

    if (!fileStream)
    {
        TraceLog(LOG_ERROR, "Failed to read file [%s].", mapFile);
        return;
    }

    int x = 0, y = 0;
    while(y < mapH)
    {
        char c;
        fileStream.get(c);

        if (c == '\n')
            continue;

        if (c == 'P')
        {
            scenePlayer.pos = {(float) x, (float) y};
            c = cge::GROUND;
        }
        if (c == 'D')
        {
            exitDoor.pos = {(float) x, (float) y};
            c = cge::GROUND;
        }

        map[x + y * mapW] = c;
        x++;
        if (x == mapW)
        {
            x = 0;
            y++;
        }
    }
}

void LevelScene::StartLevel()
{
    paused = true;
    sceneTween.InterpolateValue(fade, 1.0f, 0.0f, 1.0f, [this]() { this->paused = false; });
}

void LevelScene::FinishLevel()
{
    sceneTween.InterpolateValue(fade, 0.0f, 1.0f, 1.0f, [this]() { this->sceneWon = true; });
    paused = true;
}

void LevelScene::Update(float delta)
{
    // Handle camera rig

    if (IsKeyPressed(KEY_SPACE))
    {
        sceneRig.SetTrauma(0.2);
    }

    sceneRig.Update(delta);

    // Handle player movement

    Vector2 input;
    input.x = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) - (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A));
    input.y = (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) - (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W));

    if (!paused)
        HandleMove(input, delta);

    if (scenePlayer.pos.x == exitDoor.pos.x && scenePlayer.pos.y == exitDoor.pos.y && !sceneTween.isActive())
    {
        FinishLevel();
    }

    sceneTween.UpdateTweens(delta);

    inputTimer = std::max(inputTimer - delta, 0.0f);
}

void LevelScene::HandleMove(Vector2 input, float delta)
{
    if (input.x != 0 || input.y != 0)
    {
        if (inputTimer == 0)
        {
            float nPosX = scenePlayer.pos.x + input.x;
            float nPosY = scenePlayer.pos.y + input.y;

            char destTile = GetTile(nPosX, nPosY);

            // Change this for a better collision detection!
            if (destTile == cge::WALL)
            {
                sceneRig.SetTrauma(0.15);
                inputTimer = 0.2;
                return;
            }
            else
            {
                sceneTween.InterpolateValue<Vector2>(scenePlayer.pos, scenePlayer.pos, Vector2 {nPosX, nPosY}, 0.15f);
                cge::PlayStepSound();
                inputTimer = 0.2;
            }
        }
    }
}

void LevelScene::Draw()
{
    BeginMode2D(sceneRig.cam);
    for (int i = 0; i < mapH * mapW; i++)
    {
        float y = i / mapW;
        float x = i - y * mapW;
        cge::DrawTile(map[i], Vector2 {x, y});
    }

    cge::DrawTileCentered(exitDoor.texId, exitDoor.pos);
    cge::DrawTileCentered(scenePlayer.playerTexId, scenePlayer.pos, scenePlayer.rotation, scenePlayer.size);

    for (Object& obj : objects)
    {
        cge::DrawTileCentered(obj.texId, obj.pos);
    }

    EndMode2D();

    DrawRectangleRec({0, 0, (float) cge::renderW, (float) cge::renderH}, ColorFromNormalized({0,0,0,fade}));
}

// ====================== UTILITY FUNCTIONS ====================

inline Vector2 ToTile(Vector2 worldPos)
{
    return Vector2 {floorf(worldPos.x / cge::tileSize.x), floorf(worldPos.y / cge::tileSize.y)};
}

inline Vector2 ToWorld(Vector2 tilePos)
{
    return Vector2 {tilePos.x * cge::tileSize.x, tilePos.y * cge::tileSize.y};
}
