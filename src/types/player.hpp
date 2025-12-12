#include "raylib.h"
#include "mobileEntity.hpp"

class Player : public MobileEntity {
    Texture2D sprite;

public:
    Player();
    void Draw(TopCamera) override;
};