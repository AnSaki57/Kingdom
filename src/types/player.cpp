#include "player.hpp"
#include "../constants.hpp"
#include <iostream>
#include "wood.hpp"

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

    inventory.Init(1, 10, {(DEFAULT_MONITOR_WIDTH-BOX_SIZE*10)/2, 2000});
    inventory.SetBox(0, 0, std::make_unique<Wood>(inventory.GetPosn(), 5));
}

/**
 * Per-frame updation of the player
 */
void Player::Update() {
    hpBar.setFill(CurrHP/TotalHP);
}

/**
 * @brief   Draws the player at the very centre of the board
*/
void Player::Draw(const TopCamera&) const {
    DrawTexture(sprite, posn.x, posn.y, WHITE);
    hpBar.Draw();
    inventory.Draw();
}