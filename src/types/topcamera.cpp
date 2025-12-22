#include "topcamera.hpp"
#define ONE_BY_ROOT2 0.707

/**
 * @brief   Constructor for the TopCamera class
*/
TopCamera::TopCamera() {}

/**
 * @brief   Initialiser for the Topcamera clas
*/
void TopCamera::Init() {
    posn = {0,0};
    speed = CAMERA_SPEED;
}

/**
 * @brief   Captures movement keys for moving the camera around
*/
void TopCamera::MotionCapture() {
    Vector2 newPosn = posn;
    
    double speedMultiplier = 1.0;
    if (IsKeyDown(KEY_LEFT_SHIFT)) speedMultiplier = CAMERA_SPEED_MULTIPLIER;
    double trueSpeed = speed * speedMultiplier;

    if (IsKeyDown(KEY_UP)) {
        if (IsKeyDown(KEY_LEFT)) {
            newPosn.y-=trueSpeed * ONE_BY_ROOT2;
            newPosn.x-=trueSpeed * ONE_BY_ROOT2;
        } else if (IsKeyDown(KEY_RIGHT)) {
            newPosn.y-=trueSpeed * ONE_BY_ROOT2;
            newPosn.x+=trueSpeed * ONE_BY_ROOT2;
        } else {
            newPosn.y-=trueSpeed;
        }
    } else if (IsKeyDown(KEY_DOWN)) {
        if (IsKeyDown(KEY_LEFT)) {
            newPosn.y+=trueSpeed * ONE_BY_ROOT2;
            newPosn.x-=trueSpeed * ONE_BY_ROOT2;
        } else if (IsKeyDown(KEY_RIGHT)) {
            newPosn.y+=trueSpeed * ONE_BY_ROOT2;
            newPosn.x+=trueSpeed * ONE_BY_ROOT2;
        } else {
            newPosn.y+=trueSpeed;
        }
    } else if (IsKeyDown(KEY_LEFT)) {
        newPosn.x-=trueSpeed;
    } else if (IsKeyDown(KEY_RIGHT)) {
        newPosn.x+=trueSpeed;
    }

    posn = newPosn;
}

/**
 * @brief   Helper function for other objects to check whether they collide with the camera or not (by overall shape)
 */
bool TopCamera::IsObjOnScreen(Rectangle objShape) const {
    Rectangle screen = {posn.x, posn.y, float(GetScreenWidth()), float(GetScreenHeight())};
    return CheckCollisionRecs(objShape, screen);
}

/**
 * @brief   Helper function for other objects to check whether they collide with the camera or not (by overall shape)
 */
bool TopCamera::IsObjOnScreen(std::pair<Vector2, double> objShape) const {
    Rectangle screen = {posn.x, posn.y, float(GetScreenWidth()), float(GetScreenHeight())};
    return CheckCollisionCircleRec(objShape.first, objShape.second, screen);
}