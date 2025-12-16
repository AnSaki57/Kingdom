#include "tile.hpp"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"
#include "../constants.hpp"

Tile::Tile(Vector2 posn_, float size_, float borderSize_, std::unique_ptr<StationaryEntity> tileEntity_) : posn(posn_), size(size_), borderSize(borderSize_), tileEntity(std::move(tileEntity_)) {}

Tile::Tile(Vector2 posn_, std::unique_ptr<StationaryEntity> tileEntity_) : posn(posn_), size(TILE_SIZE), borderSize(TILE_BORDER_SIZE), tileEntity(std::move(tileEntity_)) {}

Vector2 Tile::getPosn() const {
    return posn;
}

Rectangle Tile::getBounds() const {
    return {posn.x, posn.y, size, size};
}