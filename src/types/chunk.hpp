#include "raylib.h"
#include <vector>
#include <functional>
#include <memory>

class Tile;
class TopCamera;
class StationaryEntity;

/**
 * A class to hold a 2D vector of CHUNK_SIZE size of Tiles
 * 
 * Responsibilities:
 *  - Owns the Tiles in it
 *  - Must initialise the Tiles under it with the appropriate type
 *  - Exposes its size and shape through getters
 */
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

    Vector2 GetPosn() const;
    Rectangle GetShape() const;
    void Draw(const TopCamera& camera) const;
};