#include "entity.hpp"
#include "topcamera.hpp"
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

/**
 * @brief           Common, generic portion of any Entity's Draw function
 * 
 * @param camera    Drawing context for the Entity
 */
void Entity::EntityDraw(const TopCamera& camera) const {
    DrawCircle(posn.x-camera.GetPosn().x, posn.y-camera.GetPosn().y, POPUP_CIRCLE_SIZE, POPUP_CIRCLE_COLOUR);
    DrawText(std::to_string(level).c_str(), posn.x-camera.GetPosn().x, posn.y-camera.GetPosn().y, POPUP_CIRCLE_SIZE, WHITE);
}