#include "raylib.h"
#include <vector>
#include <functional>
#include <memory>

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 32
#endif

class Tile;
class TopCamera;
class StationaryEntity;

class Chunk {
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    Vector2 posn;

public:
    using TileCreator = std::function<std::unique_ptr<Tile>(Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_)>;

    Chunk(TileCreator tc, Vector2 chunkPosn);

    // Default move constructor and assignment operator are required
    // because unique_ptr cannot be copied.
    ~Chunk();
    Chunk(Chunk&&) noexcept;
    Chunk& operator=(Chunk&&) noexcept;

    // Delete copy components to prevent accidental copying
    Chunk(const Chunk&) = delete;
    Chunk& operator=(const Chunk&) = delete;

    Rectangle getPosn() const;
    void Draw(const TopCamera& camera) const;
};