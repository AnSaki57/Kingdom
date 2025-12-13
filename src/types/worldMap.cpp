#include "worldMap.hpp"
#include "grasstile.hpp"
#include "mudtile.hpp"
#include "topcamera.hpp"
#include <cstdlib>
#include <cmath>
#include <algorithm>

WorldMap::WorldMap() {
    grassTileCreator = [](Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_) {
        return std::make_unique<GrassTile>(posn, std::move(tileEntity_));
    };
    mudTileCreator = [](Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_) {
        return std::make_unique<MudTile>(posn, std::move(tileEntity_));
    };
}

void WorldMap::GenerateChunks(const TopCamera& camera) {
    const double chunkWorldSize = CHUNK_SIZE * TILE_SIZE;

    Vector2 currGridPosn = {
        std::floor(camera.posn.x / chunkWorldSize) * chunkWorldSize,
        std::floor(camera.posn.y / chunkWorldSize) * chunkWorldSize
    };

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            Vector2 targetPosn = {
                currGridPosn.x + i * chunkWorldSize,
                currGridPosn.y + j * chunkWorldSize
            };

            bool chunkExists = false;
            for (const auto& chunk : mapChunks) {
                Rectangle chunkPosn = chunk.getPosn();
                if (std::abs(chunkPosn.x - targetPosn.x) < 1.0f && std::abs(chunkPosn.y - targetPosn.y) < 1.0f) {
                    chunkExists = true;
                    break;
                }
            }

            if (!chunkExists) {
                int rand = random() % 2;
                if (rand) {
                    Chunk newChunk(grassTileCreator, targetPosn);
                    mapChunks.push_back(std::move(newChunk));
                } else {
                    Chunk newChunk(mudTileCreator, targetPosn);
                    mapChunks.push_back(std::move(newChunk));
                }
            }
        }
    }
}

void WorldMap::Draw(const TopCamera& camera) const {
    for (const auto& mapChunk : mapChunks) {
        mapChunk.Draw(camera);
    }
}