#include "tile.hpp"

#define GREEN_ {0, 210, 0, 255}
#define LIGHT_GREEN_ {120, 230, 120, 255}

/**
 * Represents a Tile of grass type
 * 
 * Responsibilities:
 *  - Concrete class; must draw itself using Raylib functions
 * 
 * Non-responsibilities:
 *  - Uses default Draw function of parent
 */
class GrassTile : public Tile {
    static constexpr TileStats grassTileStats = { GREEN_, LIGHT_GREEN_ };
public:
    GrassTile(Vector2 posn_, float size_, float borderSize_, std::unique_ptr<StationaryEntity> tileEntity_);
    GrassTile(Vector2 posn_, std::unique_ptr<StationaryEntity> tileEntity_);
};