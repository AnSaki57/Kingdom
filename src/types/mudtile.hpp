#include "tile.hpp"

#define BROWN_ {210, 70, 0, 255}
#define LIGHT_BROWN_ {255, 170, 100, 255}

/**
 * Represents a Tile of mud type (brownish in colour)
 * 
 * Responsibilities:
 *  - Concrete class; must draw itself using Raylib functions
 * 
 * Non-responsibilities:
 *  - Uses default Draw function of parent
 */
class MudTile : public Tile {
    static constexpr TileStats mudTileStats = { BROWN_, LIGHT_BROWN_ };
public:
    MudTile(Vector2 posn_, float size_, float borderSize_);
    MudTile(Vector2 posn_);
};