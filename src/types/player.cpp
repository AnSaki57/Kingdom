#include "player.hpp"
#include <iostream>
#include "../constants.hpp"

/**
 * @brief   Constructor for the player class
*/
Player::Player() : hpBar({float(240), float(1920), float(DEFAULT_MONITOR_WIDTH-480), float(15)}, 3, BLUE, RED, BLACK, 0.8) {}

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

void Player::Update() {
    // hpBar.setFill(hpBar.getFill()-0.0003);
    // if (IsKeyDown(KEY_H)) hpBar.setFill(hpBar.getFill()+0.003);
    // if (IsKeyDown(KEY_L)) hpBar.setFill(hpBar.getFill()-0.007);
}

/**
 * @brief   Draws the player at the very centre of the board
*/
void Player::Draw(const TopCamera&) const {
    DrawTexture(sprite, posn.x, posn.y, WHITE);
    hpBar.Draw();
}