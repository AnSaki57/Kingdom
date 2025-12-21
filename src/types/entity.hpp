#pragma once

#include "raylib.h"

class TopCamera;

/**
 * Represents a generic entity on the map
 */
class Entity{
protected:
    Vector2 posn;
    double totalHP = 100.0;
    double currHP = 80.0;
    int level = 1;

public:
    virtual void Draw(const TopCamera& camera) const = 0;
    virtual ~Entity() = default;
};