#include "stationaryEntity.hpp"

/**
 * Represents a tree that can be placed on a Tile on the map
 * 
 * Responsibilities:
 *  - Provides handlers for managing its sprite
*/
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