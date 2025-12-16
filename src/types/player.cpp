#include "player.hpp"
#include "../constants.hpp"

/**
 * @brief   Constructor for the player class
*/
Player::Player() {}

/**
 * @brief   Initialiser for the player class, handles texture loading 
*/
void Player::Init() {
    posn = {float(GetMonitorWidth(GetCurrentMonitor()))/2, float(GetMonitorHeight(GetCurrentMonitor()))/2};

    // Get sprite
    Image imgsprite = LoadImage("Player2.png");
    // ImageCrop(&imgsprite, {});
    ImageResize(&imgsprite, TILE_SIZE, TILE_SIZE);
    sprite = LoadTextureFromImage(imgsprite);
    UnloadImage(imgsprite);
}

/**
 * @brief   Draws the player at the very centre of the board
*/
void Player::Draw(const TopCamera&) const {
    DrawTexture(sprite, posn.x, posn.y, WHITE);
}