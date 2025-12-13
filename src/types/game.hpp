#include "raylib.h"
#include "worldMap.hpp"
#include "player.hpp"
#include "topcamera.hpp"

class Game {
    int fps;
    int frameCount;
    WorldMap worldMap;
    Player player;
    TopCamera camera;

    void HandleEvents();
    void Update();
    void Draw();

public:
    Game();
    ~Game();
    void Run();
};