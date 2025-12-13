#include "raylib.h"
// #include "tile.hpp"
#include <iostream>
#include <vector>
#include <functional>
#include <memory>

#define CHUNK_SIZE 16

class Tile;
class TopCamera;
class StationaryEntity;

class Chunk {
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;

public:
    using TileCreator = std::function<std::unique_ptr<Tile>(Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_)>;

    Chunk(TileCreator tc, Vector2 chunkPosn);
    ~Chunk();
    Chunk(const Chunk&) = delete;
    Chunk& operator=(const Chunk&) = delete;
    Chunk(Chunk&& other);
    Chunk& operator=(Chunk&& other);

    Rectangle getPosn() const;
    void Draw(const TopCamera& camera) const;
};