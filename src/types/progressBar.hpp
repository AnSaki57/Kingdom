#include "raylib.h"

class TopCamera;

/**
 * General-purpose class to draw any kind of progress bar (health bars, cooldown, etc.)
 * 
 * Responsibilities:
 *  - Holds aesthetic design (shape and colours)
 *  - Maintains value of fill ratio
 */
class ProgressBar{
    Vector2 posn;
    double width;
    double height;
    double borderWidth;
    Color bgColour;
    Color fillColour;
    Color borderColour;
    double fill;

public:
    ProgressBar(Rectangle posn_, double borderWidth_, Color bgColour_, Color fillColour_, Color borderColour_, double fill_); 
    void SetPosn(Vector2 posn_);
    double GetFill() const;
    void SetFill(double fill_);

    void Draw(const TopCamera& camera) const;
    void Draw() const;
};