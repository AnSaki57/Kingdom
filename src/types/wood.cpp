#include "wood.hpp"
#include "../constants.hpp"

Texture2D Wood::sprite = Texture2D();
bool Wood::isSpriteLoaded = false;

/**
 * @brief           Definition of a Wood object based on parent constructor
 * 
 * @param posn_     Where the object is to be placed on the overall map
 * @param count_    The count of the resource for that specific obect-pile
 */
Wood::Wood(Vector2 posn_, int count_) : Resource(posn_, count_, ResourceStats({sprite, wood})) {}

/**
 * @brief   Sets the Texture2D sprite after processing the image
 */
void Wood::LoadSprite() {
    if (!isSpriteLoaded) {
        Image imgSprite = LoadImage("Wood.png");
        ImageCrop(&imgSprite, {156, 156, 313, 313});
        ImageResize(&imgSprite, RESOURCE_SIZE, RESOURCE_SIZE);
        sprite = LoadTextureFromImage(imgSprite);

        isSpriteLoaded = true;
    }
}

/**
 * @brief   Unloads the static Wood sprite
 */
void Wood::UnloadSprite() {
    UnloadTexture(sprite);
}

/**
 * @brief   Getter for the sprite of the class
 * 
 * @returns The "wood" sprite
 */
const Texture2D& Wood::GetSprite() const {
    return sprite;
}