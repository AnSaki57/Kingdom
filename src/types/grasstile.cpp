#include "grasstile.hpp"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"

// Constructors for GrassTile based on Tile's constructor, plus custom Tile attributes
GrassTile::GrassTile(Vector2 posn_, float size_, float borderSize_) : Tile(posn_, size, borderSize_, grassTileStats) {}
GrassTile::GrassTile(Vector2 posn_) : Tile(posn_, grassTileStats) {}