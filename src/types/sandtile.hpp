#include "tile.hpp"

#define SANDY_YELLOW_ {220, 220, 150, 255}
#define LIGHT_SANDY_YELLOW_ {235, 235, 200, 255}

/**
 * Represents a Tile of sand type (golden yellow in colour)
 * 
 * Responsibilities:
 *  - Concrete class; must draw itself using Raylib functions
 */
class SandTile : public Tile {
public:
    using Tile::Tile;
    void Draw(const TopCamera& camera) const;
};