#include "tile.hpp"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"
#include "../constants.hpp"

/**
 * @brief               Detailed constructor for initialising all aspects of a Tile
 * 
 * @param posn_         Initialiser for the position of the Tile
 * @param size_         Initialiser for the size of the Tile
 * @param borderSize_   Initialiser for the border padding thickness (usually of a lighter colour than the body)
 * @param tileEntity_   Pointer to a stationary Entity to now be owned by this Tile
 * @param tileStats_    Reference to custom Tile attributes, for each type of Tile
 * 
 * Ownership:
 *  tileEntity_ is now owned by this Tile
*/
Tile::Tile(Vector2 posn_, float size_, float borderSize_, std::unique_ptr<StationaryEntity> tileEntity_, const TileStats& tileStats_) : posn(posn_), size(size_), borderSize(borderSize_), tileEntity(std::move(tileEntity_)), tileStats(tileStats_) {}

/**
 * @brief               Simple constructor for a Tile
 * @param posn_         Initialiser for the position of the Tile
 * @param tileEntity_   Pointer to a stationary Entity to now be owned by this Tile
 * @param tileStats_    Reference to custom Tile attributes, for each type of Tile
 * 
 * Ownership:
 *  tileEntity_ is now owned by this Tile
*/
Tile::Tile(Vector2 posn_, std::unique_ptr<StationaryEntity> tileEntity_, const TileStats& tileStats_) : posn(posn_), size(TILE_SIZE), borderSize(TILE_BORDER_SIZE), tileEntity(std::move(tileEntity_)), tileStats(tileStats_) {}

/**
 * @brief   Getter for the position of the Tile
 * 
 * @return  Position of the Tile
*/
Vector2 Tile::GetPosn() const {
    return posn;
}

/**
 * @brief   Getter for the overall shape of the Tile
 * 
 * @return  Position and size of the Tile
*/
Rectangle Tile::GetShape() const {
    return {posn.x, posn.y, size, size};
}

/**
 * @brief           Drawing function for a generic Tile class
 * 
 * @param camera    Drawing context to decide whether to draw the Tile or not, as well as get the offset for drawing so
*/
void Tile::Draw(const TopCamera& camera) const {
    if (camera.isObjOnScreen(GetShape())) {
        DrawRectangle(this->posn.x-camera.posn.x, this->posn.y-camera.posn.y, this->size, this->size, tileStats.bgColour);
        DrawRectangleLinesEx({this->posn.x-camera.posn.x, this->posn.y-camera.posn.y, this->size, this->size}, TILE_BORDER_SIZE, tileStats.borderColour);
        if (tileEntity != nullptr) {
            tileEntity->Draw(camera);
        }
    }
}