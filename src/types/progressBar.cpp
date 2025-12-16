#include "progressBar.hpp"

/**
 * @brief               Initialises the various aspects of the progress bar
 * 
 * @param posn          Size and shape of the bar
 * @param borderWidth   Thickness of the border line
 * @param bgColour      Colour of background, that is not filled in
 * @param fillColour    Colour of filled-in (active) ratio of bar
 * @param borderColour  Colour of border line
 * @param fill          Fill ratio
 */
ProgressBar::ProgressBar(Rectangle posn_, double borderWidth_, Color bgColour_, Color fillColour_, Color borderColour_, double fill_) : 
  posn(posn_), borderWidth(borderWidth_), bgColour(bgColour_), fillColour(fillColour_), borderColour(borderColour_), fill(fill_) {
    if (fill>1.0) fill = 1.0;
    if (fill<0.0) fill = 0.0;
}

/**
 * @brief   Getter for the fill ratio
 * 
 * @returns The fill ratio
 */
double ProgressBar::getFill() const {
    return fill;
}

/**
 * @brief       Setter for the fill ratio
 * 
 * @param fill  The fill ratio
 */
void ProgressBar::setFill(double fill_) {
    fill = fill_;
    if (fill>1.0) fill = 1.0;
    if (fill<0.0) fill = 0.0;
}

/**
 * @brief   The drawing function for the ProgressBar
 */
void ProgressBar::Draw() const {
    Rectangle innerPosn = {posn.x+float(borderWidth), posn.y+float(borderWidth), posn.width-2*float(borderWidth), posn.height-2*float(borderWidth)};
    DrawRectangleRec(innerPosn, bgColour);
    DrawRectangle(innerPosn.x, innerPosn.y, innerPosn.width * fill, innerPosn.height, fillColour);
    DrawRectangleLinesEx(posn, float(borderWidth), borderColour);
}