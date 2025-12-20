#include "tile.hpp"

#define SANDY_YELLOW_ {220, 220, 150, 255}
#define LIGHT_SANDY_YELLOW_ {235, 235, 200, 255}

/**
 * Represents a Tile of sand type (golden yellow in colour)
 * 
 * Responsibilities:
 *  - Concrete class; must draw itself using Raylib functions
 * 
 * Non-responsibilities:
 *  - Uses default Draw function of parent
 */
class SandTile : public Tile {
    static constexpr TileStats sandTileStats = { SANDY_YELLOW_, LIGHT_SANDY_YELLOW_ };
public:
    SandTile(Vector2 posn_, float size_, float borderSize_, std::unique_ptr<StationaryEntity> tileEntity_);
    SandTile(Vector2 posn_, std::unique_ptr<StationaryEntity> tileEntity_);
};