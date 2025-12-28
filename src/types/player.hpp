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
    double xp = 0;      // Defines the Players' level, not the other way round
    ProgressBar xpBar;
    bool isAlive = true;

public:
    Player();
    void Init();
    Vector2 GetPosn() const;
    bool GetLiveness() const;
    double GetXP() const;
    void SetXP(double xp_);
    void PutResource(int count, ResourceType resourceType);
    void Update() override;
    void Draw(const TopCamera&) const override;
    EntityCollisionResponse OnCollision(EntityType entityType_, EntityUpdateStats entityUpdateStats_) override;
};