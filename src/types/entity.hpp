#pragma once

#include "raylib.h"
#include "../constants.hpp"
#include "progressBar.hpp"

class TopCamera;

/**
 * Represents the type of Entitys present in the game (stationary and mobile)
 */
enum EntityType {
    ENTITY_TYPE_NONE,
    // Stationary
    ENTITY_TYPE_TREE,
    ENTITY_TYPE_BOULDER,
    // Mobile
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_ENEMY,
    ENTITY_TYPE_PROJECTILE
};

/**
 * What must be done to an Entity by the manager, as per the Entity's collision outcome
 */
enum EntityCollisionResponse {
    ENTITY_COLL_NONE,
    ENTITY_COLL_DESTROY
};

/**
 * Full set of Update statistics that an Entity child may ever need for its own Update()
 */
struct EntityUpdateStats {
    Vector2 playerPosn;
};

/**
 * Represents a generic entity on the map
 * 
 * Responsibilities:
 *  - Holds the default values of hitboxes, hp, and level
 *  - Implements the getter for hitboxes
 */
class Entity{
protected:
    // Texture2D sprite;
    ProgressBar hpBar;
    Vector2 posn;
    double hitboxRadius = TILE_SIZE/3;
    double totalHP = 100.0;
    double currHP = 100.0;
    int level = 1;
    
public:
    enum EntityType entityType = ENTITY_TYPE_NONE;
    bool followsCamera = false;
    Entity(ProgressBar hpBar_);
    std::pair<Vector2, double> GetHitbox() const;
    virtual void Update(const EntityUpdateStats& entityUpdateStats) = 0;
    virtual void Draw(const TopCamera& camera) const = 0;
    virtual ~Entity() = default;
    virtual EntityCollisionResponse OnCollision(EntityType entityType_) = 0;
};

inline ProgressBar DefaultHpBar(Vector2 posn_) {
    return ProgressBar({posn_.x, posn_.y-float(ENTITY_SIZE)/5, float(ENTITY_SIZE), float(ENTITY_SIZE)/8}, 1, BLUE, RED, BLACK, 0.5);
}