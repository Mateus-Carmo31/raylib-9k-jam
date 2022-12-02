#include "scene.hpp"
#include "game.hpp"
#include "tilemap.hpp"
#include "raylib.h"

Scene::Scene(int width, int height) : mapW(width), mapH(height)
{
    map = new char[width * height]();
    sceneCam = Camera2D {
        { (float) cge::renderH/2, (float) cge::renderW/2 },
        { (float) mapW / 2, (float) mapH / 2},
        0, 1.0f
    };
    scenePlayer = new Player({1,1}, {1,1});
}

Scene::~Scene()
{
    delete scenePlayer;
    delete[] map;
}

void Scene::Update(float delta)
{
    Vector2 input;
    input.x = (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) - (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A));
    input.y = (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) - (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W));

    // if (input.x != 0)
    //     TraceLog(LOG_INFO, TextFormat("Input registered (%f)", input.x));

    scenePlayer->Update(input, delta);
}

void Scene::Draw()
{
    BeginMode2D(sceneCam);
    for (int i = 0; i < mapH * mapW; i++)
    {
        float y = i / mapW;
        float x = i - y * mapW;
        tilemap->DrawTile(map[i], Vector2 {x, y});
    }

    scenePlayer->Draw();
    EndMode2D();
}
