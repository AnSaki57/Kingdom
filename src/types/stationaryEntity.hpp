#pragma once

#include "entity.hpp"

/**
 * Represents an entity on the map that cannot move
 */
class StationaryEntity : public Entity {
protected:
    StationaryEntity(ProgressBar hpBar_);
    // As of now, nothing else to implement
};