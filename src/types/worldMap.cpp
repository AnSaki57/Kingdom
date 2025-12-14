#include "worldMap.hpp"
#include "grasstile.hpp"
#include "mudtile.hpp"
#include "topcamera.hpp"
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

WorldMap::WorldMap() {}

void WorldMap::Init() {
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
        float(std::floor(camera.posn.x / chunkWorldSize) * chunkWorldSize),
        float(std::floor(camera.posn.y / chunkWorldSize) * chunkWorldSize)
    };


    for (int i = pendingChunks.size()-1; i >= 0; i--) {
        if (pendingChunks[i].pChunk.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            std::unique_ptr<Chunk> newChunk = pendingChunks[i].pChunk.get();
            mapChunks.push_back(std::move(newChunk));
            pendingChunks.erase(pendingChunks.begin() + i);
        }
    }

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            Vector2 targetPosn = {
                float(currGridPosn.x + i * chunkWorldSize),
                float(currGridPosn.y + j * chunkWorldSize)
            };

            bool chunkExists = false;
            for (const auto& chunk : mapChunks) {
                Rectangle chunkPosn = chunk->getPosn();
                if (std::abs(chunkPosn.x - targetPosn.x) < 1.0f && std::abs(chunkPosn.y - targetPosn.y) < 1.0f) {
                    chunkExists = true;
                    break;
                }
            }
            for (const auto& [chunkPosn, chunk] : pendingChunks) {
                if (std::abs(chunkPosn.x - targetPosn.x) < 1.0f && std::abs(chunkPosn.y - targetPosn.y) < 1.0f) {
                    chunkExists = true;
                    break;
                }
            }

            if (!chunkExists) {
                pendingChunks.push_back({
                    targetPosn,
                    std::async(std::launch::async, [=]() {
                        int rand = random() % 2;
                        if (rand) return std::make_unique<Chunk>(grassTileCreator, targetPosn);
                        return std::make_unique<Chunk>(mudTileCreator, targetPosn);
                    })}
                );
            }
        }
    }
}

void WorldMap::Draw(const TopCamera& camera) const {
    for (const auto& mapChunk : mapChunks) {
        mapChunk->Draw(camera);
    }
}