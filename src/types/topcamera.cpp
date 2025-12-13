#include "topcamera.hpp"
#define ONE_BY_ROOT2 0.707

TopCamera::TopCamera() {}

void TopCamera::Init() {
    posn = {0,0};
    speed = CAMERA_SPEED;
}

void TopCamera::Move() {
    if (IsKeyDown(KEY_UP)) {
        if (IsKeyDown(KEY_LEFT)) {
            posn.y-=speed * ONE_BY_ROOT2;
            posn.x-=speed * ONE_BY_ROOT2;
        } else if (IsKeyDown(KEY_RIGHT)) {
            posn.y-=speed * ONE_BY_ROOT2;
            posn.x+=speed * ONE_BY_ROOT2;
        } else {
            posn.y-=speed;
        }
    } else if (IsKeyDown(KEY_DOWN)) {
        if (IsKeyDown(KEY_LEFT)) {
            posn.y+=speed * ONE_BY_ROOT2;
            posn.x-=speed * ONE_BY_ROOT2;
        } else if (IsKeyDown(KEY_RIGHT)) {
            posn.y+=speed * ONE_BY_ROOT2;
            posn.x+=speed * ONE_BY_ROOT2;
        } else {
            posn.y+=speed;
        }
    } else if (IsKeyDown(KEY_LEFT)) {
        posn.x-=speed;
    } else if (IsKeyDown(KEY_RIGHT)) {
        posn.x+=speed;
    }
}
    
bool TopCamera::isObjOnScreen(Vector2 objPosn) const {
    if  (
            objPosn.x - posn.x > GetScreenWidth()  || objPosn.x < posn.x ||
            objPosn.y - posn.y > GetScreenHeight() || objPosn.y < posn.y 
        ) {
        return false;
    }
    return true;
}