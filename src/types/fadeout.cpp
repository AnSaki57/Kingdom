#include "fadeout.hpp"

Font Fadeout::font;

/**
 * @brief               Constructor for the Fadeout class
 * 
 * @param frameCount_   No. of frames the Fadeout should last
 * @param fontSize_     Size of the font of the Fadeout
 */
Fadeout::Fadeout(int frameCount_, int fontSize_) : frameCount(frameCount_), fontSize(fontSize_) {}

/**
 * @brief           Initaliser for an object of the class
 * 
 * @param msg_      The message to be displayed
 * @param colour_   Colour of the message
 * @param posn_     Position of the Fadeout
 * @param velocity_ Velocity (speed and direction) of the Fadeout from its initial position
 */
void Fadeout::Init(std::string msg_, Color colour_, Vector2 posn_, Vector2 velocity_) {
    msg = msg_;
    colour = colour_;
    posn = posn_;
    velocity = velocity_;
    currFrame = 0;
}

/**
 * @brief       Static setter for the font of the class
 * 
 * @param font_ Font of the class
 */
void Fadeout::SetFont(Font font_) { font = font_; }

/**
 * @brief       Gets the dimensions of a potential string with the given font
 * 
 * @param str   String whose dimensions are to be measured
 */
Vector2 Fadeout::GetFontMeasure(std::string str) {
    return MeasureTextEx(font, str.c_str(), fontSize, fontSize/10);
}

/**
 * @brief   Frame-by-frame updation of the Fadeout
 */
void Fadeout::Update() { 
    if (currFrame<frameCount) {
        posn = {posn.x+velocity.x, posn.y+velocity.y};
        currFrame++; 
    }
}

/**
 * @brief           Draws the Fadeout on the screen
 * 
 * @param camera    Drawing context for the Fadeout
 */
void Fadeout::Draw(const TopCamera& camera) const {
    double opacity = 255 * (1 - (double)currFrame/frameCount);
    Color fadedColour = colour;
    fadedColour.a = opacity;

    DrawTextEx(font, msg.c_str(), {posn.x-camera.GetPosn().x, posn.y-camera.GetPosn().y}, fontSize, fontSize/10, fadedColour);
}

/**
 * @brief   Details if this Fadeout is past its period-of-use, or not
 * 
 * @returns Boolean true if this object can be deleted, and false otherwise
 */
bool Fadeout::CanDelete() const {
    if (currFrame < frameCount) return false;
    return true;
}