#include "resource.hpp"

/**
 * Wood-type resource
 * 
 * Responsibilities:
 *  - Manages its own static "wood" sprite
 * 
 * Non-responsibilities:
 *  - Inherits a Draw() function from parent, none of its own
 */
class Wood : public Resource {
    static Texture2D sprite;
public:
    Wood(Vector2 posn_, int count_);
    static void setSprite() ; 
    const Texture2D& getSprite() const override;
};