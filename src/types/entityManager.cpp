#include "entityManager.hpp"
#include "fadeoutManager.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "topcamera.hpp"
#include "tree.hpp"
#include "../constants.hpp"
#include "raymath.h"

/**
 * @brief   Initialises the player of the game
 */
void EntityManager::Init() {
    std::unique_ptr<Player> player = std::make_unique<Player>();
    player->Init();
    entities.push_back(std::move(player));
    destroyQueue.resize(0);
    countStats.resize(4, 0);
}

std::vector<int> EntityManager::GetCountStats() { 
    countStats[0] = entities[0]->GetLevel();
    return countStats; 
}

/**
 * @brief                   Generate entities on newly-generated Chunks
 * 
 * @param newChunksPosns    Location of newly generated Chunks
 * @param level             Level of Entitys to generate (roughly)
 */
void EntityManager::GenerateEntities(std::vector<Vector2> newChunksPosns, int level) {
    for (const auto& newChunkPosn : newChunksPosns) {
        for (size_t i = 0; i < CHUNK_SIZE; i++) {
            for (size_t j = 0; j < CHUNK_SIZE; j++) {
                Vector2 tilePosn = {float(newChunkPosn.x + i * TILE_SIZE), float(newChunkPosn.y + j * TILE_SIZE)};

                // Tree generation
                int rand = random() % 1000;
                if (rand < 50) {
                    entities.push_back(std::make_unique<Tree>(tilePosn));
                }

                // Enemy generation
                rand = random() % 1000000;
                if (rand < 1500) {
                    rand = random() % 10 - 4;   // Generate Entity levels +-5 from intended
                    if (level+rand<1) rand = 1-level;
                    entities.push_back(std::make_unique<Enemy>(tilePosn, level+rand));
                }
            }
        }
    }
}

/**
 * @brief           Spawns random Enemys around the Player, at given level
 * 
 * @param camera    Positional context on where the Player is
 * @param level     Level of Enemys to add
 */
