#ifndef SCENE_H_
#define SCENE_H_

#include <cmath>
#include "player.hpp"
#include "camerarig.hpp"
#include "tween.hpp"
#include "raylib.h"

class Scene
{
public:
    Scene(int width, int height);
    ~Scene();

    Vector2 ToTileSpace(Vector2 worldPos) const;
    Vector2 ToWorldPos(Vector2 tilePos) const;

    void LoadMap(const char *mapFile);

    char GetTile(int x, int y) const;
    void SetTile(int x, int y, char c);

    virtual void Update(float delta);
    virtual void Draw();

    Player scenePlayer;

private:
    char* map;
    int mapW, mapH;
    Tween sceneTween;
    CameraRig sceneRig;

    // Used to avoid input input being too fast when keys are held
    float inputTimer;

    virtual void HandleMove(Vector2 input, float delta);
};

inline char Scene::GetTile(int x, int y) const
{
    return map[x + y * mapW];
}

#endif // SCENE_H_
