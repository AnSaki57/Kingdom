#include <iostream>
#include "tree.hpp"
#include "topcamera.hpp"
#include "../constants.hpp"

Texture2D Tree::sprite;
bool Tree::isTextureLoaded = false;

/**
 * @brief       Initialiser for a Tree object, starting off with beginner-level hp
 * 
 * @param posn_ Position on the map to draw the Tree
*/
Tree::Tree(Vector2 posn_) {
    posn = posn_;
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
Rectangle Tree::GetShape() const { return {posn.x, posn.y, TILE_SIZE, TILE_SIZE}; }

/**
 * @brief           Draws the Tree texture (sprite) on the screen
 * 
 * @param camera    Context for drawing the texture on the map
*/
void Tree::Draw(const TopCamera& camera) const {
    if (camera.IsObjOnScreen(GetShape())) {
        DrawTexture(sprite, posn.x-camera.posn.x, posn.y-camera.posn.y, WHITE);
    }
}