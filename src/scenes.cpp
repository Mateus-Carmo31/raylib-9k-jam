#include "scenes.hpp"

void Scene3::HandleMove(Vector2 input, float delta)
{
    if (input.x != 0 || input.y != 0)
    {
        if (inputTimer == 0)
        {
            // Move player
            float nPosX = scenePlayer.pos.x + input.x;
            float nPosY = scenePlayer.pos.y + input.y;

            char destTile = GetTile(nPosX, nPosY);

            if (destTile == cge::WALL)
            {
                sceneRig.ApplyTrauma(0.15);
                inputTimer = 0.2;
            }
            else
            {
                sceneTween.InterpolateValue<Vector2>(scenePlayer.pos, scenePlayer.pos, Vector2 {nPosX, nPosY}, 0.15f);
                inputTimer = 0.2;
            }

            // Move door
            nPosX = exitDoor.pos.x + input.x;
            nPosY = exitDoor.pos.y + input.y;

            destTile = GetTile(nPosX, nPosY);

            if (destTile != cge::WALL)
            {
                sceneTween.InterpolateValue<Vector2>(exitDoor.pos, exitDoor.pos, Vector2 {nPosX, nPosY}, 0.15f);
            }
        }
    }
    else
    {
        inputTimer = 0;
    }
}

void DrawThankYouScreen()
{
    DrawText("Thank you for Playing!", 0, cge::renderH/2, 10, WHITE);
}
