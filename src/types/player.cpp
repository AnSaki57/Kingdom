#include "player.hpp"
#include "../constants.hpp"
#include <iostream>
#include "wood.hpp"

/**
 * @brief   Constructor for the player class, with its custom, wide hpBar
*/
Player::Player() : MobileEntity(ProgressBar({float(240), float(1920), float(DEFAULT_MONITOR_WIDTH-480), float(15)}, 3, BLUE, RED, BLACK, 0.8)) {
    entityType = ENTITY_TYPE_PLAYER;
    followsCamera = true;
}

/**
 * @brief   Initialiser for the player class, handles texture loading 
*/
void Player::Init() {
    posn = {float(GetMonitorWidth(GetCurrentMonitor())-ENTITY_SIZE)/2, float(GetMonitorHeight(GetCurrentMonitor())-ENTITY_SIZE)/2};

    // Get sprite
    Image imgsprite = LoadImage("Player2.png");
    // ImageCrop(&imgsprite, {});
    ImageResize(&imgsprite, ENTITY_SIZE, ENTITY_SIZE);
    sprite = LoadTextureFromImage(imgsprite);
    UnloadImage(imgsprite);

    inventory.Init(1, 10, {(DEFAULT_MONITOR_WIDTH-BOX_SIZE*10)/2, 2000});
}

/**
 * @brief   Getter for the Player's position
 * 
 * @returns The position of the Player (usually a constant value(?))
 */
Vector2 Player::GetPosn() const { return posn; }

/**
 * @brief   Resource putter through count and type of Resource
 * 
 * @param count         Count of Resource to insert
 * @param resourceType  Type of Resource to insert
 */
void Player::PutResource(int count, ResourceType resourceType) { 
    inventory.PutResource(count, resourceType); 
}

/**
 * @brief   Per-frame updation of the player
 */
void Player::Update(const EntityUpdateStats&) {
    hpBar.SetFill(currHP/totalHP);
}

/**
 * @brief   Draws the player at the very centre of the board
*/
void Player::Draw(const TopCamera&) const {
    DrawTexture(sprite, posn.x, posn.y, WHITE);
    hpBar.Draw();
    inventory.Draw();
}

/**
 * @brief   What the player is meant to do on a collision (as of now, nothing)
 * 
 * @returns Info abt the Player's response to the collision, that the manager might want to know
 */
EntityCollisionResponse Player::OnCollision(EntityType entityType_) { return ENTITY_COLL_NONE; }