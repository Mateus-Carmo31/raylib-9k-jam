#ifndef SCENE_H_
#define SCENE_H_

#include <cmath>
#include "camerarig.hpp"
#include "tween.hpp"
#include "raylib.h"

struct Player
{
    Vector2 pos;
    Vector2 size {1,1}; // Multiplier over tilesize
    float rotation = 0;

    char playerTexId = 'P';
};

struct Object
{
    Vector2 pos;
    Vector2 size {1,1};
    float rotation = 0;

    char texId = 'B';
};

class Scene
{
public:
    Scene(int width, int height);
    virtual ~Scene();

    char GetTile(int x, int y) const;
    void SetTile(int x, int y, char c);
    bool InBounds(Vector2 pos) const;

    virtual void Update(float delta);
    virtual void Draw();

    Player scenePlayer;
    Object exitDoor;

    bool paused = false;
    bool sceneWon = false;

    void StartLevel();
    void FinishLevel();

protected:
    char* map;
    int mapW, mapH;
    Tween sceneTween;
    CameraRig sceneRig;

    // Used to avoid input input being too fast when keys are held
    float inputTimer = 0.2;

    float fade = 0.0;

    void LoadMap(const char *mapFile);
    virtual void HandleMove(Vector2 input, float delta);
};

inline char Scene::GetTile(int x, int y) const
{
    return map[x + y * mapW];
}

inline bool Scene::InBounds(Vector2 pos) const
{
    if (pos.x < 0)
        return false;
    if (pos.y < 0)
        return false;
    if (pos.x > mapW)
        return false;
    if (pos.y > mapH)
        return false;

    return true;
}

#endif // SCENE_H_
