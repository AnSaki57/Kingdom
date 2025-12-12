#include "chunk.hpp"
#include "tile.hpp"
#include "topcamera.hpp"
#include "tree.hpp"
#include <random>
#include <chrono>

Chunk::Chunk(TileCreator tc, Vector2 chunkPosn) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(1, 1000000);
    
    tiles.resize(CHUNK_SIZE);

    for (size_t i = 0; i < CHUNK_SIZE; i++) {
        tiles[i].resize(CHUNK_SIZE);
        for (size_t j = 0; j < CHUNK_SIZE; j++) {
            Vector2 tilePosn = {chunkPosn.x+i*TILE_SIZE, chunkPosn.y+j*TILE_SIZE};
            
            int randnum = distribution(generator); 
            if (randnum % 16 == 0) {
                auto tree = std::make_unique<Tree>(tilePosn);
                tiles[i][j] = tc(tilePosn, std::move(tree));
            } else {
                tiles[i][j] = tc(tilePosn, nullptr);
            }
        }
    }
}

Rectangle Chunk::getPosn() {
    return {tiles[0][0]->getPosn().x, tiles[0][0]->getPosn().y, CHUNK_SIZE * TILE_SIZE, CHUNK_SIZE * TILE_SIZE};
}

void Chunk::Draw(const TopCamera& camera) {
    for (size_t i = 0; i < CHUNK_SIZE; i++) {
        for (size_t j = 0; j < CHUNK_SIZE; j++) {
            tiles[i][j]->Draw(camera);
        }
    }
}