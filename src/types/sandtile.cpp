#include "sandtile.hpp"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"

// Constructors for SandTile based on Tile's constructor, plus custom Tile attributes
SandTile::SandTile(Vector2 posn_, float size_, float borderSize_, std::unique_ptr<StationaryEntity> tileEntity_) : Tile(posn_, size, borderSize_, std::move(tileEntity_), sandTileStats) {}
SandTile::SandTile(Vector2 posn_, std::unique_ptr<StationaryEntity> tileEntity_) : Tile(posn_, std::move(tileEntity_), sandTileStats) {}