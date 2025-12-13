#pragma once

#include "raylib.h"
#include "../constants.hpp"
#define CAMERA_SPEED 8 * SCALING_FACTOR

class TopCamera{
public:
    Vector2 posn;
    double speed;
    double zoom;    // For later

    TopCamera();
    void Init();

    void Move();
    bool isObjOnScreen(Vector2 objPosn) const;
};