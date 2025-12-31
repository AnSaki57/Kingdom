#include "assets.hpp"
#include "entity.hpp"
#include "enemy.hpp"
#include "resource.hpp"
#include "tree.hpp"
#include "wood.hpp"
#include "fadeout.hpp"

/**
 * @brief   Loads all assets, to be used before game starts and after window init
 */
void Assets::LoadAll() {
    Enemy::LoadSprite();
    gameFont = LoadFont("SansSerifBold.ttf");
    Entity::SetFont(gameFont);
    Resource::SetFont(gameFont);
    Fadeout::SetFont(gameFont);
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
    UnloadFont(gameFont);
}