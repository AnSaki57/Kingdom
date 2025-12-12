#include "tile.hpp"

#define BROWN_ {210, 70, 0, 255}
#define LIGHT_BROWN_ {255, 170, 100, 255}

class MudTile : public Tile {
public:
    using Tile::Tile;
    void Draw(const TopCamera& camera);
};