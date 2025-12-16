#include "stationaryEntity.hpp"

class Tree : public StationaryEntity {
    static Texture2D sprite;
    static bool isTextureLoaded;
    // Make a resource class, add wood

public:
    Tree(Vector2 posn_);
    static void LoadSprite();
    static void UnloadSprite();

    void Draw(const TopCamera& camera) const override;
};