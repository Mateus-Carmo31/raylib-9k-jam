#ifndef SCENES_H_
#define SCENES_H_

#include "scene.hpp"
#include "game.hpp"

// Scene 1: nothing different
class Scene1 : public Scene
{
public:
    Scene1(int width, int height) : Scene {width, height}
    {
        LoadMap("./assets/maps/scene1.map");
        exitDoor.texId = cge::DOOR;
    }
};

// Scene 2: the door moves instead of the player
class Scene2 : public Scene
{
public:
    Scene2(int width, int height) : Scene {width, height}
    {
        LoadMap("./assets/maps/scene1.map");
        scenePlayer.playerTexId = cge::DOOR;
        exitDoor.texId = cge::PLAYER;
    }
};

// Scene 3: the player and the door move together
class Scene3 : public Scene
{
public:
    Scene3(int width, int height) : Scene {width, height}
    {
        LoadMap("./assets/maps/scene1.map");
        exitDoor.texId = cge::DOOR;
    }

    virtual void HandleMove(Vector2 input, float delta) override;
};

// Scene 4: the player rotates the entire room
class Scene4 : public Scene
{
public:
    Scene4(int width, int height) : Scene {width, height}
    {
        LoadMap("./assets/maps/scene1.map");
        exitDoor.texId = cge::DOOR;
    }

    float currentRot = 0;
    Vector2 currentFacing = {0,1};

    virtual void HandleMove(Vector2 input, float delta) override;
};

void DrawThankYouScreen();

#endif // SCENES_H_
