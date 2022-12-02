#include "player.hpp"
#include "game.hpp"
#include "raylib.h"

void Player::Update(Vector2 input, float delta)
{
    pos.x += input.x * cge::playerSpeed * delta;
    pos.y += input.y * cge::playerSpeed * delta;
}

void Player::Draw()
{
    DrawTexturePro(cge::playerTex,
                   {0, 0, 16, 16},
                   {pos.x, pos.y, 16, 16},
                   {8, 8}, 0, WHITE);
}
