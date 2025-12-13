#include "raylib.h"
#include "chunk.hpp"
#include <vector>

class TopCamera;

class WorldMap {
    std::vector<Chunk> mapChunks;

public:
    void GenerateChunks(const TopCamera& camera);   // To be run every few secs
    void Draw(const TopCamera& camera) const;
};