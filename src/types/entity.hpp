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
 * Represents a generic entity on the map
 */
class Entity{
protected:
    Vector2 posn;
    double hitboxRadius = TILE_SIZE/3;
    enum EntityType entityType;
    double totalHP = 100.0;
    double currHP = 80.0;
    int level = 1;

public:
    std::pair<Vector2, double> GetHitbox();
    virtual void Update() = 0;
    virtual void Draw(const TopCamera& camera) const = 0;
    virtual ~Entity() = default;
    virtual void OnCollision() = 0;
};