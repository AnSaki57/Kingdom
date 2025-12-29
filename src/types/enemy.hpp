#pragma once

#include "mobileEntity.hpp"

/**
 * Generic Enemy class (for now, a slow zombie)
 * 
 * Responsibilities:
 *  - Owns its sprite as a static member
 *  - Deals with updation, drawing, and collision
 * 
 * Non-responsibilities:
 *  - Actual calling of sprite (un)loaders by the Asset class
 */
class Enemy : public MobileEntity {
    Vector2 randDir = {0,0};
    static Texture2D sprite;
    static bool isTextureLoaded;

public:
    Enemy(Vector2 posn_);
    Enemy(Vector2 posn_, int level_);
    static void LoadSprite();
    static void UnloadSprite();
    void Update() override;
    void Draw(const TopCamera& camera) const override;
    EntityCollisionResponse OnCollision(EntityType entityType_, EntityUpdateStats entityUpdateStats_) override;
};