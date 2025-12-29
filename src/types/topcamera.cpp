#include "topcamera.hpp"

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
 * @brief   Getter for position of the camera
 * 
 * @returns Position of the camera
 */
Vector2 TopCamera::GetPosn() const { return posn; }

/**
 * @brief   Captures movement keys for moving the camera around
*/
void TopCamera::MotionCapture(double borderSize) {
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

    // posn = newPosn;
    // Sample code for restricting movement to a borderSize x borderSize chunk area (comment above line)
    if (
        newPosn.x >= -TILE_SIZE * CHUNK_SIZE * borderSize - GetScreenWidth()/2 && newPosn.x <= TILE_SIZE * CHUNK_SIZE * borderSize - GetScreenWidth()/2 &&
        newPosn.y >= -TILE_SIZE * CHUNK_SIZE * borderSize - GetScreenHeight()/2 && newPosn.y <= TILE_SIZE * CHUNK_SIZE * borderSize - GetScreenHeight()/2
    ) {
        posn = newPosn;
    }
}

/**
 * @brief   Helper function for other objects to check whether they intersect with the screen or not (by rectangular hitbox)
 * 
 * @param objShape  Shape of object to check
 * 
 * @returns Boolean is-on-screen or not
 */
bool TopCamera::IsObjOnScreen(Rectangle objShape) const {
    Rectangle screen = {posn.x, posn.y, float(GetScreenWidth()), float(GetScreenHeight())};
    return CheckCollisionRecs(objShape, screen);
}

/**
 * @brief   Helper function for other objects to check whether they intersect with the screen or not (by circular hitbox)
 * 
 * @param objShape  Shape of object to check
 * 
 * @returns Boolean is-on-screen or not
 */
bool TopCamera::IsObjOnScreen(std::pair<Vector2, double> objShape) const {
    Rectangle screen = {posn.x, posn.y, float(GetScreenWidth()), float(GetScreenHeight())};
    return CheckCollisionCircleRec(objShape.first, objShape.second, screen);
}