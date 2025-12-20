#pragma once

#include "raylib.h"

class TopCamera;

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
public:
    Resource(Vector2 posn_, int count_);

    Vector2 GetPosn() const;
    void SetPosn(Vector2 posn_);
    int GetCount() const;
    void SetCount(int count_);

    static void setFont();
    virtual ~Resource() = default;
    // virtual void setSprite() = 0;
    virtual const Texture2D& getSprite() const = 0;

    void Draw(const TopCamera& camera) const;
};