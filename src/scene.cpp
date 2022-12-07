#include "scene.hpp"
#include <fstream>
#include "game.hpp"
#include "raylib.h"

Scene::Scene(int width, int height) :
    scenePlayer({{1,1}, {1,1}, cge::PLAYER}),
    mapW(width),
    mapH(height),
    sceneRig(
        { Camera2D {
        { (float) cge::renderH/2, (float) cge::renderW/2 },
        { (float) mapW / 2 * cge::tileSize.x, (float) mapH / 2 * cge::tileSize.y},
        0, 1.0f }, 0.6})
{
    map = new char[width * height]();
}

Scene::~Scene()
{
    delete[] map;
}

Vector2 ToTile(Vector2 worldPos);
Vector2 ToWorld(Vector2 tilePos);

void Scene::LoadMap(const char *mapFile)
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
        map[x + y * mapW] = c;
        x++;
        if (x == mapW)
        {
            x = 0;
            y++;
        }
    }
}

void Scene::Update(float delta)
{
    // Handle camera rig

    if (IsKeyPressed(KEY_SPACE))
    {
        sceneRig.ApplyTrauma(0.2);
    }

    sceneRig.Update(delta);

    // Handle player movement

    Vector2 input;
    input.x = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) - (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A));
    input.y = (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) - (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W));

    HandleMove(input, delta);

    inputTimer = std::max(inputTimer - delta, 0.0f);
}

void Scene::HandleMove(Vector2 input, float delta)
{
    if (input.x != 0 || input.y != 0)
    {
        if (inputTimer == 0)
        {
            float nPosX = scenePlayer.pos.x + input.x;
            float nPosY = scenePlayer.pos.y + input.y;

            // Change this for a better collision detection!
            if (GetTile(nPosX, nPosY) != cge::WALL)
            {
                scenePlayer.pos.x += input.x;
                scenePlayer.pos.y += input.y;
                inputTimer = 0.2;
            }
        }
    }
    else
    {
        inputTimer = 0;
    }
}

void Scene::Draw()
{
    BeginMode2D(sceneRig.cam);
    for (int i = 0; i < mapH * mapW; i++)
    {
        float y = i / mapW;
        float x = i - y * mapW;
        cge::DrawTile(map[i], Vector2 {x, y});
    }

    cge::DrawTileCentered(scenePlayer.playerTexId, scenePlayer.pos, scenePlayer.size);

    EndMode2D();
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
