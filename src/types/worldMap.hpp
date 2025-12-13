#pragma once
#include <vector>
#include <memory>
#include "chunk.hpp"
#include "raylib.h"

class TopCamera;

class WorldMap {
    std::vector<Chunk> mapChunks;

    Chunk::TileCreator grassTileCreator;
    Chunk::TileCreator mudTileCreator;

public:
    WorldMap();
    void Init();

    void GenerateChunks(const TopCamera& camera);
    void Draw(const TopCamera& camera) const;
};