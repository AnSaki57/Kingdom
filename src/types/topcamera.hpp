#pragma once

#include "raylib.h"
#include "../constants.hpp"
#define CAMERA_SPEED 8 * SCALING_FACTOR

/**
 * Represents the top-view camera above the Player
*/
class TopCamera{
public:
    Vector2 posn;
    double speed;
    double zoom;    // For later

    TopCamera();
    void Init();

    void MotionCapture();
    bool isObjOnScreen(Vector2 objPosn) const;
};