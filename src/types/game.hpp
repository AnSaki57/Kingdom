#include "worldMap.hpp"
#include "entityManager.hpp"
#include "resourceManager.hpp"
#include "topcamera.hpp"
// #include "inventory.hpp"    // TODO: Delete this after incorporating into Entity objects
#include "fadeoutManager.hpp"

enum GameState {
    GAME_STATE_PAUSED,
    GAME_STATE_RUNNING,
    GAME_STATE_OVER
};

/**
 * Overall game class to encapsulate all of the game elements
 * 
 * Responsibilities:
 *  - Runs the core game loop
 *  - Manages the initiation and destruction of the map, the Player, and the camera
 */
class Game {
    int frameCount;
    double borderSize = 1;
    int worldLevel = 0;
    std::pair<int, int> tilePosn, chunkPosn;

    Music introMusic, music;
    GameState gameState = GAME_STATE_PAUSED;
    WorldMap worldMap;
    ResourceManager resourceManager;
    EntityManager entityManager;
    FadeoutManager fadeoutManager;
    TopCamera camera;
    // Inventory inventory;    // TODO: Delete this after incorporating into Entity objects

    void HandleEvents();
    void Update();
    void Draw();
    void DrawGameOver();

public:
    Game();
    ~Game();
    
    void Init();
    void Run();
};