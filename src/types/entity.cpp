#include "entity.hpp"
#include <utility>

/**
 * @brief   Getter for hitbox circle of the Entity
 * 
 * @returns Position, radius of hitbox circle
 */
std::pair<Vector2, double> Entity::GetHitbox() { return std::pair<Vector2, double>(posn, hitboxRadius); }