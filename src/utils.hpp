#pragma once

#include "raylib.h"
#include <cmath>

namespace Utility {
    /**
     * @brief       Gets the appropriate value multiplier for the level of the Entity
     * 
     * @param level Level of intended entity
     * 
     * @returns     Net multiplier value
     */
    inline constexpr double GetMultiplier(int level) {
        return std::pow(BASE_LEVEL_MULTIPLIER, level);
    }

    /**
     * @brief   Gets a random unit-length 2D vector
     * 
     * @returns 2D unit vector in a random direction
     */
    /**
     * TODO: Make it proper
     */
    inline Vector2 GetRandUnitDir() {
        float rand1 = random() % 101 - 50;
        float rand2 = random() % 101 - 50;
        float magnitude = sqrt(rand1*rand1 + rand2*rand2);
        return Vector2({rand1/magnitude, rand2/magnitude});
    }
}