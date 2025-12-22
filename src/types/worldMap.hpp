#pragma once
#include <vector>
#include <memory>
#include <future>
#include "chunk.hpp"

class TopCamera;

/**
 * Helper struct that holds a reference to a Chunk not yet computed, and where to place it
 * 
 * Responsibilities:
 *  - Owns the Chunk once created, until it is time to give it away
 */
struct PendingChunk {
    Vector2 posn;
    std::future<std::unique_ptr<Chunk>> pChunk;
};

/**
 * Overall map class to hold all Tiles in the form of Chunks, and display them accordingly
 * 
 * Responsibilities:
 *  - Owns all Chunks
 *  - Has the list of all Tile types
 *  - Must initialise the Tile creators for all Tile types
 *  - Must generate new Chunks as the Player moves around with the camera
 */
class WorldMap {
    std::vector<std::unique_ptr<Chunk>> mapChunks;
    std::vector<PendingChunk> pendingChunks;

    Chunk::TileCreator grassTileCreator;
    Chunk::TileCreator mudTileCreator;
    Chunk::TileCreator sandTileCreator;

public:
    WorldMap();
    void Init();

    std::vector<Vector2> GenerateChunks(const TopCamera& camera);
    void Draw(const TopCamera& camera) const;
};