void EntityManager::SpawnEnemies(const TopCamera& camera, int level) {
    double chunkWorldSize = CHUNK_SIZE * TILE_SIZE;
    Vector2 currGridPosn = {
        float(std::floor(camera.posn.x / chunkWorldSize) * chunkWorldSize),
        float(std::floor(camera.posn.y / chunkWorldSize) * chunkWorldSize)
    };

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i==0&&j==0) continue;

            Vector2 chunkPosn = {float(currGridPosn.x + chunkWorldSize*i), float(currGridPosn.y + chunkWorldSize*j)};

            // Chunk at i, j
            for (int row = 0; row < CHUNK_SIZE; row++) {
                for (int col = 0; col < CHUNK_SIZE; col++) {
                    Vector2 tilePosn = {float(chunkPosn.x+TILE_SIZE*row), float(chunkPosn.y+TILE_SIZE*col)};
                    int rand = random() % 1000000;
                    if (rand < 1000) {
                        rand = random() % 10 - 4;  // Generate Entity levels +-5 from intended
                    if (level+rand<1) rand = 1-level;
                        entities.push_back(std::make_unique<Enemy>(tilePosn, level+rand));
                    }
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
    if (!entities[0]->CanAttack()) return;  // If cooldown not yet elapsed since last attack, skip this

    Vector2 centre = {GetScreenWidth()/2+camera.GetPosn().x, GetScreenHeight()/2+camera.GetPosn().y};
    Vector2 attackDir = {dirposn.x-centre.x, dirposn.y-centre.y};
    attackDir = {
        float(attackDir.x*PROJECTILE_SPEED / Vector2Length(attackDir)), 
        float(attackDir.y*PROJECTILE_SPEED / Vector2Length(attackDir))
    };
    std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(centre, attackDir, entities[0]->GetAttackPower());
    entities.push_back(std::move(projectile));

    entities[0]->ResetAttackCooldown(); // Pause for a second before launching another Projectile
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
void EntityManager::CheckCollisions(const TopCamera& camera, FadeoutManager& fadeoutManager) {
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i] && (entities[i]->followsCamera || camera.IsObjOnScreen(entities[i]->GetHitbox()))) {
            // Adjust position as based on whether the Entity follows the camera or not
            auto [posn1, radius1] = entities[i]->GetHitbox();
            if (entities[i]->followsCamera) posn1 = {posn1.x+camera.GetPosn().x, posn1.y+camera.GetPosn().y};

            for (size_t j = i+1; j < entities.size(); j++) {
                auto [posn2, radius2] = entities[j]->GetHitbox();
                if (entities[j]->followsCamera) posn2 = {posn2.x+camera.GetPosn().x, posn2.y+camera.GetPosn().y};

                // Check if entities[i] and entities[j] collide with each other
                if (
                    entities[j] && 
                    camera.IsObjOnScreen(entities[j]->GetHitbox()) && 
                    CheckCollisionCircles(posn1, radius1, posn2, radius2)
                ) {
                    // Collision setup (i does what to j's state, and vice versa)
                    switch (entities[i]->entityType) {
                        case ENTITY_TYPE_PROJECTILE:
                            entities[j]->entityUpdateStats.damage=entities[i]->GetAttackPower()*ProjectileDamageMultiplier(entities[j]->entityType);
                            break;
                        case ENTITY_TYPE_ENEMY:
                            if (entities[j]->entityType==ENTITY_TYPE_PLAYER && entities[i]->CanAttack()) {
                                entities[j]->entityUpdateStats.damage=entities[i]->GetAttackPower()*0.2;
                                fadeoutManager.PutMessage(FADEOUT_TYPE_PLAYER_DAMAGE,std::to_string(int(std::floor(entities[j]->entityUpdateStats.damage))), posn2);
                                entities[i]->ResetAttackCooldown();
                            }
                        
                        default:
                            break;
                    }
                    switch (entities[j]->entityType) {
                        case ENTITY_TYPE_PROJECTILE:
                            entities[i]->entityUpdateStats.damage=entities[j]->GetAttackPower()*ProjectileDamageMultiplier(entities[i]->entityType);
                            break;
                        case ENTITY_TYPE_ENEMY:
                            if (entities[i]->entityType==ENTITY_TYPE_PLAYER && entities[j]->CanAttack()) {
                                entities[i]->entityUpdateStats.damage=entities[j]->GetAttackPower()*0.2;
                                fadeoutManager.PutMessage(FADEOUT_TYPE_PLAYER_DAMAGE,std::to_string(int(std::floor(entities[i]->entityUpdateStats.damage))), posn1);
                                entities[j]->ResetAttackCooldown();
                            }
                        
                        default:
                            break;
                    }
                    
                    // Collision response of entities (how j responds to i's interference, and vice versa)
                    EntityCollisionResponse resp1 = entities[i]->OnCollision(entities[j]->entityType, EntityUpdateStats());
                    EntityCollisionResponse resp2 = entities[j]->OnCollision(entities[i]->entityType, EntityUpdateStats());
                    
                    // Collision response of the Entity manager (what needs to be done to j, that only the manager can do (eg. deletion))
                    switch (resp1) {
                        case ENTITY_COLL_DESTROY:
                            destroyQueue.push_back(i);
                            break;
                        
                        default:
                            break;
                    }
                    switch (resp2) {
                        case ENTITY_COLL_DESTROY:
                            destroyQueue.push_back(j);
                            break;
                        
                        default:
                            break;
                    }
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
std::vector<std::tuple<Vector2, int, ResourceType>> EntityManager::Update(const TopCamera& camera, FadeoutManager& fadeoutManager) {
    if (entities[0] && static_cast<Player*>(entities[0].get())->GetLiveness() == false) {
        isPlayerAlive = false;
    }

    std::vector<std::tuple<Vector2, int, ResourceType>> returnResources;
    EntityUpdateStats entityUpdateStats;
    entityUpdateStats.damage = 0;
    entityUpdateStats.playerPosn = static_cast<Player*>(entities[0].get())->GetPosn();
    entityUpdateStats.playerPosn = {entityUpdateStats.playerPosn.x+camera.posn.x, entityUpdateStats.playerPosn.y+camera.posn.y};

    // Put some more objects up for destruction
    for (int i = 0; i < entities.size(); i++) {
        switch (entities[i]->entityType) {
            case ENTITY_TYPE_PROJECTILE: {
                Projectile* projectile = static_cast<Projectile*>(entities[i].get());
                if (!projectile->ShouldBeAlive()) {
                    destroyQueue.push_back(i);
                }
                break;
            }
            
            default:
                break;
        }
    }

    // Destroy Entities scheduled for removal
    for (int i = destroyQueue.size()-1; i >= 0; i--) {
        // In the off-chance that out-of-bounds access occurs
        if (destroyQueue[i]>=entities.size()) { continue; }

        EntityType entityDestroyType = entities[destroyQueue[i]]->entityType;
        Player* player = static_cast<Player*>(entities[0].get());

        switch (entityDestroyType) {
            case ENTITY_TYPE_TREE:
            // If Tree is to be erased, add 5 Wood to the map 
            // TODO: Automate this for every Entity
            returnResources.push_back(std::tuple<Vector2, int, ResourceType>(entities[destroyQueue[i]]->GetHitbox().first, 5, RESOURCE_TYPE_WOOD));
            player->SetXP(player->GetXP()+5);
            fadeoutManager.PutMessage(FADEOUT_TYPE_XP, "5", {entities[destroyQueue[i]]->GetPosn()});
            countStats[COUNTSTAT_TREES_DESTROYED]++;
            break;
        case ENTITY_TYPE_ENEMY:
            player->SetXP(player->GetXP()+15);
            fadeoutManager.PutMessage(FADEOUT_TYPE_XP, "15", {entities[destroyQueue[i]]->GetPosn()});
            countStats[COUNTSTAT_ENEMIES_KILLED]++;
            break;
        
        default:
            break;
        }

        entities.erase(entities.begin()+destroyQueue[i]);
    }
    destroyQueue.resize(0);

    // Update the Entities acording to their type
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i]->entityUpdateStats = entityUpdateStats;
        switch (entities[i]->entityType) {
            case ENTITY_TYPE_NONE:
                break;
            case ENTITY_TYPE_PLAYER:
                entities[i]->Update();
                break;
            case ENTITY_TYPE_ENEMY:
                entities[i]->Update();
                break;
            case ENTITY_TYPE_PROJECTILE:
                entities[i]->Update();
                break;
            case ENTITY_TYPE_TREE:
                if (camera.IsObjOnScreen(entities[i]->GetHitbox())) {
                    entities[i]->Update();
                }
                break;
            
            default:
                break;
        }
    }

    for (const auto& entity : entities) {
        entity->UpdateCooldown();
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
            
            // Draw the level an object is
            switch (entities[i]->entityType) {
                case ENTITY_TYPE_ENEMY:
                    entities[i]->EntityDraw(camera);
                    break;
                case ENTITY_TYPE_TREE:
                    if (entities[i]->GetCurrHP()<entities[i]->GetTotalHP())
                        entities[i]->EntityDraw(camera);

                default:
                    break;
            }
        }
    }
    entities[0]->Draw(camera);  // Draw the player over other Entitys
}