#include "mobileEntity.hpp"
#include "progressBar.hpp"
#include "inventory.hpp"

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
    Inventory inventory;

public:
    Player();
    void Init();
    void Update();
    void Draw(const TopCamera&) const override;
};