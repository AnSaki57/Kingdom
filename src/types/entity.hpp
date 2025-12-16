#pragma once

#include "raylib.h"

class TopCamera;

class Entity{
protected:
    Vector2 posn;
    double hp;
    int level;

public:
    virtual void Draw(const TopCamera& camera) const = 0;
    virtual ~Entity() = default;
};