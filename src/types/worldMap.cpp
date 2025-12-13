#include "worldMap.hpp"
#include "grasstile.hpp"
#include "mudtile.hpp"
#include "topcamera.hpp"

Chunk::TileCreator grassTileCreator = [](Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_) {
    return std::make_unique<GrassTile>(posn, std::move(tileEntity_));
};
Chunk::TileCreator mudTileCreator = [](Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_) {
    return std::make_unique<MudTile>(posn, std::move(tileEntity_));
};

void WorldMap::GenerateChunks(const TopCamera& camera) {
    Vector2 posn = camera.posn;
    Vector2 nearestLatticePoint = {
        int(posn.x) % int(CHUNK_SIZE * TILE_SIZE), 
        int(posn.y) % int(CHUNK_SIZE * TILE_SIZE)
    };

    // Check nearby lattice points for existence of chunk; if not, make one
    std::vector<Vector2> checkPoints(9);
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            checkPoints[3*i+j] = {
                nearestLatticePoint.x + i * (CHUNK_SIZE * TILE_SIZE),
                nearestLatticePoint.y + j * (CHUNK_SIZE * TILE_SIZE)
            };
        }
    }

    std::vector<bool> chunkExists(9, false);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < mapChunks.size(); j++) {
            Vector2 chunkPosn = {mapChunks[j].getPosn().x, mapChunks[j].getPosn().y};
            if (chunkPosn.x == checkPoints[i].x && chunkPosn.y == checkPoints[i].y) {
                chunkExists[i] = true;
            } 
        }
    }

    for (int i = 0; i < 9; i++) {
        if (!chunkExists[i]) {
            Chunk mapChunk(grassTileCreator, checkPoints[i]);
            mapChunks.push_back(std::move(mapChunk));
            // mapChunks.emplace_back(mapChunk);
        }
    }
}

void WorldMap::Draw(const TopCamera& camera) const {
    for (const auto& mapChunk : mapChunks) {
        mapChunk.Draw(camera);
    }
}