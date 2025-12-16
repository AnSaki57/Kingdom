#include "player.hpp"
#include "../constants.hpp"

Player::Player() {}

void Player::Init() {
    hp = 100;
    level = 1;
    posn = {float(GetMonitorWidth(GetCurrentMonitor()))/2, float(GetMonitorHeight(GetCurrentMonitor()))/2};

    // Get sprite
    Image imgsprite = LoadImage("Player2.png");
    // ImageCrop(&imgsprite, {});
    ImageResize(&imgsprite, TILE_SIZE, TILE_SIZE);
    sprite = LoadTextureFromImage(imgsprite);
    UnloadImage(imgsprite);
}

void Player::Draw(const TopCamera&) const {
    DrawTexture(sprite, posn.x, posn.y, WHITE);
}