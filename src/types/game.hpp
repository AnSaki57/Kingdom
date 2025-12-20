#include "worldMap.hpp"
#include "player.hpp"
#include "topcamera.hpp"
#include "inventory.hpp"    // TODO: Delete this after incorporating into Entity objects

/**
 * Overall game class to encapsulate all of the game elements
 * 
 * Responsibilities:
 *  - Runs the core game loop
 *  - Manages the initiation and destruction of the map, the Player, and the camera
 */
class Game {
    int fps;
    int frameCount;
    WorldMap worldMap;
    Player player;
    TopCamera camera;
    Inventory inv;

    void HandleEvents();
    void Update();
    void Draw();

public:
    Game();
    ~Game();
    
    void Init();
    void Run();
};