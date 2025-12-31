#include "fadeout.hpp"
#include <vector>

/**
 * Manages all the Fadeouts on the Game
 */
class FadeoutManager {
    std::vector<Fadeout> fadeouts;

public:
    void Init();
    void PutMessage(std::string msg, Color colour, Vector2 posn, Vector2 velocity, int frameCount, int fontSize);
    void PutMessage(FadeoutType fadeoutType, std::string msg, Vector2 posn);
    void Update();
    void Draw(const TopCamera& camera);
};