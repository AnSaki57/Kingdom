#include "fadeoutManager.hpp"
#include "../constants.hpp"

/**
 * @brief   Initialiser for the Fadeout manager (as of now, no function)
 */
void FadeoutManager::Init() {}

/**
 * @brief               Puts a message with all the necessary parameters
 * 
 * @param msg           The intended message to display
 * @param colour        Colour of the message
 * @param posn          Position of the message
 * @param velocity      Rate at which the message should move (if not needed, set to {0,0})
 * @param frameCount    No. of frames the message should last
 * @param fontSize      Font size of the message
 */
void FadeoutManager::PutMessage(std::string msg, Color colour, Vector2 posn, Vector2 velocity, int frameCount, int fontSize) {
    Fadeout fadeout(frameCount, fontSize);
    fadeout.Init(msg, colour, posn, velocity);
    fadeouts.push_back(fadeout);
}

/**
 * @brief               Puts a message based on the type of the Fadeout
 * 
 * @param fadeoutType   Type of the Fadeout
 * @param msg           Message to be displayed
 * @param posn          Position of the message
 */
void FadeoutManager::PutMessage(FadeoutType fadeoutType, std::string msg, Vector2 posn) {
    switch (fadeoutType) {
        case FADEOUT_TYPE_PLAIN: {
            PutMessage(msg, WHITE, posn, {0,-1}, FRAMES_PER_SECOND*2.5, 30);
            break;
        }
        case FADEOUT_TYPE_XP: {
            PutMessage("+"+msg+"XP", BLUE, posn, {0,-1}, FRAMES_PER_SECOND*2.5, 30);
            break;
        }
        case FADEOUT_TYPE_PLAYER_DAMAGE: {
            PutMessage("-"+msg+"HP", RED, posn, {0,-1}, FRAMES_PER_SECOND*5, 40);
            break;
        }
        case FADEOUT_TYPE_ANNOUNCEMENT: {
            Fadeout fadeout(FRAMES_PER_SECOND*5, 130);
            Vector2 msgPosn = {float(GetScreenWidth()-fadeout.GetFontMeasure(msg).x)/2+posn.x, float(GetScreenHeight()-fadeout.GetFontMeasure(msg).y)/2+posn.y};


            fadeout.Init(msg, WHITE, msgPosn, {0,0});
            fadeouts.push_back(fadeout);
            break;
        }
        
        default:
            break;
    }
}

/**
 * @brief   Frame-by-frame updation of the FadeoutManager
 */
void FadeoutManager::Update() {
    for (int i = fadeouts.size()-1; i >= 0; i--) {
        // Clean stale fadeouts
        if (fadeouts[i].CanDelete()) {
            fadeouts.erase(fadeouts.begin()+i);
            continue;
        }
        
        fadeouts[i].Update();
    }
}

/**
 * @brief           Draws the Fadeouts to the screen
 * 
 * @param camera    Drawing context for the fadeouts
 */
void FadeoutManager::Draw(const TopCamera& camera) {
    for (const auto& fadeout : fadeouts) {
        fadeout.Draw(camera);
    }
}