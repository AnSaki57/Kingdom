#pragma once

#include "raylib.h"

class TopCamera;

/**
 * List of types of Resources
 */
enum ResourceType{
    RESOURCE_TYPE_NONE,
    RESOURCE_TYPE_WOOD,
    RESOURCE_TYPE_STONE,
};

/**
 * Helper class to represent varying aspects of types of Resources
 */
struct ResourceStats {
    Texture2D sprite;
    enum ResourceType resourceType;
};

/**
 * Generic resource class that emulates a pile of a type of resource
 * 
 * Responsibilities:
 *  - Holds the font for displaying count as static member
 * 
 * Non-responsibilities:
 *  - Not responsible for sprite asset mgmt; done by children instead
 */
class Resource {
protected:
    Vector2 posn;
    int count;
    inline static Font countFont = {0};
    ResourceStats resourceStats = {Texture2D(), RESOURCE_TYPE_NONE};
public:

    Resource(Vector2 posn_, int count_, const ResourceStats resourceStats_);

    Vector2 GetPosn() const;
    void SetPosn(Vector2 posn_);
    int GetCount() const;
    void SetCount(int count_);
    enum ResourceType GetResourceType() const;

    static void SetFont(Font font_);
    virtual ~Resource() = default;
    virtual const Texture2D& GetSprite() const = 0;

    void Draw(const TopCamera& camera) const;
};