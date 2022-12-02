#ifndef SCENE_H_
#define SCENE_H_

#include "tilemap.hpp"
#include "player.hpp"
#include "tween.hpp"
#include "raylib.h"

class Scene
{
public:
    Scene(int width, int height);
    ~Scene();

    void SetTilemap(Tilemap* tilemap);
    const Tilemap* GetTilemap() const;
    void Update(float delta);
    void Draw();

    Player* scenePlayer;

private:
    char* map;
    int mapW, mapH;
    Tilemap* tilemap;
    Tween sceneTween;
    Camera2D sceneCam;
};

inline void Scene::SetTilemap(Tilemap* tilemap)
{
    this->tilemap = tilemap;
    sceneCam.target = {(float) mapW * tilemap->tileSize.x / 2, (float) mapH * tilemap->tileSize.y / 2};
}

inline const Tilemap* Scene::GetTilemap() const
{
    return tilemap;
}

#endif // SCENE_H_
