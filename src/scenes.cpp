#include "scenes.hpp"
#include "raylib.h"
#include <cmath>

void MoveTogetherScene::HandleMove(Vector2 input, float delta)
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
            cge::PlayStepSound();
        }
    }
}

void RotatingScene::HandleMove(Vector2 input, float delta)
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

        sceneTween.InterpolateValue(sceneRig.cam.rotation, sceneRig.cam.rotation, currentRot, 0.4);
        sceneTween.InterpolateValue(scenePlayer.pos, scenePlayer.pos, newPos, 0.5);
        sceneRig.SetTrauma(0.2);
        PlaySound(cge::shiftSound);

        // TraceLog(LOG_INFO, "Rotating... [%f]", currentRot);
        inputTimer = 0.6;
    }
}

void LevelMoveScene::HandleMove(Vector2 input, float delta)
{
    input.x = -input.x;
    input.y = -input.y;
    if (input.x != 0 || input.y != 0)
    {
        if (inputTimer == 0)
        {
            float nPosX = scenePlayer.pos.x + input.x;
            float nPosY = scenePlayer.pos.y + input.y;

            char destTile = GetTile(nPosX, nPosY);

            // Change this for a better collision detection!
            if (destTile == cge::WALL)
            {
                sceneRig.SetTrauma(0.15);
                inputTimer = 0.2;
                return;
            }
            else
            {
                sceneTween.InterpolateValue(scenePlayer.pos, scenePlayer.pos, Vector2 {nPosX, nPosY}, 0.15f);
                sceneTween.InterpolateValue(
                    sceneRig.cam.target,
                    sceneRig.cam.target,
                    Vector2 {
                    sceneRig.cam.target.x + input.x * cge::tileSize.x,
                    sceneRig.cam.target.y + input.y * cge::tileSize.y}, 0.15f);
                inputTimer = 0.2;
                PlaySound(cge::shiftSound);
            }
        }
    }
}

void LargeBillyScene::HandleMove(Vector2 input, float delta)
{
    if (input.x != 0 || input.y != 0)
    {
        if (inputTimer == 0)
        {
            if (firstMove)
            {
                scenePlayer.pos.x = mapW / 2 + 10 * -input.x;
                scenePlayer.pos.y = mapH / 2 + 10 * -input.y;
                firstMove = false;
            }

            float nPosX = scenePlayer.pos.x + input.x;
            float nPosY = scenePlayer.pos.y + input.y;

            for (int y = -scenePlayer.size.y / 2 ; y < scenePlayer.size.y/2; y++)
            {
                for (int x = -scenePlayer.size.x / 2; x < scenePlayer.size.x/2; x++)
                {
                    if (InBounds({(float) nPosX + x, (float) nPosY + y}))
                    {
                        char destTile = GetTile(nPosX + x, nPosY + y);
                        if (destTile == cge::WALL)
                        {
                            SetTile(nPosX + x, nPosY + y, cge::GROUND);
                            sceneRig.SetTrauma(0.2);
                        }
                    }
                }
            }

            sceneTween.InterpolateValue<Vector2>(scenePlayer.pos, scenePlayer.pos, Vector2 {nPosX, nPosY}, 0.15f);
            PlaySound(cge::bigStepSound);
            inputTimer = 0.2;
        }
    }
}

void FinalScene::Draw()
{
    BeginMode2D(sceneRig.cam);
    cge::DrawTileCentered(exitDoor.texId, exitDoor.pos);
    cge::DrawTileCentered(scenePlayer.playerTexId, scenePlayer.pos, scenePlayer.rotation, scenePlayer.size);
    EndMode2D();

    float centerX = cge::renderH / 2;
    float centerY = cge::renderW / 2;

    DrawTextureEx(cge::logo, {centerX - 73, centerY - 26 - 50}, 0, 2, WHITE);
    DrawText("START", 40, centerY, 10, cge::white);
    DrawText("CREDITS", 40, centerY + 20, 10, cge::white);

    // TraceLog(LOG_INFO, "Pos: %f %f", scenePlayer.pos.x, scenePlayer.pos.y);

    DrawRectangleRec({0, 0, (float) cge::renderW, (float) cge::renderH}, ColorFromNormalized({0,0,0,fade}));
}

// void Scene7::Update(float delta)
// {
//     LevelScene::HandleMove(Vector2 input, float delta)
// }

// void Scene7::Draw()
// {
//     // Fetch all walls that need to be drawn
//     std::vector<Vector3> blocks;
//     for (int i = 0; i < mapW * mapH; i++)
//     {
//         if (map[i] == cge::WALL)
//         {
//             int y = i / mapW;
//             int x = i - y * mapW;
//             blocks.push_back(Vector3 {(float) x, (float) y, 0});
//         }
//     }

//     // Sort them by distance to camera (painter's algorithm)
//     // This lambda returns true if vec1 is the closest to the camera, false otherwise
//     auto sortFunc = [this](Vector3& vec1, Vector3& vec2) {
//         float dist1 = powf((vec1.x - this->cam.position.x), 2) + powf((vec1.y - this->cam.position.y), 2);
//         float dist2 = powf((vec2.x - this->cam.position.x), 2) + powf((vec2.y - this->cam.position.y), 2);
//         if (dist1 < dist2)
//         {
//             vec2.z = vec1.z + 1;
//             return true;
//         }
//         else
//         {
//             vec1.z = vec2.z + 1;
//             return false;
//         }
//     };

//     std::sort(blocks.begin(), blocks.end(), sortFunc);

//     BeginMode3D(cam);
//     for (Vector3& block : blocks)
//     {
//         Color col = {(unsigned char) (255 - block.z)};
//         col.a = 255;
//         DrawCube(Vector3 {block.x * cge::tileSize.x / 2 + cge::tileSize.x / 4, 0, block.y * cge::tileSize.y / 2 + cge::tileSize.y / 4}, cge::tileSize.x/2, cge::tileSize.y/2, cge::tileSize.x/2, col);
//     }
//     EndMode3D();
// }

// void Scene7::HandleMove(Vector2 input, float delta)
// {
//     float x = input.x;
//     input.x = 0;
//     LevelScene::HandleMove(input, delta);
//     cam.position.x = scenePlayer.pos.x * cge::tileSize.x / 2 + cge::tileSize.x / 4;
//     cam.position.z = scenePlayer.pos.y * cge::tileSize.y / 2 + cge::tileSize.y / 4;
//     cam.target.x = cam.position.x + facing.x * cge::tileSize.x/2;
//     cam.target.z = cam.position.z + facing.y * cge::tileSize.y/2;
// }

void DrawThankYouScreen()
{
    cge::DrawTextCentered("And so, Billy Bob went home,", cge::renderW/2, 50, 10, cge::white);
    cge::DrawTextCentered("Deeply unsettled by his perception", cge::renderW/2, 70, 10, cge::white);
    cge::DrawTextCentered("of reality being shattered.", cge::renderW/2, 90, 10, cge::white);
    cge::DrawTextCentered("Thank you for playing!", cge::renderW/2, 120, 20, cge::white);
}
