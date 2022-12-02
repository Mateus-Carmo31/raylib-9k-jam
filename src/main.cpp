#include <iostream>
#include "scene.hpp"
#include "game.hpp"
#include "raylib.h"
#include "rlgl.h"

#if defined(PLATFORM_WEB)
    #include <emscripten.h>
#endif

RenderTexture renderTex;
Camera2D cam {{(float) cge::renderW/2, (float) cge::renderH/2}, {0}, 0, 3.0};

Sound testSound;

void Draw()
{
    cge::currentScene->Update(GetFrameTime());

    // Draws everything on the render texture
    BeginTextureMode(renderTex);
        ClearBackground(BLACK);

        cge::currentScene->Draw();

        Vector2 mousePos {(float) GetMouseX(), (float) GetMouseY()};
        DrawCircle(mousePos.x * ((float) cge::renderW / cge::screenW), mousePos.y * ((float) cge::renderH / cge::screenH), 15, WHITE);

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

    cge::currentScene = new Scene {16, 16};

    Tilemap testmap {"./assets/textures/kenney_tinydungeon/Tilemap/tilemap_packed.png", {16, 16}};
    testmap.RegisterTile(0, {1, 5});
    cge::currentScene->SetTilemap(&testmap);

    cge::playerTex = LoadTexture("./assets/textures/kenney_tinydungeon/Tiles/tile_0097.png");

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

    delete cge::currentScene;
    UnloadTexture(cge::playerTex);
    UnloadRenderTexture(renderTex);
    CloseWindow();

    return 0;
}
