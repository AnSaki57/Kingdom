#include "stationaryEntity.hpp"

class Tree : public StationaryEntity {
    static Texture2D sprite;
    static bool isTextureLoaded;
    // Make a resource class, add wood

public:
    Tree();
    Tree(Vector2 posn_);
    void SetPosn(Vector2 posn_);
    static const Texture2D& getTexture();
    void Draw(const TopCamera& camera) override;
};