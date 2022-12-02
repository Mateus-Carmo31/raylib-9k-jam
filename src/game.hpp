#ifndef GAME_H_
#define GAME_H_

#include "scene.hpp"
#include "resources.hpp"
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

    // Services
    extern Resources<Texture2D>* textures;
};

#endif // GAME_H_
