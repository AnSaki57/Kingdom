#include "worldMap.hpp"
#include "grasstile.hpp"
#include "mudtile.hpp"
#include "sandtile.hpp"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

// How many rows/cols of Chunks to generate, starting from where 
#define CHUNK_LOAD_SIZE_X 4
#define CHUNK_LOAD_SIZE_Y 3
#define CHUNK_LOAD_BEGIN_X -1
#define CHUNK_LOAD_BEGIN_Y -1

/**
 * @brief   Default initialiser for the class
*/
WorldMap::WorldMap() {}

/**
 * @brief   Creates the Tile creation lambdas for the underlying Chunk class
*/
void WorldMap::Init() {
    grassTileCreator = [](Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_) {
        return std::make_unique<GrassTile>(posn, std::move(tileEntity_));
    };
    mudTileCreator = [](Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_) {
        return std::make_unique<MudTile>(posn, std::move(tileEntity_));
    };
    sandTileCreator = [](Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_) {
        return std::make_unique<SandTile>(posn, std::move(tileEntity_));
    };
}

/**
 * @brief   Automatically generates Chunks around the place where the camera is focusing on, if those Chunks don't exist already
 * 
 * @param camera    Context provider for where to generate Chunks
*/
void WorldMap::GenerateChunks(const TopCamera& camera) {
    const double chunkWorldSize = CHUNK_SIZE * TILE_SIZE;

    // Lattice position where Chunks are created
    Vector2 currGridPosn = {
        float(std::floor(camera.posn.x / chunkWorldSize) * chunkWorldSize),
        float(std::floor(camera.posn.y / chunkWorldSize) * chunkWorldSize)
    };


    // Get any Chunks computed in previous cycle out of pendingChunks
    for (int i = pendingChunks.size()-1; i >= 0; i--) {
        if (pendingChunks[i].pChunk.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            std::unique_ptr<Chunk> newChunk = pendingChunks[i].pChunk.get();
            mapChunks.push_back(std::move(newChunk));
            pendingChunks.erase(pendingChunks.begin() + i);
        }
    }

    // For each nearby lattice position, push ungenerated Chunk areas into pendingChunks
    for (int i = CHUNK_LOAD_BEGIN_X; i < CHUNK_LOAD_BEGIN_X + CHUNK_LOAD_SIZE_X; i++) {
        for (int j = CHUNK_LOAD_BEGIN_Y; j < CHUNK_LOAD_BEGIN_Y + CHUNK_LOAD_SIZE_Y; j++) {
            Vector2 targetPosn = {
                float(currGridPosn.x + i * chunkWorldSize),
                float(currGridPosn.y + j * chunkWorldSize)
            };

            // Check if a Chunk already exists, either in mapChunks or pendingChunks
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

            // If not, push to pendingChunks
            if (!chunkExists) {
                pendingChunks.push_back({
                    targetPosn,
                    std::async(std::launch::async, [=]() {
                        int rand = random() % 3;
                        if (rand==0) return std::make_unique<Chunk>(grassTileCreator, targetPosn);
                        if (rand==1) return std::make_unique<Chunk>(mudTileCreator, targetPosn);
                        return std::make_unique<Chunk>(sandTileCreator, targetPosn);
                    })}
                );
            }
        }
    }
}

/**
 * @brief Calls Draw on each Chunk in mapChunks; whether to draw or not is decided at the Chunk-level
 * 
 * @param camera    Camera context to pass down to each Chunk
*/
void WorldMap::Draw(const TopCamera& camera) const {
    for (const auto& mapChunk : mapChunks) {
        mapChunk->Draw(camera);
    }
}