#include "chunk.hpp"
#include "tile.hpp"
#include "topcamera.hpp"
#include "tree.hpp"
#include <random>
#include <chrono>

// Manual initialisation of default functions
Chunk::~Chunk() = default;
Chunk::Chunk(Chunk&&) noexcept = default;
Chunk& Chunk::operator=(Chunk&&) noexcept = default;

/**
 * @brief           Creates a Chunk based on the Tile type that the Tile creator function passes on, randomly deciding on whether or not to add a Tree to the Tile
 * 
 * @param tc        Tile Creation function that allows the creation of either grass or mud Tile types
 * @param chunkPosn Position on the screen where the Chunk is to be placed
*/
Chunk::Chunk(TileCreator tc, Vector2 chunkPosn) : posn(chunkPosn) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(1, 1000000);
    
    tiles.resize(CHUNK_SIZE);

    for (size_t i = 0; i < CHUNK_SIZE; i++) {
        tiles[i].resize(CHUNK_SIZE);
        for (size_t j = 0; j < CHUNK_SIZE; j++) {
            Vector2 tilePosn = {chunkPosn.x+i*TILE_SIZE, chunkPosn.y+j*TILE_SIZE};
            
            tiles[i][j] = tc(tilePosn, nullptr);
        }
    }
}

/**
 * @brief   Getter for Chunk posn
 * 
 * @returns Chunk posn on the map
*/
Vector2 Chunk::GetPosn() const { return posn; }

/**
 * @brief   Getter for Chunk size and posn
 * 
 * @returns Chunk posn, and size on the map
*/
Rectangle Chunk::GetShape() const {
    return {posn.x, posn.y, CHUNK_SIZE * TILE_SIZE, CHUNK_SIZE * TILE_SIZE};
}

/**
 * @brief           Draws each Tile in the Chunk (if it exists)
 * 
 * @param camera    Provides drawing context for the underlying Tile class
*/
void Chunk::Draw(const TopCamera& camera) const {
    if (!camera.IsObjOnScreen(GetShape())) return;
    for (size_t i = 0; i < CHUNK_SIZE; i++) {
        for (size_t j = 0; j < CHUNK_SIZE; j++) {
            if (tiles[i][j]) {
                tiles[i][j]->Draw(camera);
            }
        }
    }
}