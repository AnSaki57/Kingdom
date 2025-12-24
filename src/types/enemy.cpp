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
Enemy::Enemy(Vector2 posn_) : MobileEntity(ProgressBar({}, 1, BLUE, RED, BLACK, 0.5)) {
    posn = posn_;
    entityType = ENTITY_TYPE_ENEMY;
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
}

/**
 * @brief   Draws the zombie based on the camera context
 */
void Enemy::Draw(const TopCamera& camera) const {
    if (camera.IsObjOnScreen(GetHitbox())) {
        DrawTexture(sprite, posn.x-camera.posn.x, posn.y-camera.posn.y, WHITE);
    }
}

EntityCollisionResponse Enemy::OnCollision(EntityType entityType_) { return ENTITY_COLL_NONE; }