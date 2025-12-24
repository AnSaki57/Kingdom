#include "entityManager.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "topcamera.hpp"
#include "tree.hpp"
#include "../constants.hpp"
#include <iostream>

/**
 * @brief   Initialises the player of the game
 */
void EntityManager::Init() {
    std::unique_ptr<Player> player = std::make_unique<Player>();
    player->Init();
    entities.push_back(std::move(player));
    destroyQueue.resize(0);
}

/**
 * @brief                   Generate entities on newly-generated Chunks
 * 
 * @param newChunksPosns    Location of newly generated Chunks
 */
void EntityManager::GenerateEntities(std::vector<Vector2> newChunksPosns) {
    for (const auto& newChunkPosn : newChunksPosns) {
        for (size_t i = 0; i < CHUNK_SIZE; i++) {
            for (size_t j = 0; j < CHUNK_SIZE; j++) {
                Vector2 tilePosn = {newChunkPosn.x + i * TILE_SIZE, newChunkPosn.y + j * TILE_SIZE};

                // Tree generation
                int rand = random() % 1000;
                if (rand < 50) {
                    entities.push_back(std::make_unique<Tree>(tilePosn));
                }

                // Enemy generation
                rand = random() % 1000000;
                if (rand < 250) {
                    entities.push_back(std::make_unique<Enemy>(tilePosn));
                }
            }
        }
    }
}

/**
 * @brief   Puts resource to the Player Entity's Inventory
 * 
 * @param count         Count of Resource to insert
 * @param resourceType  Type of Resource to insert
 */
void EntityManager::PutResource(int count, ResourceType resourceType) { 
    static_cast<Player*>(entities[0].get())->PutResource(count, resourceType); 
}

/**
 * @brief           Checks each pair of entities for a hitbox-hitbox collision
 * 
 * @param camera    Context for what collisions matter (only those on-screen)
 */
void EntityManager::CheckCollisions(const TopCamera& camera) {
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i] && (entities[i]->followsCamera || camera.IsObjOnScreen(entities[i]->GetHitbox()))) {
            Vector2 offset = {0,0};
            if (entities[i]->followsCamera) offset = {camera.posn.x, camera.posn.y};
            auto [posn1, radius1] = entities[i]->GetHitbox();
            posn1 = {posn1.x+offset.x, posn1.y+offset.y};

            for (size_t j = i+1; j < entities.size(); j++) {
                if (
                    entities[j] && 
                    camera.IsObjOnScreen(entities[j]->GetHitbox()) && 
                    CheckCollisionCircles (
                        posn1, radius1, 
                        entities[j]->GetHitbox().first, 
                        entities[j]->GetHitbox().second
                    )
                ) {
                    EntityCollisionResponse resp1 = entities[i]->OnCollision(entities[j]->entityType);
                    EntityCollisionResponse resp2 = entities[j]->OnCollision(entities[i]->entityType);
                    if (resp1 == ENTITY_COLL_DESTROY) destroyQueue.push_back(i); 
                    if (resp2 == ENTITY_COLL_DESTROY) destroyQueue.push_back(j); 
                }
            }
        }
    }
}

/**
 * @brief           Calls the Update function for each Entity on the screen
 * 
 * @param camera    Context for what Entitys to update
 */
std::vector<std::tuple<Vector2, int, ResourceType>> EntityManager::Update(const TopCamera& camera/*, EntityUpdateStats entityUpdateStats*/) {
    std::vector<std::tuple<Vector2, int, ResourceType>> returnResources;
    EntityUpdateStats entityUpdateStats;
    entityUpdateStats.playerPosn = static_cast<Player*>(entities[0].get())->GetPosn();
    entityUpdateStats.playerPosn = {entityUpdateStats.playerPosn.x+camera.posn.x, entityUpdateStats.playerPosn.y+camera.posn.y};

    for (const auto& i : destroyQueue) {
        // If Tree is to be erased, add 5 Wood to the map 
        // TODO: Automate this for every Entity
        auto entityDestroyType = entities[i]->entityType;
        if (entityDestroyType == ENTITY_TYPE_TREE) {
            returnResources.push_back(std::tuple<Vector2, int, ResourceType>(entities[i]->GetHitbox().first, 5, RESOURCE_TYPE_WOOD));
        }
        entities.erase(entities.begin()+i);
    }
    destroyQueue.resize(0);

    for (size_t i = 0; i < entities.size(); i++) {
        switch (entities[i]->entityType) {
            case ENTITY_TYPE_NONE:
                break;
            case ENTITY_TYPE_PLAYER:
                entities[i]->Update(entityUpdateStats);
                break;
            case ENTITY_TYPE_ENEMY:
                entities[i]->Update(entityUpdateStats);
            case ENTITY_TYPE_TREE:
                if (camera.IsObjOnScreen(entities[i]->GetHitbox())) {
                    entities[i]->Update(entityUpdateStats);
                }
                break;
            
            default:
                break;
        }
    }

    return returnResources;
}

/**
 * @brief           Draws each Entity on the map
 * 
 * @param camera    Drawing context for the Entitys
 */
void EntityManager::Draw(const TopCamera& camera) const {
    for (size_t i = 1; i < entities.size(); i++) {
        if (entities[i]->followsCamera || camera.IsObjOnScreen(entities[i]->GetHitbox())) {
            entities[i]->Draw(camera);
        }
    }
    entities[0]->Draw(camera);  // Draw the player over other Entitys
}