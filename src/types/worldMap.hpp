#pragma once
#include <vector>
#include <memory>
#include <future>
#include "chunk.hpp"

class TopCamera;

struct PendingChunk {
    Vector2 posn;
    std::future<std::unique_ptr<Chunk>> pChunk;
};

class WorldMap {
    std::vector<std::unique_ptr<Chunk>> mapChunks;
    std::vector<PendingChunk> pendingChunks;

    Chunk::TileCreator grassTileCreator;
    Chunk::TileCreator mudTileCreator;

public:
    WorldMap();
    void Init();

    void GenerateChunks(const TopCamera& camera);
    void Draw(const TopCamera& camera) const;
};