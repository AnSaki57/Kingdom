#pragma once

#include <memory>
#include "raylib.h"

class TopCamera;
class StationaryEntity;

/**
 * Represents a generic tile that can hold a StationaryEntity on it
 * 
 * Responsibilities:
 *  - Owns the underlying StationaryEntity object
 */
class Tile {
protected:
    Vector2 posn;
    float size;
    float borderSize;
    std::unique_ptr<StationaryEntity> tileEntity;

public:    
    Tile(Vector2 posn_, float size_, float borderSize_, std::unique_ptr<StationaryEntity> tileEntity_);
    Tile(Vector2 posn_, std::unique_ptr<StationaryEntity> tileEntity_);
    
    Vector2 getPosn() const;
    Rectangle getBounds() const;
    virtual void Draw(const TopCamera& camera) const = 0;
    virtual ~Tile() = default;
};