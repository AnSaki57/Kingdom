#include "resource.hpp"
#include "topcamera.hpp"
#include <vector>
#include <memory>

/**
 * Manages all the stray resources (& inventories?) in the Game
 * 
 * Responsibilities:
 *  - Owns all stray Resources (Resources not owned by any Entity)
 *  - Appends/deletes/draws stray Resources
 */
class ResourceManager {
    std::vector<std::unique_ptr<Resource>> resources;

public:
    void Append(Vector2 appendPosn, int count, ResourceType resourceType);
    std::pair<int, ResourceType> Delete(Vector2 clickPosn);
    void Draw(const TopCamera& camera) const;
};