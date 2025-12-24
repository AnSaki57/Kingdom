#include "entity.hpp"
#include <utility>

/**
 * @brief           Constructor for Entity, helps initialise the hpBar
 * 
 * @param hpBar_    Value of hpBar to set to
 */
Entity::Entity(ProgressBar hpBar_) : hpBar(hpBar_) {}

/**
 * @brief   Getter for hitbox circle of the Entity
 * 
 * @returns Position, radius of hitbox circle
 */
std::pair<Vector2, double> Entity::GetHitbox() const { return std::pair<Vector2, double>(posn, hitboxRadius); }