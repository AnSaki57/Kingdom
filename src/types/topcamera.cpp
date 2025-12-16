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

    if (IsKeyDown(KEY_UP)) {
        if (IsKeyDown(KEY_LEFT)) {
            newPosn.y-=speed * ONE_BY_ROOT2;
            newPosn.x-=speed * ONE_BY_ROOT2;
        } else if (IsKeyDown(KEY_RIGHT)) {
            newPosn.y-=speed * ONE_BY_ROOT2;
            newPosn.x+=speed * ONE_BY_ROOT2;
        } else {
            newPosn.y-=speed;
        }
    } else if (IsKeyDown(KEY_DOWN)) {
        if (IsKeyDown(KEY_LEFT)) {
            newPosn.y+=speed * ONE_BY_ROOT2;
            newPosn.x-=speed * ONE_BY_ROOT2;
        } else if (IsKeyDown(KEY_RIGHT)) {
            newPosn.y+=speed * ONE_BY_ROOT2;
            newPosn.x+=speed * ONE_BY_ROOT2;
        } else {
            newPosn.y+=speed;
        }
    } else if (IsKeyDown(KEY_LEFT)) {
        newPosn.x-=speed;
    } else if (IsKeyDown(KEY_RIGHT)) {
        newPosn.x+=speed;
    }

    posn = newPosn;
}
    
/**
 * @brief   Helper function for other objects to check whether they collide with the camera or not
*/
bool TopCamera::isObjOnScreen(Vector2 objPosn) const {
    if  (
            objPosn.x - posn.x > GetScreenWidth()  || objPosn.x < posn.x ||
            objPosn.y - posn.y > GetScreenHeight() || objPosn.y < posn.y 
        ) {
        return false;
    }
    return true;
}