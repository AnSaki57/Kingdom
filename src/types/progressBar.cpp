#include "progressBar.hpp"
#include "topcamera.hpp"

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
  posn({posn_.x, posn_.y}), width(posn_.width), height(posn_.height), borderWidth(borderWidth_), bgColour(bgColour_), fillColour(fillColour_), borderColour(borderColour_), fill(fill_) {
    if (fill>1.0) fill = 1.0;
    if (fill<0.0) fill = 0.0;
}

/**
 * @brief   Setter for the ProgressBar based on position
 */
void ProgressBar::SetPosn(Vector2 posn_) {
    posn.x = posn_.x;
    posn.y = posn_.y;
}

/**
 * @brief   Getter for the fill ratio
 * 
 * @returns The fill ratio
 */
double ProgressBar::GetFill() const {
    return fill;
}

/**
 * @brief       Setter for the fill ratio
 * 
 * @param fill  The fill ratio
 */
void ProgressBar::SetFill(double fill_) {
    fill = fill_;
    if (fill>1.0) fill = 1.0;
    if (fill<0.0) fill = 0.0;
}

/**
 * @brief   The drawing function for the ProgressBar, for objects that move around the screen
 */
void ProgressBar::Draw(const TopCamera& camera) const {
    Rectangle innerPosn = {posn.x+float(borderWidth)-camera.posn.x, posn.y+float(borderWidth)-camera.posn.y, float(width-2*borderWidth), float(height-2*borderWidth)};
    DrawRectangleRec(innerPosn, bgColour);
    DrawRectangle(innerPosn.x, innerPosn.y, innerPosn.width * fill, innerPosn.height, fillColour);
    DrawRectangleLinesEx(innerPosn, float(borderWidth), borderColour);
}

/**
 * @brief   The drawing function for the ProgressBar, that stays still on the screen
 */
void ProgressBar::Draw() const {
    TopCamera camera;
    camera.Init();
    Draw(camera);
}