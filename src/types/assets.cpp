#include "assets.hpp"
#include "tree.hpp"
#include "wood.hpp"

/**
 * @brief   Loads all assets, to be used before game starts and after window init
 */
void Assets::LoadAll() {
    sansSerifBold = LoadFont("SansSerifBold.ttf");
    Tree::LoadSprite();
    Wood::LoadSprite();
}

/**
 * @brief   Unloads all assets, to be used after game ends and before prog exit
 */
void Assets::UnloadAll() {
    Tree::UnloadSprite();
    Wood::UnloadSprite();
    UnloadFont(sansSerifBold);
}