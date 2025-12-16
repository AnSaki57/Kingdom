#include "raylib.h"

/**
 * General-purpose class to draw any kind of progress bar (health bars, cooldown, etc.)
 * 
 * Responsibilities:
 *  - Holds aesthetic design (shape and colours)
 *  - Maintains value of fill ratio
 */
class ProgressBar{
    Rectangle posn;
    double borderWidth;
    Color bgColour;
    Color fillColour;
    Color borderColour;
    double fill;

public:
    ProgressBar(Rectangle posn_, double borderWidth_, Color bgColour_, Color fillColour_, Color borderColour_, double fill_); 
    double getFill() const;
    void setFill(double fill_);

    void Draw() const;
};