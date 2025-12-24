#include "mudtile.hpp"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"

// Constructors for SandTile based on Tile's constructor, plus custom Tile attributes
MudTile::MudTile(Vector2 posn_, float size_, float borderSize_) : Tile(posn_, size, borderSize_, mudTileStats) {}
MudTile::MudTile(Vector2 posn_) : Tile(posn_, mudTileStats) {}