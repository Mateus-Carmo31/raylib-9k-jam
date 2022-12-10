#include "ui.hpp"
#include "game.hpp"
#include "raylib.h"

void MainMenu::Update(float delta)
{
    if (!creditsOpen)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            if (option == 0 && !transitionTween.isActive())
                transitionTween.InterpolateValue(
                    fade,
                    0.0f,
                    1.0f,
                    1.0f,
                    []() { cge::currentScene = 0; });
            if (option == 1)
                creditsOpen = true;
        }

        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
            option += 1;
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
            option -= 1;

        if (option < 0)
            option = 1;
        if (option > 1)
            option = 0;
    }
    else
        if (IsKeyPressed(KEY_SPACE))
            creditsOpen = false;

    transitionTween.UpdateTweens(delta);
}

void MainMenu::Draw()
{
    float centerX = cge::renderH / 2;
    float centerY = cge::renderW / 2;

    // Draw Title
    // float textSize = MeasureText("Billy Bob's Adventure", 20);
    // DrawText("Billy Bob's Adventure", centerX - textSize, 20, 20, WHITE);
    DrawTextureEx(cge::logo, {centerX - 73, centerY - 26 - 50}, 0, 2, WHITE);
    cge::DrawTileCentered('P', {3,3});

    // Draw Options
    if (!creditsOpen)
    {
        int top = centerY;
        for (int i = 0; i < 2; i++)
        {
            if (option == i)
                DrawText(TextFormat("> %s", options[i]), 40, top + 20 * i, 10, cge::white);
            else
                DrawText(options[i], 40, top + 20 * i, 10, cge::white);
        }
    }
    else
    {
        // Draw Extras
        cge::DrawTextCentered("Game by Mateus Carmo", centerX, centerY + 15, 10, cge::white);
        cge::DrawTextCentered("Assets by Kenney (@kenney.nl)", centerX, centerY + 35, 10, cge::white);
        cge::DrawTextCentered("Sounds made using rFxGen", centerX, centerY + 65, 10, cge::white);
        cge::DrawTextCentered("Made with Raylib", centerX, centerY + 90, 10, cge::white);
        cge::DrawTextCentered("(Press SPACE to return)", centerX, centerY + 110, 5, cge::white);
    }

    DrawRectangleV({0}, {(float) cge::renderW, (float) cge::renderH}, ColorFromNormalized({0,0,0,fade}));
}
