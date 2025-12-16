#include "mobileEntity.hpp"

/**
 * Represents the main playable character of the game
 * 
 * Responsibilities:
 *  - Manages its own sprite (creation and deletion) 
 *  - Concrete class; must draw itself using Raylib functions
*/
class Player : public MobileEntity {
    Texture2D sprite;

public:
    Player();
    void Init();
    void Draw(const TopCamera&) const override;
};