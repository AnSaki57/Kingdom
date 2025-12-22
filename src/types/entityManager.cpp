#include "entityManager.hpp"
#include "topcamera.hpp"

/**
 * @brief   Initialises the player of the game
 */
void EntityManager::Init() {
    std::unique_ptr<Player> player = std::make_unique<Player>();
    player->Init();
    entities.push_back(std::move(player));
}

/**
 * @brief   Calls the Update function for each entity on the screen
 */
void EntityManager::Update(const TopCamera& camera) {
    for (size_t i = 0; i < entities.size(); i++) {
        if (camera.IsObjOnScreen(entities[i]->GetHitbox())) {
            entities[i]->Update();
        }
    }
}

/**
 * @brief   Checks each pair of entities for a hitbox-hitbox collision
 */
void EntityManager::CheckCollisions() {
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i]) {
            for (size_t j = i+1; j < entities.size(); j++) {
                if (entities[j] && CheckCollisionCircles(entities[i]->GetHitbox().first, entities[i]->GetHitbox().second, entities[j]->GetHitbox().first, entities[j]->GetHitbox().second)) {
                    entities[i]->OnCollision();
                    entities[j]->OnCollision();
                }
            }
        }
    }
}

/**
 * @brief           Draws each Entity on the map
 * 
 * @param camera    Drawing context for the Entitys
 */
void EntityManager::Draw(const TopCamera& camera) {
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i]->Draw(camera);
    }
}
