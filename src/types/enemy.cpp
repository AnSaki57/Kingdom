#include "enemy.hpp"
#include "topcamera.hpp"
#include "../constants.hpp"
#include "../utils.hpp"
#include "raymath.h"

// Initialise static parameters
Texture2D Enemy::sprite;
bool Enemy::isTextureLoaded = false;

/**
 * @brief       Enemy constructor, initialises the ProgressBar as well
 * 
 * @param posn_ Where to put the Enemy at
 */
Enemy::Enemy(Vector2 posn_) : MobileEntity(DefaultHpBar(posn_)) {
    posn = posn_;
    entityType = ENTITY_TYPE_ENEMY;
    hitboxRadius = TILE_SIZE * 0.8;
}

/**
 * @brief           Enemy constructor, initialising the HP bar and level as well
 * 
 * @param posn_     Where to put the Enemy at
 * @param level_    What level of enemy to create
 */
Enemy::Enemy(Vector2 posn_, int level_) : Enemy(posn_) {
    level = level_;

    speed *= GetSpeedMult();
    totalHP *= GetHealthMult();
    currHP *= GetHealthMult();
    // totalHP *= GetHealthMult();
    // currHP *= GetHealthMult();
}

/**
 * @brief   Loads the Sprite as an image, then as a texture after processing it
 */
void Enemy::LoadSprite() {
    if (!isTextureLoaded) {
        Image imgsprite = LoadImage("Zombie.jpg");
        // ImageCrop(&imgsprite, {});
        ImageResize(&imgsprite, ENTITY_SIZE, ENTITY_SIZE);
        sprite = LoadTextureFromImage(imgsprite);
        UnloadImage(imgsprite);

        isTextureLoaded = true;
    }
}

/**
 * @brief   Unloads the static texture of the class
 */
void Enemy::UnloadSprite() {
    UnloadTexture(sprite);
    isTextureLoaded = false;
}

/**
 * @brief                   Updates the location of the Enemy based on where the Player is
 * 
 * [older version]@param entityUpdateStats Information wrapper for anything that a child of Entity may need for its Update function
 */
void Enemy::Update() {
    // Unit vector in direction of Player
    Vector2 moveDir = {entityUpdateStats.playerPosn.x-posn.x, entityUpdateStats.playerPosn.y-posn.y};
    double len = Vector2Length(moveDir);
    moveDir = {float(moveDir.x/len), float(moveDir.y/len)};
    
    // Add some random noise
    int rand = random() % 100;
    if (rand == 0) {
        randDir = Utility::GetRandUnitDir();
    }
    Vector2 netMoveDir = {moveDir.x+randDir.x*0.35, moveDir.y+randDir.y*0.35};
    len = Vector2Length(netMoveDir);
    netMoveDir = {float(netMoveDir.x/len), float(netMoveDir.y/len)};

    // Update position, hpBar
    posn = {float(posn.x+netMoveDir.x*speed), float(posn.y+netMoveDir.y*speed)};
    hpBar.SetPosn({posn.x,float(posn.y-TILE_SIZE/5)});
    hpBar.SetFill(currHP/totalHP);
}

/**
 * @brief   Draws the zombie based on the camera context
 */
void Enemy::Draw(const TopCamera& camera) const {
    if (camera.IsObjOnScreen(GetHitbox())) {
        DrawTexture(sprite, posn.x-camera.posn.x, posn.y-camera.posn.y, WHITE);
        hpBar.Draw(camera);
    }
}

/**
 * @brief               Reaction of the Enemy to a collision with entityType_
 * 
 * @param entityType_   Type of Entity the Enemy collided with
 * 
 * @returns             Response of the Enemy (currently, none)
 */
EntityCollisionResponse Enemy::OnCollision(EntityType entityType_, EntityUpdateStats entityUpdateStats_) { 
    switch (entityType_) {
        case ENTITY_TYPE_NONE:
            break;
        case ENTITY_TYPE_PROJECTILE:
            currHP-=entityUpdateStats.damage;
            entityUpdateStats.damage = 0;
            if (currHP <= 0) {
                return ENTITY_COLL_DESTROY;
            }
            break;
        
        default:
            break;
    }

    return ENTITY_COLL_NONE; 
}