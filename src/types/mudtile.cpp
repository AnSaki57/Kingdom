#include "mudtile.hpp"

void MudTile::Draw(const TopCamera& camera) {
    DrawRectangle(this->posn.x-camera.posn.x, this->posn.y-camera.posn.y, this->size, this->size, BROWN_);
    DrawRectangleLinesEx({this->posn.x-camera.posn.x, this->posn.y-camera.posn.y, this->size, this->size}, 2, LIGHT_BROWN_);
    if (tileEntity != nullptr) {
        tileEntity->Draw(camera);
    }
}