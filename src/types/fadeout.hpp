#include "raylib.h"
#include "topcamera.hpp"
#include <iostream>

/**
 * Displays messages on the screen that slowly fade out
 * 
 * Responsibilities:
 *  - Maintains its copy of the font
 *  - Keeps track of which and how many more frames there are to its animation
 *  - Informs whether it is done displaying the message, and can safely be deleted
 * 
 * Non-responsibilities:
 *  - Not responsible for its own deletion
 */
class Fadeout {
    static Font font;
    std::string msg;
    Color colour;
    int fontSize;
    int currFrame;
    int frameCount;
    Vector2 posn;
    Vector2 velocity;

public:
    Fadeout(int frameCount_, int fontSize_);
    void Init(std::string msg_, Color colour_, Vector2 posn_, Vector2 velocity_);
    static void SetFont(Font font_);
    Vector2 GetFontMeasure(std::string str);
    void Update();
    void Draw(const TopCamera& camera) const;
    bool CanDelete() const;
};

/**
 * @brief   Lists the common types of Fadeouts that can be created; used by the FadeoutManager
 */
enum FadeoutType{
    FADEOUT_TYPE_PLAIN,
    FADEOUT_TYPE_XP,
    FADEOUT_TYPE_PLAYER_DAMAGE,
    FADEOUT_TYPE_ANNOUNCEMENT
};