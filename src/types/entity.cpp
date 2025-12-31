#include "entity.hpp"
#include "topcamera.hpp"
#include "utils.hpp"
#include <utility>

/**
 * @brief           Constructor for Entity, helps initialise the hpBar
 * 
 * @param hpBar_    Value of hpBar to set to
 */
Entity::Entity(ProgressBar hpBar_) : hpBar(hpBar_) {}

/**
 * @brief   Getter for the position of the Entity
 * 
 * @returns The position of the Entity
 */
Vector2 Entity::GetPosn() { return posn; }

/**
 * @brief   Getter for hitbox circle of the Entity
 * 
 * @returns Position, radius of hitbox circle
 */
std::pair<Vector2, double> Entity::GetHitbox() const { return std::pair<Vector2, double>(posn, hitboxRadius); }

/**
 * @brief   Getter for current HP
 * 
 * @returns  Current HP
 */
double Entity::GetCurrHP() { return currHP; }

/**
 * @brief   Getter for total HP
 * 
 * @returns Total HP
 */
double Entity::GetTotalHP() { return totalHP; }

/**
 * @brief   Getter for actual attack power (with multiplier)
 * 
 * @returns True attack power of the Entity
 */
double Entity::GetAttackPower() {
    return attackPower * GetAttackMult();
}

/**
 * @brief   Getter for current level of the Entity
 * 
 * @returns Level of the Entity
 */
int Entity::GetLevel() { return level; }

/**
 * @brief       Static setter for the Font asset of every Entity's text info
 * 
 * @param font_ Font to set the text to
 */
void Entity::SetFont(Font font_) { font = font_; }


/**
 * @brief   Getter for the multiplier for object speed
 * 
 * @returns Multiplier for the speed according to the Entity's level
 */
double Entity::GetSpeedMult() { return Utility::GetMultiplier(level); }

/**
 * @brief   Getter for the multiplier for attack strength
 * 
 * @returns Multiplier for the attack strength according to the Entity's level
 */
double Entity::GetAttackMult() { return Utility::GetMultiplier(level); }

/**
 * @brief   Getter for the multiplier for attack speed
 * 
 * @returns Multiplier for the attack speed according to the Entity's level
 */
double Entity::GetAttackSpeedMult() { return Utility::GetMultiplier(level); }

/**
 * @brief   Getter for the multiplier for health of the Entity
 * 
 * @returns Multiplier for the health according to the Entity's level
 */
double Entity::GetHealthMult() { return Utility::GetMultiplier(level); }


/**
 * @brief   Update all the cooldowns of the Entity (eg. attack cooldown)
 */
void Entity::UpdateCooldown() {
    if (attackCooldown > 0) {
        attackCooldown--;
    }
}

/**
 * @brief   Describes whether this entity can attack now, or not
 * 
 * @returns Boolean to whether attacking is possible or not
 */
bool Entity::CanAttack() { 
    if (attackCooldown<=0) return true; 
    return false;
}

/**
 * @brief   Setter to the attackCooldown
 */
void Entity::ResetAttackCooldown() {
    attackCooldown = attackSpeed / GetAttackSpeedMult();
}


/**
 * @brief           Common, generic portion of any Entity's Draw function
 * 
 * @param camera    Drawing context for the Entity
 */
void Entity::EntityDraw(const TopCamera& camera) const {
    DrawCircle(posn.x-camera.GetPosn().x, posn.y-camera.GetPosn().y, POPUP_CIRCLE_SIZE, POPUP_CIRCLE_COLOUR);
    
    // Draw the text at the centre of the circle
    Vector2 textSize = MeasureTextEx (
        font, 
        std::to_string(level).c_str(), 
        POPUP_CIRCLE_SIZE*1.5, 
        POPUP_CIRCLE_SIZE/5
    );
    DrawTextEx (
        font, 
        std::to_string(level).c_str(), 
        {
            float(posn.x-camera.posn.x-textSize.x/2), 
            float(posn.y-camera.posn.y-textSize.y/2), 
        }, 
        POPUP_CIRCLE_SIZE*1.5, 
        POPUP_CIRCLE_SIZE/5, 
        WHITE
    );
}