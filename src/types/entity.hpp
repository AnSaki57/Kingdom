#pragma once

#include "raylib.h"
#include "topcamera.hpp"

class Entity{
protected:
    Vector2 posn;
    double hp;
    int level;

public:
    virtual void Draw(const TopCamera& camera) = 0;
    virtual ~Entity() = default;
};