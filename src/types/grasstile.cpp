#include "grasstile.hpp"

void GrassTile::Draw(const TopCamera& camera) {
    DrawRectangle(this->posn.x-camera.posn.x, this->posn.y-camera.posn.y, this->size, this->size, GREEN_);
    DrawRectangleLinesEx({this->posn.x-camera.posn.x, this->posn.y-camera.posn.y, this->size, this->size}, 2, LIGHT_GREEN_);
    if (tileEntity != nullptr) {
        tileEntity->Draw(camera);
    }
}