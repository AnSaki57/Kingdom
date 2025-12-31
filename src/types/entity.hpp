#pragma once

#include "raylib.h"
#include "../constants.hpp"
#include "progressBar.hpp"

class TopCamera;

/**
 * Represents the type of Entitys present in the game (stationary and mobile)
 */
enum EntityType {
    ENTITY_TYPE_NONE,

    // Stationary
    ENTITY_TYPE_TREE,
    ENTITY_TYPE_BOULDER,

    // Mobile
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_ENEMY,
    ENTITY_TYPE_PROJECTILE
};

/**
 * What must be done to an Entity by the manager, as per the Entity's collision outcome
 */
enum EntityCollisionResponse {
    ENTITY_COLL_NONE,
    ENTITY_COLL_DESTROY
};

/**
 * Full set of Update statistics that an Entity child may ever need for its own Update()
 */
struct EntityUpdateStats {
    Vector2 playerPosn;
    double damage;
};

/**
 * Represents a generic entity on the map
 * 
 * Responsibilities:
 *  - Holds the default values of hitboxes, hp, and level
 *  - Implements the getter for hitboxes
 */
class Entity{
protected:
    ProgressBar hpBar;
    Vector2 posn;
    double hitboxRadius = TILE_SIZE/3;
    double currHP = BASE_ENTITY_HP;
    double totalHP = BASE_ENTITY_HP;
    int level = 1;
    double speed = ENTITY_SPEED;
    double attackPower = BASE_ENTITY_ATTACK;
    int attackSpeed = int(FRAMES_PER_SECOND * 0.5); // No. of frames between each consecutive attack
    int attackCooldown = 0;
    inline static Font font = {0};
    
public:
    EntityType entityType = ENTITY_TYPE_NONE;
    EntityUpdateStats entityUpdateStats;
    bool followsCamera = false;

    Entity(ProgressBar hpBar_);

    Vector2 GetPosn();
    std::pair<Vector2, double> GetHitbox() const;
    double GetCurrHP();
    double GetTotalHP();
    double GetAttackPower();
    int GetLevel();
    // double GetShield();     // TODO: Implement this later (when Entity lvl > 20 or smthng)
    static void SetFont(Font font_);
    
    double GetSpeedMult();
    double GetAttackMult();
    double GetAttackSpeedMult();
    double GetHealthMult();
    // double GetShieldMult();  // Intended for the `Shield` feature (lvl > 20 or smthng)
    // double GetBuildSpeedMult(); // Intended for the `Buildings` feature
    // double GetPotionAttackMult();   // Intended for the `Potions` feature (lvl > 50 or smthng)

    void UpdateCooldown();
    bool CanAttack();
    void ResetAttackCooldown();

    virtual void Update() = 0;
    virtual void Draw(const TopCamera& camera) const = 0;
    void EntityDraw(const TopCamera& camera) const;
    virtual ~Entity() = default;
    virtual EntityCollisionResponse OnCollision(EntityType entityType_, EntityUpdateStats entityUpdateStats_) = 0;
};

/**
 * @brief       Get the default HP bar for all the Entities
 * 
 * @param posn_ Where the bar is to be placed
 */
inline ProgressBar DefaultHpBar(Vector2 posn_) {
    return ProgressBar({posn_.x, posn_.y-float(ENTITY_SIZE)/5, float(ENTITY_SIZE), float(ENTITY_SIZE)/8}, 1, BLUE, RED, BLACK, 1.0);
}

/**
 * @brief               How effective a projectile should be against another Entity
 * 
 * @param entityType    Type of Entity at the receiving end
 */
inline double ProjectileDamageMultiplier(EntityType entityType) {
    switch (entityType) {
        case ENTITY_TYPE_BOULDER:
        case ENTITY_TYPE_TREE:
            return 0.1;
        case ENTITY_TYPE_PLAYER:
            return 0.0;
        case ENTITY_TYPE_ENEMY:
            return 1.0;
        
        default:
            break;
    }
    return 0.0;
}