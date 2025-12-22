#include "entity.hpp"
#include "player.hpp"
#include <vector>
#include <memory>

/**
 * Manages all the Entity objects in the game
 * 
 * Responsibilities:
 *  - Owns all the Entity Objects in the game
 */
class EntityManager {
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void Init();
    void Update(const TopCamera& camera);
    void CheckCollisions();
    void Draw(const TopCamera& camera);
};