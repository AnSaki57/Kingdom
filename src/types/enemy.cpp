#include "enemy.hpp"
#include "topcamera.hpp"
#include "../constants.hpp"
#include "raymath.h"

// Initialise static parameters
Texture2D Enemy::sprite;
bool Enemy::isTextureLoaded = false;

/**
 * @brief       Enemy constructor, initialises the ProgressBar as well
 * 
 * @param posn_ Where to put the Enemy in
 */
Enemy::Enemy(Vector2 posn_) : MobileEntity(DefaultHpBar(posn_)) {
    posn = posn_;
    entityType = ENTITY_TYPE_ENEMY;
    hitboxRadius = TILE_SIZE * 0.8;
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
 * @param entityUpdateStats Information wrapper for anything that a child of Entity may need for its Update function
 */
void Enemy::Update(const EntityUpdateStats& entityUpdateStats) {
    Vector2 moveDir = {entityUpdateStats.playerPosn.x-posn.x, entityUpdateStats.playerPosn.y-posn.y};
    double len = Vector2Length(moveDir);
    moveDir = {float(moveDir.x/len), float(moveDir.y/len)};

    posn = {posn.x+moveDir.x*ENEMY_SPEED, posn.y+moveDir.y*ENEMY_SPEED};
    hpBar.SetPosn({posn.x,posn.y-TILE_SIZE/5});
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
EntityCollisionResponse Enemy::OnCollision(EntityType entityType_) { 
    switch (entityType_) {
        case ENTITY_TYPE_NONE:
            break;
        case ENTITY_TYPE_PROJECTILE:
            return ENTITY_COLL_DESTROY;
        
        default:
            break;
    }

    return ENTITY_COLL_NONE; 
}