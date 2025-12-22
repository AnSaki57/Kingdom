#pragma once

#include "raylib.h"
#include "../constants.hpp"
#define CAMERA_SPEED 8 * SCALING_FACTOR
#define CAMERA_SPEED_MULTIPLIER 10.0

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

    Vector2 GetPosn() const;

    void MotionCapture();
    bool IsObjOnScreen(Rectangle objShape) const;
    bool IsObjOnScreen(std::pair<Vector2, double> objShape) const;
};