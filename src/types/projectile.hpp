#include "mobileEntity.hpp"

/**
 * Defines a generic projectile (usually, a bullet) shot by some weapon (weapon class not yet created)
 * 
 * Responsibilities:
 *  - Handles velocity explicitly
 *  - Provides behaviour for collision with other Entities
 */
class Projectile : public MobileEntity {
    Vector2 velocity;
    int lifetime = 4000;    // TODO: Integrate this better

public:
    Projectile(Vector2 posn_, Vector2 velocity_);
    void Update() override;
    void Draw(const TopCamera& camera) const;
    EntityCollisionResponse OnCollision(EntityType entityType_, EntityUpdateStats entityUpdateStats_) override;

};