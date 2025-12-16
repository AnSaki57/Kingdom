#include "tile.hpp"

#define BROWN_ {210, 70, 0, 255}
#define LIGHT_BROWN_ {255, 170, 100, 255}

/**
 * Represents a Tile of mud type (brownish in colour)
 * 
 * Responsibilities:
 *  - Concrete class; must draw itself using Raylib functions
 */
class MudTile : public Tile {
public:
    using Tile::Tile;
    void Draw(const TopCamera& camera) const;
};