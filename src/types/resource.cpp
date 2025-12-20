#include "resource.hpp"
#include "topcamera.hpp"
#include "../constants.hpp"
#include "assets.hpp"

/**
 * @brief           Constructor for Resource class, for initialising the common attributes
 * 
 * @param posn_     Where the object is to be placed on the overall map
 * @param count_    The count of the resource for that specific obect-pile
 */
Resource::Resource(Vector2 posn_, int count_) : posn(posn_), count(count_) {
    if (count>25) count = 25;
}

// Getters and setters for position, count of Resource
Vector2 Resource::GetPosn() const { return posn; }
void Resource::SetPosn(Vector2 posn_) { posn = posn_; }
int Resource::GetCount() const { return count; }
void Resource::SetCount(int count_) { count = count_; }

/**
 * @brief   Defines the static font element used by all Resource objects
 */
void Resource::setFont() {
    countFont = Assets::sansSerifBold;
}

/**
 * @brief           Draws the resource, as well as the count of that resource in a popup on the bottom-right corner
 * 
 * @param camera    Drawing context on where to draw the resource
 */
void Resource::Draw(const TopCamera& camera) const {
    const Texture2D& sprite = getSprite();

    DrawTexture(sprite, posn.x-camera.posn.x, posn.y-camera.posn.y, WHITE);
    DrawCircle(posn.x+RESOURCE_SIZE-camera.posn.x, posn.y+RESOURCE_SIZE-camera.posn.y, POPUP_CIRCLE_SIZE, POPUP_CIRCLE_COLOUR);
    DrawTextEx (
        countFont, 
        std::to_string(count).c_str(), 
        {
            float(posn.x+RESOURCE_SIZE-camera.posn.x-POPUP_CIRCLE_SIZE*0.75), 
            float(posn.y+RESOURCE_SIZE-camera.posn.y-POPUP_CIRCLE_SIZE*0.75)
        }, 
        POPUP_CIRCLE_SIZE*1.5, 
        POPUP_CIRCLE_SIZE/5, 
        WHITE
    );
}