#pragma once

#include "entity.hpp"
#include "progressBar.hpp"

/**
 * Represents an entity on the board that can move around
*/
class MobileEntity : public Entity {
protected:
    ProgressBar hpBar;
    MobileEntity(ProgressBar hpBar_);
    // As of now, nothing else to implement
};