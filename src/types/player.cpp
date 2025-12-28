#include "player.hpp"
#include <iostream>
#include "wood.hpp"
#include "utils.hpp"

/**
 * @brief   Constructor for the player class, with its custom, wide hpBar
*/
Player::Player() : MobileEntity(ProgressBar({float(240), float(80), float(DEFAULT_MONITOR_WIDTH-480), float(20)}, 1.5, GRAY, RED, BLACK, 0.8)) 
                 , xpBar(ProgressBar({0, DEFAULT_MONITOR_HEIGHT-40, DEFAULT_MONITOR_WIDTH, 20}, 2, WHITE, GREEN, BLACK, 0.2))
{
    entityType = ENTITY_TYPE_PLAYER;
    followsCamera = true;
    entityUpdateStats.damage = 0;

    // For testing only
    /*xp = 3000;
    level = 31;
    totalHP = currHP = BASE_ENTITY_HP * Utility::GetMultiplier(level);*/
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

    inventory.Init(1, 10, {float(DEFAULT_MONITOR_WIDTH-BOX_SIZE*10)/2, 2000});
}

/**
 * @brief   Getter for the Player's position
 * 
 * @returns The position of the Player (usually a constant value(?))
 */
Vector2 Player::GetPosn() const { return posn; }

/**
 * @brief   Getter for whether the Player is alive or not
 * 
 * @returns Liveness of the Player
 */
bool Player::GetLiveness() const { return isAlive; }

/**
 * @brief   Getter for the player's experience points
 * 
 * @returns Player's XP
 */
double Player::GetXP() const { return xp; }

/**
 * @brief       Setter for the player's experience points
 * 
 * @param xp_   What the player's xp is to be set as
 */
void Player::SetXP(double xp_) { xp=xp_; }

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
void Player::Update() {
    if (currHP<=0) isAlive = false;
    // level = int(xp/100)+1;
    if (int(xp/100)+1>level) {
        level = int(xp/100)+1;
        totalHP*=BASE_LEVEL_MULTIPLIER;
        if (level%10==0)
            currHP=totalHP;
    }
    // currHP = GetCurrHP() * GetHealthMult();
    // totalHP = GetTotalHP() * GetHealthMult();
    hpBar.SetFill(currHP/totalHP);
    xpBar.SetFill(double(int(xp)%100)/100);
}

/**
 * @brief   Draws the player at the very centre of the board
*/
void Player::Draw(const TopCamera&) const {
    if (currHP<=0) return;
    DrawTexture(sprite, posn.x, posn.y, WHITE);
    hpBar.Draw();
    xpBar.Draw();
    std::string levelText = "Level " + std::to_string(level);
    DrawText(levelText.c_str(), 10, DEFAULT_MONITOR_HEIGHT-60, 25, BLACK);
    inventory.Draw();
}

/**
 * @brief   What the player is meant to do on a collision (as of now, nothing)
 * 
 * @returns Info abt the Player's response to the collision, that the manager might want to know
 */
EntityCollisionResponse Player::OnCollision(EntityType entityType_, EntityUpdateStats entityUpdateStats_) { 
    switch (entityType_) {
        case ENTITY_TYPE_ENEMY:
            currHP-=entityUpdateStats.damage;
            break;
        
        default:
            break;
    }

    return ENTITY_COLL_NONE; 
}