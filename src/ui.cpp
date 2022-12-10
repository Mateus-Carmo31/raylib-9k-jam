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

void DrawTextCentered(const char* text, int posX, int posY, int fontSize, Color color)
{
    float textSize = MeasureText(text, fontSize);
    DrawText(text, posX - textSize/2, posY - fontSize / 2, fontSize, color);
}

void MainMenu::Draw()
{
    float centerX = cge::renderH / 2;
    float centerY = cge::renderW / 2;

    // Draw Title
    // float textSize = MeasureText("Billy Bob's Adventure", 20);
    // DrawText("Billy Bob's Adventure", centerX - textSize, 20, 20, WHITE);

    // Draw Options
    if (!creditsOpen)
    {
        int top = centerY;
        for (int i = 0; i < 2; i++)
        {
            if (option == i)
                DrawText(TextFormat("> %s", options[i]), 40, top + 20 * i, 10, WHITE);
            else
                DrawText(options[i], 40, top + 20 * i, 10, WHITE);
        }
    }
    else
    {
        // Draw Extras
        DrawTextCentered("Game by Mateus Carmo", centerX, centerY + 15, 10, WHITE);
        DrawTextCentered("Assets by Kenney (@kenney.nl)", centerX, centerY + 35, 10, WHITE);
        DrawTextCentered("Sounds made using rFxGen", centerX, centerY + 65, 10, WHITE);
        DrawTextCentered("Made with Raylib", centerX, centerY + 90, 10, WHITE);
    }

    DrawRectangleV({0}, {(float) cge::renderW, (float) cge::renderH}, ColorFromNormalized({0,0,0,fade}));
}
