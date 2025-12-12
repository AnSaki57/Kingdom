#include "tile.hpp"

#define GREEN_ {0, 210, 0, 255}
#define LIGHT_GREEN_ {120, 230, 120, 255}

class GrassTile : public Tile {
public:
    using Tile::Tile;
    void Draw(const TopCamera& camera) const;
};