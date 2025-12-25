#include "entityManager.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "topcamera.hpp"
#include "tree.hpp"
#include "../constants.hpp"
#include "raymath.h"
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
 * @brief   Creates a Projectile in the input position's direction
 * 
 * @param dirposn   Position of the mouse click on the overall map
 * @param camera    Offset context for the projectile's position and direction on the overall map
 */
void EntityManager::AttackDir(Vector2 dirposn, const TopCamera& camera) {
    if (attackCooldown>0) return;           // If cooldown not yet elapsed since last attack, skip this

    Vector2 centre = {GetScreenWidth()/2+camera.GetPosn().x, GetScreenHeight()/2+camera.GetPosn().y};
    Vector2 attackDir = {dirposn.x-centre.x, dirposn.y-centre.y};
    attackDir = {attackDir.x*PROJECTILE_SPEED/Vector2Length(attackDir), attackDir.y*PROJECTILE_SPEED/Vector2Length(attackDir)};
    std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(centre, attackDir);
    entities.push_back(std::move(projectile));

    attackCooldown = 1 * FRAMES_PER_SECOND; // Pause for a second before launching another Projectile
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
                // Check if entities[i] and entities[j] collide with each other
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

    for (int i = destroyQueue.size()-1; i >= 0; i--) {
        if (destroyQueue[i]>=entities.size()) {
            // In the off-chance that out-of-bounds access occurs
            continue;
        }
        // If Tree is to be erased, add 5 Wood to the map 
        // TODO: Automate this for every Entity
        EntityType entityDestroyType = entities[destroyQueue[i]]->entityType;
        if (entityDestroyType == ENTITY_TYPE_TREE) {
            returnResources.push_back(std::tuple<Vector2, int, ResourceType>(entities[destroyQueue[i]]->GetHitbox().first, 5, RESOURCE_TYPE_WOOD));
        }
        entities.erase(entities.begin()+destroyQueue[i]);
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
                break;
            case ENTITY_TYPE_PROJECTILE:
                entities[i]->Update(entityUpdateStats);
                break;
            case ENTITY_TYPE_TREE:
                if (camera.IsObjOnScreen(entities[i]->GetHitbox())) {
                    entities[i]->Update(entityUpdateStats);
                }
                break;
            
            default:
                break;
        }
    }

    if (attackCooldown>0) attackCooldown--;

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