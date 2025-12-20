#include "mudtile.hpp"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"

// Constructors for SandTile based on Tile's constructor, plus custom Tile attributes
MudTile::MudTile(Vector2 posn_, float size_, float borderSize_, std::unique_ptr<StationaryEntity> tileEntity_) : Tile(posn_, size, borderSize_, std::move(tileEntity_), mudTileStats) {}
MudTile::MudTile(Vector2 posn_, std::unique_ptr<StationaryEntity> tileEntity_) : Tile(posn_, std::move(tileEntity_), mudTileStats) {}