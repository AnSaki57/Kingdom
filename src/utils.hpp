#pragma once
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
}