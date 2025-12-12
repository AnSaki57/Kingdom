#include "raylib.h"
#include <iostream>
#include <vector>
#include <functional>
#include <memory>

#define CHUNK_SIZE 64

class Tile;
class TopCamera;
class StationaryEntity;

class Chunk {
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;

public:
    using TileCreator = std::function<std::unique_ptr<Tile>(Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_)>;

    Chunk(TileCreator tc, Vector2 chunkPosn);

    void Draw(const TopCamera& camera);
};