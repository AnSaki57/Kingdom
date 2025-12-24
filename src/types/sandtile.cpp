#include "sandtile.hpp"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"

// Constructors for SandTile based on Tile's constructor, plus custom Tile attributes
SandTile::SandTile(Vector2 posn_, float size_, float borderSize_) : Tile(posn_, size, borderSize_, sandTileStats) {}
SandTile::SandTile(Vector2 posn_) : Tile(posn_, sandTileStats) {}