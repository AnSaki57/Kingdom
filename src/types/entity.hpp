#pragma once

#include "raylib.h"
#include "topcamera.hpp"

class Entity{
protected:
    Vector2 posn;
    // Texture2D sprite;
    double hp;
    int level;

public:
    virtual void Draw(TopCamera camera) = 0;
    virtual ~Entity() = default;
};