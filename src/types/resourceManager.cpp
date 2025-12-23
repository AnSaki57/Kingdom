#include "resourceManager.hpp"
#include "wood.hpp"

/**
 * @brief               Appends resources to the list by taking in the needed parameters
 * 
 * @param appendPosn    Position where the Resource is to be created
 * @param count         Count of Resource to make
 * @param resourceType  Type of Resource to make
 */
void ResourceManager::Append(Vector2 appendPosn, int count, ResourceType resourceType) {
    switch (resourceType) {
        case wood:
            resources.push_back(std::move(std::make_unique<Wood>(appendPosn, count)));
            break;
        
        default:
            break;
    }
}

/**
 * @brief           Deletes Resources at a certain posn on the board
 * 
 * @param clickPosn Posn to check for Resource (to delete said resource, if found)
 */
std::pair<int, ResourceType> ResourceManager::Delete(Vector2 clickPosn) {
    std::pair<int, ResourceType> returnedResource;
    for (size_t i = 0; i < resources.size(); i++) {
        if (CheckCollisionPointRec(clickPosn, {resources[i]->GetPosn().x, resources[i]->GetPosn().y, float(RESOURCE_SIZE), float(RESOURCE_SIZE)})) {
            returnedResource = std::pair<int, ResourceType>(resources[i]->GetCount(), resources[i]->GetResourceType());
            resources.erase(resources.begin()+i);   // If multiple resources on same posn, delete only one
            return returnedResource;  
        }
    }

    return std::pair<int, ResourceType>(0, wood);
}

/**
 * @brief           Draws all the resources on the screen
 * 
 * @param camera    Drawing context for object, as well as condition on whether to draw or not
 */
void ResourceManager::Draw(const TopCamera& camera) const {
    for (auto& resource : resources) {
        if (camera.IsObjOnScreen({resource->GetPosn(), RESOURCE_SIZE/2})) {
            resource->Draw(camera);
        }
    }
}