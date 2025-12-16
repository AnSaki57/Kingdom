#include "mobileEntity.hpp"
#include "progressBar.hpp"

/**
 * Represents the main playable character of the game
 * 
 * Responsibilities:
 *  - Manages its own sprite (creation and deletion) 
 *  - Concrete class; must draw itself using Raylib functions
*/
class Player : public MobileEntity {
    Texture2D sprite;
    ProgressBar hpBar;

public:
    Player();
    void Init();
    void Update();
    void Draw(const TopCamera&) const override;
};