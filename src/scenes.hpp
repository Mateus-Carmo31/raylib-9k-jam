#ifndef SCENES_H_
#define SCENES_H_

#include "scene.hpp"
#include "game.hpp"

// Scene 1: nothing different

// Scene 2: the door moves instead of the player
class SwitchScene : public LevelScene
{
public:
    SwitchScene(int width, int height, const char* mapFile) : LevelScene {width, height, mapFile}
    {
        exitDoor.texId = cge::PLAYER;
        scenePlayer.playerTexId = cge::DOOR;
    }
};

// Scene 3: the player and the door move together
class MoveTogetherScene : public LevelScene
{
public:
    MoveTogetherScene(int width, int height, const char* mapFile) : LevelScene {width, height, mapFile} {}

    virtual void HandleMove(Vector2 input, float delta) override;
};

// Scene 4: the player rotates the entire room
class RotatingScene : public LevelScene
{
public:
    RotatingScene(int width, int height, const char* mapFile) : LevelScene {width, height, mapFile} {}

    float currentRot = 0;
    Vector2 currentFacing = {0,1};

    virtual void HandleMove(Vector2 input, float delta) override;
};

// Scene 5: the player is a box
class ObjectsScene : public LevelScene
{
public:
    ObjectsScene(int width, int height, const char* mapFile) : LevelScene {width, height, mapFile}
    {
        scenePlayer.playerTexId = cge::BOX;
        objects.push_back( Object { {3,5}, {1,1}, 0, 'P'} );
    }
};

// Scene 6: the "map" moves (the camera moves)
class LevelMoveScene : public LevelScene
{
public:
    LevelMoveScene(int width, int height, const char* mapFile) : LevelScene {width, height, mapFile} {}

    virtual void HandleMove(Vector2 input, float delta) override;
};

class LargeBillyScene : public LevelScene
{
public:
    LargeBillyScene(int width, int height, const char* mapFile) : LevelScene {width, height, mapFile}
    {
        scenePlayer.pos = {-100, -100};
        scenePlayer.size = {5,5};
    }

    bool firstMove = true;
    virtual void HandleMove(Vector2 input, float delta) override;
};

class RotatingScene2 : public RotatingScene
{
public:
    RotatingScene2(int width, int height, const char* mapFile) : RotatingScene {width, height, mapFile}
    {
        scenePlayer.playerTexId = cge::DOOR;
        exitDoor.texId = cge::PLAYER;
    }
};

class FinalScene : public LevelScene
{
public:
    FinalScene(int width, int height, const char* mapFile) : LevelScene {width, height, mapFile} {}

    virtual void Draw() override;
};

// class Scene7 : public LevelScene
// {
// public:
//     Scene7(int width, int height, const char* mapFile) : LevelScene {width, height, mapFile}
//     {
//         cam.position = {0,0,0};
//         cam.target = {0, 0, 0};
//         cam.up = {0,1,0};
//         cam.fovy = 60;
//     }

//     Vector2 facing {-1,0};
//     Camera3D cam;

//     // virtual void Update(float delta) override;
//     virtual void Draw() override;
//     virtual void HandleMove(Vector2 input, float delta) override;
// };

void DrawThankYouScreen();

#endif // SCENES_H_
