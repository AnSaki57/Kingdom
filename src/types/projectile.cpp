#include "projectile.hpp"
#include "topcamera.hpp"
#include <iostream>

#define GREY_ {160, 160, 160, 255}

/**
 * @brief           Constructor for Projector, initialises its posn and velocity
 * 
 * @param posn_     Desired initial position of Projectile
 * @param velocity_ Desired velocity of projectile
 */
Projectile::Projectile(Vector2 posn_, Vector2 velocity_) : MobileEntity(ProgressBar({}, 0.0, {}, {}, {}, 0.0)) {
    posn = posn_;
    velocity = velocity_;
    entityType = ENTITY_TYPE_PROJECTILE;
    hitboxRadius = PROJECTILE_SIZE;
}

/**
 * @brief   Frame-by-frame updation of the Projectile's position (EntityUpdateStats not used)
 */
void Projectile::Update(const EntityUpdateStats&) {
    posn.x += velocity.x;
    posn.y += velocity.y;
    lifetime--;
}

/**
 * @brief           Draws the Projectile
 * 
 * @param camera    Provides the drawing context for the Projectile
 */
void Projectile::Draw(const TopCamera& camera) const {
    DrawCircle(posn.x-camera.posn.x, posn.y-camera.posn.y, PROJECTILE_SIZE, GREY_);
    DrawCircleLines(posn.x-camera.posn.x, posn.y-camera.posn.y, PROJECTILE_SIZE, BLACK);
}

/**
 * @brief               Describes the behaviour of the object on collision with another Entity
 * 
 * @param entityType_   Type of Entity this object collided with
 */
EntityCollisionResponse Projectile::OnCollision(EntityType entityType_) { 
    if (entityType_ == entityType || entityType_ == ENTITY_TYPE_PLAYER) return ENTITY_COLL_NONE;
    return ENTITY_COLL_DESTROY;
}