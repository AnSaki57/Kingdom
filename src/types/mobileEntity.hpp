#pragma once

#include "entity.hpp"

/**
 * Represents an entity on the board that can move around
*/
class MobileEntity : public Entity {
protected:
    MobileEntity(ProgressBar hpBar_);
    // As of now, nothing else to implement
};