#include <iostream>
#include "scene.hpp"
#include "scenes.hpp"
#include "game.hpp"
#include "raylib.h"
#include "rlgl.h"

#if defined(PLATFORM_WEB)
    #include <emscripten.h>
#endif

RenderTexture renderTex;

Sound testSound;

void Draw()
{
    if (cge::currentScene < sizeof cge::scenes / sizeof cge::scenes[0])
    {
        cge::scenes[cge::currentScene]->Update(GetFrameTime());

        if (cge::scenes[cge::currentScene]->sceneWon)
        {
            TraceLog(LOG_INFO, "Switching scene...");
            cge::currentScene++;
        }
    }

    // Draws everything on the render texture
    BeginTextureMode(renderTex);
        ClearBackground(BLACK);

        if (cge::currentScene < sizeof cge::scenes / sizeof cge::scenes[0])
            cge::scenes[cge::currentScene]->Draw();
        else
            DrawThankYouScreen();

        DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 8, WHITE);

    EndTextureMode();

    // Draws the render texture
    BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(renderTex.texture,
                       {0,0,(float) renderTex.texture.width, (float) -renderTex.texture.height},
                       {0,0, (float) cge::screenW, (float) cge::screenH},
                       {0,0}, 0, WHITE);
    EndDrawing();
}

void UpdateAndDraw()
{
    Draw();
}

int main()
{
    InitWindow(cge::screenW, cge::screenH, "Testing");

    InitAudioDevice();

    testSound = LoadSound("./assets/audio/fail_shot.ogg");
    renderTex = LoadRenderTexture(cge::renderW, cge::renderH);
    // SetTextureWrap(renderTex.texture, TEXTURE_WRAP_REPEAT);
    // SetTextureFilter(renderTex.texture, TEXTURE_FILTER_BILINEAR);

    cge::LoadTilemap("./assets/textures/colored-transparent_packed.png", 16, 16);
    cge::RegisterTiles();

    cge::scenes[0] = new Scene1 {10, 10};
    cge::scenes[1] = new Scene2 {10, 10};
    cge::scenes[2] = new Scene3 {10, 10};

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateAndDraw, 0, 1);
#else
    SetTargetFPS(60);
    // SetConfigFlags(FLAG_VSYNC_HINT);
    while (!WindowShouldClose())
    {
        UpdateAndDraw();
    }
#endif

    StopSoundMulti();
    UnloadSound(testSound);
    CloseAudioDevice();

    for (int i = 0; i < sizeof cge::scenes / sizeof cge::scenes[0]; i++)
    {
        delete cge::scenes[i];
    }

    cge::UnloadTilemap();
    UnloadRenderTexture(renderTex);
    CloseWindow();

    return 0;
}
