#include "resource.hpp"
#include "topcamera.hpp"
#include "../constants.hpp"
#include "assets.hpp"

/**
 * @brief           Constructor for Resource class, for initialising the common attributes
 * 
 * @param posn_     Where the object is to be placed on the overall map
 * @param count_    The count of the resource for that specific object-pile
 */
Resource::Resource(Vector2 posn_, int count_, const ResourceStats resourceStats_) : posn(posn_), count(count_), resourceStats(resourceStats_) {
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
void Resource::SetFont(Font font_) {
    countFont = font_;
}

/**
 * @brief           Draws the resource, as well as the count of that resource in a popup on the bottom-right corner
 * 
 * @param camera    Drawing context on where to draw the resource
 */
void Resource::Draw(const TopCamera& camera) const {
    const Texture2D& sprite = GetSprite();

    DrawTexture(sprite, posn.x-camera.posn.x, posn.y-camera.posn.y, WHITE);
    DrawCircle(posn.x+RESOURCE_SIZE-camera.posn.x, posn.y+RESOURCE_SIZE-camera.posn.y, POPUP_CIRCLE_SIZE, POPUP_CIRCLE_COLOUR);
    
    // Draw the text at the centre of the circle
    Vector2 textSize = MeasureTextEx (
        countFont, 
        std::to_string(count).c_str(), 
        POPUP_CIRCLE_SIZE*1.5, 
        POPUP_CIRCLE_SIZE/5
    );
    DrawTextEx (
        countFont, 
        std::to_string(count).c_str(), 
        {
            float(posn.x+RESOURCE_SIZE-camera.posn.x-textSize.x/2), 
            float(posn.y+RESOURCE_SIZE-camera.posn.y-textSize.y/2), 
        }, 
        POPUP_CIRCLE_SIZE*1.5, 
        POPUP_CIRCLE_SIZE/5, 
        WHITE
    );
}