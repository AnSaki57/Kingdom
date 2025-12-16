#include "grasstile.hpp"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"

void GrassTile::Draw(const TopCamera& camera) const {
    if (camera.isObjOnScreen(posn)) {
        DrawRectangle(this->posn.x-camera.posn.x, this->posn.y-camera.posn.y, this->size, this->size, GREEN_);
        DrawRectangleLinesEx({this->posn.x-camera.posn.x, this->posn.y-camera.posn.y, this->size, this->size}, TILE_BORDER_SIZE, LIGHT_GREEN_);
        if (tileEntity != nullptr) {
            tileEntity->Draw(camera);
        }
    }
}