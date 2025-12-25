#include "entity.hpp"
#include "resource.hpp"
#include <vector>
#include <memory>
#include <tuple>

/**
 * Manages all the Entity objects in the game
 * 
 * Responsibilities:
 *  - Owns all the Entity Objects in the game
 *  - First Entity (entities[0]) is guaranteed to be the Player
 */
class EntityManager {
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<int> destroyQueue;
    int attackCooldown;

public:
    void Init();
    void GenerateEntities(std::vector<Vector2> newChunksPosns);
    void AttackDir(Vector2 dirposn, const TopCamera& camera);
    void PutResource(int count, ResourceType resourceType);
    void CheckCollisions(const TopCamera& camera);
    std::vector<std::tuple<Vector2, int, ResourceType>> Update(const TopCamera& camera);
    void Draw(const TopCamera& camera) const;
};