#include "mobileEntity.hpp"
#include "inventory.hpp"

/**
 * Represents the main playable character of the game
 * 
 * Responsibilities:
 *  - Manages its own sprite (creation and deletion) 
 *  - Concrete class; must draw itself using Raylib functions
*/
class Player : public MobileEntity {
    Texture2D sprite;
    Inventory inventory;

public:
    Player();
    void Init();
    Vector2 GetPosn() const;
    void PutResource(int count, ResourceType resourceType);
    void Update(const EntityUpdateStats&) override;
    void Draw(const TopCamera&) const override;
    EntityCollisionResponse OnCollision(EntityType entityType_) override;
};