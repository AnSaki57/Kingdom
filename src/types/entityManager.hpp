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
    std::vector<int> destroyQueue;

public:
    void Init();
    void GenerateEntities(std::vector<Vector2> newChunksPosns);
    void CheckCollisions(const TopCamera& camera);
    void Update(const TopCamera& camera);
    void Draw(const TopCamera& camera) const;
};