#include <iostream>
#include "scenes.hpp"
#include "ui.hpp"
#include "game.hpp"
#include "raylib.h"
#include "rlgl.h"

#if defined(PLATFORM_WEB)
    #include <emscripten.h>
#endif

MainMenu mainMenu;
RenderTexture renderTex;

float totalTime = 0.0;

void UpdateAndDraw()
{
    if (cge::currentScene < 0)
    {
        mainMenu.Update(GetFrameTime());
    }
    else if (cge::currentScene < sizeof cge::scenes / sizeof cge::scenes[0])
    {
        cge::scenes[cge::currentScene]->Update(GetFrameTime());

        if (cge::scenes[cge::currentScene]->sceneWon)
        {
            TraceLog(LOG_INFO, "Switching scene...");
            cge::currentScene++;
        }
    }

    totalTime += GetFrameTime();
    if (totalTime >= cge::renderW)
        totalTime = 0;

    // Draws everything on the render texture
    BeginTextureMode(renderTex);
        ClearBackground(BLACK);

        DrawTextureEx(cge::bg, {-totalTime, 0}, 0, 2, Color {51,51,51,255});
        DrawTextureEx(cge::bg, {-totalTime + cge::renderW, 0}, 0, 2, Color {51,51,51,255});

        if (cge::currentScene < 0)
            mainMenu.Draw();
        else if (cge::currentScene < sizeof cge::scenes / sizeof cge::scenes[0])
            cge::scenes[cge::currentScene]->Draw();
        else
            DrawThankYouScreen();

        // DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 8, WHITE);

    EndTextureMode();

    // Draws the render texture
    BeginDrawing();
        DrawTexturePro(renderTex.texture,
                       {0,0,(float) renderTex.texture.width, (float) -renderTex.texture.height},
                       {0,0, (float) cge::screenW, (float) cge::screenH},
                       {0,0}, 0, WHITE);
    EndDrawing();
}

int main()
{
    InitWindow(cge::screenW, cge::screenH, "Billy Bob");

    InitAudioDevice();

    renderTex = LoadRenderTexture(cge::renderW, cge::renderH);
    // SetTextureWrap(renderTex.texture, TEXTURE_WRAP_REPEAT);
    // SetTextureFilter(renderTex.texture, TEXTURE_FILTER_BILINEAR);

    cge::LoadTilemap("./assets/textures/colored-transparent_packed.png", 16, 16);
    cge::RegisterTiles();

    cge::LoadSFX();
    cge::LoadTextures();

    cge::scenes[0] = new LevelScene {10, 7, "./assets/maps/scene1.map"};
    cge::scenes[1] = new SwitchScene {9, 6, "./assets/maps/scene2.map"};
    cge::scenes[2] = new MoveTogetherScene {10, 6, "./assets/maps/scene3.map"};
    cge::scenes[3] = new RotatingScene {10, 10, "./assets/maps/scene4.map"};
    cge::scenes[4] = new LevelMoveScene {11, 11, "./assets/maps/scene5.map"};
    cge::scenes[5] = new ObjectsScene {7, 8, "./assets/maps/scene6.map"};
    cge::scenes[6] = new LargeBillyScene {11, 11, "./assets/maps/scene7.map"};
    cge::scenes[7] = new RotatingScene2 {11, 11, "./assets/maps/scene8.map"};
    cge::scenes[8] = new FinalScene {16, 16, "./assets/maps/scene9.map"};

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

    for (int i = 0; i < sizeof cge::scenes / sizeof cge::scenes[0]; i++)
    {
        delete cge::scenes[i];
    }

    StopSoundMulti();
    cge::UnloadSFX();
    CloseAudioDevice();

    cge::UnloadTilemap();
    cge::UnloadTextures();
    UnloadRenderTexture(renderTex);
    CloseWindow();

    return 0;
}
