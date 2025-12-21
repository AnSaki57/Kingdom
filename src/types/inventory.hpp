#pragma once

#include "raylib.h"
#include "resource.hpp"
#include <vector>
#include <memory>

/**
 * Standard storage of any type of Resources either by the player or other entities
 * 
 * Responsibilities:
 *  - Owns the Resources it contains, as well as getting/setting/deleting them
 * 
 * Non-responsibilities:
 *  - Doesn't explicitly track the type of Resource
 */
class Inventory {
    int rows;
    int cols;
    Vector2 posn;
    std::vector<std::vector<std::unique_ptr<Resource>>> boxes;

public:
    void Init(int rows_, int cols_, Vector2 posn_);   

    int GetRows() const;
    int GetCols() const;
    Vector2 GetPosn() const;
    Vector2 GetPosn(int row, int col) const;
    const Resource* GetBoxImmut(int row, int col) const;
    Resource* GetBoxMut(int row, int col);
    void SetBox(int row, int col, int count, enum ResourceType resourceType);
    void DeleteItem(int row, int col);

    void Draw() const ;
    void Draw(const TopCamera& camera) const;
};