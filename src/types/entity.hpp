#pragma once

#include "raylib.h"

class TopCamera;

class Entity{
protected:
    Vector2 posn;
    double hp = 100.0;
    int level = 1;

public:
    virtual void Draw(const TopCamera& camera) const = 0;
    virtual ~Entity() = default;
};