#include "assets.hpp"
#include "wood.hpp"

/**
 * @brief   Loads all assets, to be used before game starts and after window init
 */
void Assets::LoadAll() {
    sansSerifBold = LoadFont("SansSerifBold.ttf");
    Wood::setSprite();
}

/**
 * @brief   Unloads all assets, to be used after game ends and before prog exit
 */
void Assets::UnloadAll() {
    UnloadFont(sansSerifBold);
}