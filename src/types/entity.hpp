#pragma once

#include "raylib.h"
#include "../constants.hpp"

class TopCamera;

/**
 * Represents the type of Entitys present in the game (stationary and mobile)
 */
enum EntityType {
    tree,
    boulder,
    player,
    enemy
};

/**
 * What must be done to an Entity by the manager, as per the Entity's collision outcome
 */
enum EntityCollisionResponse {
    none,
    destroy
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
    Vector2 posn;
    double hitboxRadius = TILE_SIZE/3;
    double totalHP = 100.0;
    double currHP = 80.0;
    int level = 1;
    
public:
    enum EntityType entityType;
    bool followsCamera = false;
    std::pair<Vector2, double> GetHitbox();
    virtual void Update() = 0;
    virtual void Draw(const TopCamera& camera) const = 0;
    virtual ~Entity() = default;
    virtual EntityCollisionResponse OnCollision(EntityType entityType_) = 0;
};