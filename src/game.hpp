#ifndef GAME_H_
#define GAME_H_

#include "scene.hpp"
#include "raylib.h"

namespace cge
{
    // Game-wise values
    extern int screenW, screenH;
    extern int renderW, renderH;

    extern float playerSpeed;
    extern Texture2D playerTex;

    // Globals
    extern Scene* currentScene;
};

#endif // GAME_H_
