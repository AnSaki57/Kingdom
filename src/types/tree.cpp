#include <iostream>
#include "tree.hpp"
#include "topcamera.hpp"
#include "../constants.hpp"

// Initialise static parameters
Texture2D Tree::sprite;
bool Tree::isTextureLoaded = false;

/**
 * @brief       Initialiser for a Tree object, starting off with beginner-level hp
 * 
 * @param posn_ Position on the map to draw the Tree
*/
Tree::Tree(Vector2 posn_) : StationaryEntity(DefaultHpBar(posn_)) {
    posn = posn_;
    entityType = ENTITY_TYPE_TREE;
}

/**
 * @brief   Texture loader for the Tree class, to be called once before the game begins
*/
void Tree::LoadSprite() {
    if (!isTextureLoaded) {
        Image imgsprite = LoadImage("Trees.jpg");

        if (!IsImageValid(imgsprite)) {
            std::cerr << "Tree img not found\n";
        } else {
            std::cout << YELLOW_TEXT << "Tree loaded successfully\n" << RESET_TEXT;
        }
        ImageCrop(&imgsprite, {90, 300, 300, 400});
        ImageResize(&imgsprite, TILE_SIZE, TILE_SIZE);
        sprite = LoadTextureFromImage(imgsprite);
        UnloadImage(imgsprite);

        isTextureLoaded = true;
    }
}

/**
 * @brief   Texture unloader for the Tree class, to be called once after the game ends
*/
void Tree::UnloadSprite() {
    if (isTextureLoaded) {
        UnloadTexture(sprite);
        isTextureLoaded = false;
    }
}

/**
 * @brief   Getter for the overall shape of the Tree texture
 * 
 * @returns Tile shape, essentially 
 */
Rectangle Tree::GetShape() const { return {posn.x, posn.y, float(TILE_SIZE), float(TILE_SIZE)}; }

/**
 * @brief   Frame-by-frame updation of the Tree (as of now, nothing)
 */
void Tree::Update() {
    hpBar.SetFill(currHP/totalHP);
}

/**
 * @brief           Draws the Tree texture (sprite) on the screen
 * 
 * @param camera    Context for drawing the texture on the map
*/
void Tree::Draw(const TopCamera& camera) const {
    if (camera.IsObjOnScreen(GetShape())) {
        DrawTexture(sprite, posn.x-camera.posn.x, posn.y-camera.posn.y, WHITE);
        if (currHP < totalHP) {
            hpBar.Draw(camera);
        }
    }
}

/**
 * @brief   What a tree does on collision with a hitbox (sample, destroy itself)
 * 
 * @returns Info abt the Tree's response to the collision, that the manager might want to know
 */
EntityCollisionResponse Tree::OnCollision(EntityType entityType_, EntityUpdateStats entityUpdateStats_) {
    if (entityType_ == ENTITY_TYPE_PROJECTILE) {
        currHP-=entityUpdateStats.damage;
        entityUpdateStats.damage = 0;
        if (currHP <= 0) {
            return ENTITY_COLL_DESTROY;
        }
    } else if (entityType_ == ENTITY_TYPE_PLAYER) {
        return ENTITY_COLL_DESTROY;
    }
    return ENTITY_COLL_NONE;
}