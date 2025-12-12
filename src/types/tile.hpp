#pragma once
#include <memory>
#include "raylib.h"
#include "topcamera.hpp"
#include "stationaryEntity.hpp"
#include "../constants.hpp"

class Tile {
protected:
    Vector2 posn;
    float size;
    float borderSize;
    std::unique_ptr<StationaryEntity> tileEntity;

public:    
    Tile(Vector2 posn_, float size_, float borderSize_, std::unique_ptr<StationaryEntity> tileEntity_) : posn(posn_), size(size_), borderSize(borderSize_), tileEntity(std::move(tileEntity_)) {}
    Tile(Vector2 posn_, std::unique_ptr<StationaryEntity> tileEntity_) : posn(posn_), size(TILE_SIZE), borderSize(TILE_BORDER_SIZE), tileEntity(std::move(tileEntity_)) {}
    
    virtual void Draw(const TopCamera& camera) = 0;
    virtual ~Tile() = default;
};