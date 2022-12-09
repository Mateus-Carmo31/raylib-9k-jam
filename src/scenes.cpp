#include "scenes.hpp"
#include <cmath>

void Scene3::HandleMove(Vector2 input, float delta)
{
    if (inputTimer == 0)
    {
        if (input.x != 0 || input.y != 0)
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
}

void Scene4::HandleMove(Vector2 input, float delta)
{
    if (inputTimer == 0 && input.x != 0)
    {
        if (input.x > 0.0)
        {
            currentRot += 90;
            currentFacing = { currentFacing.y, -currentFacing.x };
        }
        else if (input.x < 0.0)
        {
            currentRot -= 90;
            currentFacing = { -currentFacing.y, currentFacing.x };
        }

        Vector2 newPos = scenePlayer.pos;
        while (InBounds(newPos) && GetTile(newPos.x, newPos.y) != cge::WALL)
        {
            newPos.x += currentFacing.x;
            newPos.y += currentFacing.y;
        }

        newPos = {newPos.x - currentFacing.x, newPos.y - currentFacing.y};

        sceneTween.InterpolateValue(sceneRig.cam.rotation, sceneRig.cam.rotation, currentRot, 0.5);
        sceneTween.InterpolateValue(scenePlayer.pos, scenePlayer.pos, newPos, 0.5);

        TraceLog(LOG_INFO, "Rotating... [%f]", currentRot);
        inputTimer = 0.6;
    }
}

void DrawThankYouScreen()
{
    DrawText("Thank you for Playing!", 0, cge::renderH/2, 10, WHITE);
}
