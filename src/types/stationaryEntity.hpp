#pragma once

#include "raylib.h"
#include "entity.hpp"

class StationaryEntity : public Entity {
public:
    virtual void SetPosn(Vector2 posn_) = 0;
};