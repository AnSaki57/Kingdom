#include "mudtile.hpp"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"

/**
 * @brief           Drawing function for the MudTile class
 * 
 * @param camera    Drawing context to decide whether to draw the Tile or not, as well as get the offset for drawing so
*/
void MudTile::Draw(const TopCamera& camera) const {
    if (camera.isObjOnScreen(posn)) {
        DrawRectangle(this->posn.x-camera.posn.x, this->posn.y-camera.posn.y, this->size, this->size, BROWN_);
        DrawRectangleLinesEx({this->posn.x-camera.posn.x, this->posn.y-camera.posn.y, this->size, this->size}, TILE_BORDER_SIZE, LIGHT_BROWN_);
        if (tileEntity != nullptr) {
            tileEntity->Draw(camera);
        }
    }
}