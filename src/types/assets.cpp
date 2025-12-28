#include "assets.hpp"
#include "entity.hpp"
#include "enemy.hpp"
#include "resource.hpp"
#include "tree.hpp"
#include "wood.hpp"

/**
 * @brief   Loads all assets, to be used before game starts and after window init
 */
void Assets::LoadAll() {
    Enemy::LoadSprite();
    sansSerifBold = LoadFont("SansSerifBold.ttf");
    Entity::SetFont(sansSerifBold);
    Resource::SetFont(sansSerifBold);
    Tree::LoadSprite();
    Wood::LoadSprite();
}

/**
 * @brief   Unloads all assets, to be used after game ends and before prog exit
 */
void Assets::UnloadAll() {
    Enemy::UnloadSprite();
    Tree::UnloadSprite();
    Wood::UnloadSprite();
    UnloadFont(sansSerifBold);
}