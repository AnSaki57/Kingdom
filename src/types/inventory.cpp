#include "inventory.hpp"
#include "../constants.hpp"
#include "wood.hpp"
#include "topcamera.hpp"

/**
 * @brief       Initialiser for the size and posn of the Inventory
 * 
 * @param rows_ No. of rows to put in the Inventory
 * @param cols_ No. of cols to put in the Inventory
 * @param posn_ Where to put the inventory
 */
void Inventory::Init(int rows_, int cols_, Vector2 posn_) {
    rows = rows_;
    cols = cols_;
    posn = posn_;

    boxes.resize(rows);
    for (size_t row = 0; row < rows; row++) {
        boxes[row].resize(cols);
    }
}   

// Standard getters for rows, cols in Inventory, posn of Inventory
int Inventory::GetRows() const { return rows; }
int Inventory::GetCols() const { return cols; }
Vector2 Inventory::GetPosn() const { return posn; }
Vector2 Inventory::GetPosn(int row, int col) const { return {float(posn.x+col*BOX_SIZE), float(posn.y+row*BOX_SIZE)}; }

/**
 * @brief       Immutable getter for Resource in box
 * 
 * @param row   Row of desired box
 * @param col   Col of desired box
 * 
 * @returns     Resource in that box, immutably
 */
const Resource* Inventory::GetBoxImmut(int row, int col) const {
    return boxes[row][col].get();
}

/**
 * @brief       Mutable getter for Resource in box
 * 
 * @param row   Row of desired box
 * @param col   Col of desired box
 * 
 * @returns     Resource in that box
 */
Resource* Inventory::GetBoxMut(int row, int col) {
    return boxes[row][col].get();
}

/**
 * @brief               Setter for a box, with Resource in argument list
 * 
 * @param row           Row of desired box
 * @param col           Col of desired box
 * @param count         Qunatity of resource to set
 * @param resourceType  Resource to be moved into the inventory
 */
void Inventory::SetBox(int row, int col, int count, enum ResourceType resourceType) {
    std::unique_ptr<Resource> res;
    switch (resourceType) {
        case RESOURCE_TYPE_NONE:
            break;
        case RESOURCE_TYPE_WOOD:
            res = std::make_unique<Wood>(GetPosn(), count);
            break;
    
        default:
            break;
    }
    boxes[row][col] = std::move(res);
    Vector2 boxPosn = GetPosn(row, col);
    boxes[row][col]->SetPosn({boxPosn.x+float(BOX_SIZE-RESOURCE_SIZE)/2, boxPosn.y+float(BOX_SIZE-RESOURCE_SIZE)/2});
}

/**
 * @brief               Puts Resource of a certain count into the inventory, accounting for spills and resourceTypes
 * 
 * @param count         Count of Resource to insert
 * @param resourceType  Type of Resource to insert
 */
void Inventory::PutResource(int count, enum ResourceType resourceType) {
    if (resourceType == RESOURCE_TYPE_NONE) {
        // Ignore empty requests
        return;
    }

    bool isPut = false;

    // Iterate over all boxes to find place for the Resource
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            if (boxes[row][col] && boxes[row][col]->GetResourceType() != resourceType) {
                continue;
            }
            if (!boxes[row][col]) {
                SetBox(row, col, 0, resourceType);
            }

            int transferCount = RESOURCE_MAX_COUNT-boxes[row][col]->GetCount();
            if (transferCount>=count) {
                boxes[row][col]->SetCount(boxes[row][col]->GetCount()+count);
                isPut = true;
                break;
            } else {
                count -= transferCount;
                boxes[row][col]->SetCount(RESOURCE_MAX_COUNT);
            }
        }
        if (isPut) break;
    }

    // If not puttable anywhere in the inventory, discard
}

/**
 * @brief       Deletes Resource in a box
 * 
 * @param row   Row of desired box
 * @param col   Col of desired box
 */
void Inventory::DeleteItem(int row, int col) {
    boxes[row][col] = nullptr;
}

/**
 * @brief           Camera-adjusting drawing function for Inventory (& Resources in it)
 * 
 * @param camera    Global camera, relative to which the inventory is to be drawn
 */
void Inventory::Draw(const TopCamera& camera) const {
    const int InventoryWidth = cols * BOX_SIZE;
    const int InventoryHeight = rows * BOX_SIZE;

    DrawRectangle(posn.x-camera.posn.x, posn.y-camera.posn.y, InventoryWidth, InventoryHeight, BOX_BGCOLOUR);

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            // Draw each box and its underlying Resource (if it exists)
            Vector2 boxposn = {float(posn.x + col * BOX_SIZE), float(posn.y + row * BOX_SIZE)};
            DrawRectangleLinesEx (
                {
                    boxposn.x-camera.posn.x, 
                    boxposn.y-camera.posn.y, 
                    float(BOX_SIZE), 
                    float(BOX_SIZE)
                }, 
                BOX_BORDER_WIDTH, 
                BOX_EDGECOLOUR
            );
            if (boxes[row][col] != nullptr) {
                boxes[row][col]->Draw(camera);
            }
        }
    }
}

/**
 * @brief   Camera-agnostic drawing function for Inventory (& Resources in it)
 */
void Inventory::Draw() const {
    TopCamera c;
    c.Init();

    Draw(c);
}