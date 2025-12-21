#include "resource.hpp"

/**
 * Wood-type resource
 * 
 * Responsibilities:
 *  - Manages its own static "wood" sprite
 *  - Must call (by itself or by others) its (un)loader
 * 
 * Non-responsibilities:
 *  - Inherits a Draw() function from parent, none of its own
 */
class Wood : public Resource {
    static Texture2D sprite;
    static bool isSpriteLoaded;
public:
    Wood(Vector2 posn_, int count_);
    static void LoadSprite(); 
    static void UnloadSprite(); 
    const Texture2D& GetSprite() const override;
};