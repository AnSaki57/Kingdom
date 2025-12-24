#pragma once

#include <memory>
#include "raylib.h"

class TopCamera;
class StationaryEntity;

/**
 * Helper struct to hold those values that vary with the type of Tile
 */
struct TileStats {
    Color bgColour;
    Color borderColour;
};

/**
 * Represents a generic tile that can hold a StationaryEntity on it
 * 
 * Responsibilities:
 *  - Owns the underlying StationaryEntity object
 *  - Contains reference to custom-Tile stats, used in Draw
 *  - Contains the logic for the Draw function, used by all its children
 *  - Exposes its shape and posn through getters
 */
class Tile {
protected:
    Vector2 posn;
    float size;
    float borderSize;
    const TileStats& tileStats;

public:    
    Tile(Vector2 posn_, float size_, float borderSize_, const TileStats& tileStats_);
    Tile(Vector2 posn_, const TileStats& tileStats_);
    
    Vector2 GetPosn() const;
    Rectangle GetShape() const;
    void Draw(const TopCamera& camera) const;
    virtual ~Tile() = default;
};