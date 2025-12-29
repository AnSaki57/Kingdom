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
    std::vector<int> countStats;

    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<int> destroyQueue;
    int attackCooldown;

public:
    bool isPlayerAlive = true;

    void Init();
    std::vector<int> GetCountStats();
    void GenerateEntities(std::vector<Vector2> newChunksPosns, int level);
    void SpawnEnemies(const TopCamera& camera, int level);
    void AttackDir(Vector2 dirposn, const TopCamera& camera);
    void PutResource(int count, ResourceType resourceType);
    void CheckCollisions(const TopCamera& camera);
    std::vector<std::tuple<Vector2, int, ResourceType>> Update(const TopCamera& camera);
    void Draw(const TopCamera& camera) const;
};

/**
 * @brief   Info on counts of various game info
 */
enum CountStats {
    COUNTSTAT_PLAYER_LEVEL,
    COUNTSTAT_ENEMIES_KILLED,
    COUNTSTAT_TREES_DESTROYED,
    COUNTSTAT_WOOD_COLLECTED
};