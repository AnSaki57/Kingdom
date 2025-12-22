#include "game.hpp"
#include "raylib.h"
#include "resource_dir.h"
#include "assets.hpp"
// #include "wood.hpp" // TODO: Remove this after the introduction of the inventory class, and its integration with entities
#include "resource.hpp"

/**
 * @brief   Initialises the Raylib window context
*/
Game::Game() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(3840, 2160, "Kingdom v0.2");
    ToggleFullscreen();
	SearchAndSetResourceDir("assets");

	fps = 40;
	SetTargetFPS(fps);
    frameCount = 0;
}

/**
 * @brief   Initialises the various classes of the game
 */
void Game::Init() {     
    Assets::LoadAll();  // Initialises static sprites of used by all members of various classes

    worldMap.Init();
    entityManager.Init();
    camera.Init();

    // TODO: Delete these 2 lines after integrating inventories into other Entitys
    // inventory.Init(2, 3, {800, 800});
    // inventory.SetBox(1, 1, 5, wood);
}

/**
 * @brief   Destroys the Raylib context
*/
Game::~Game() {
    Assets::UnloadAll();
    CloseWindow();
}

/**
 * @brief   Takes in key/mouse presses and reacts accordingly
*/
void Game::HandleEvents() {
    camera.MotionCapture();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosn = {GetMousePosition().x+camera.GetPosn().x, GetMousePosition().y+camera.GetPosn().y};
        resourceManager.Delete(mousePosn);
    }
}

/**
 * @brief   Executes computations in a single frame
*/
void Game::Update() {
    std::vector<Vector2> newChunksPosns = worldMap.GenerateChunks(camera);
    entityManager.GenerateEntities(newChunksPosns);
    entityManager.CheckCollisions(camera);
    std::vector<std::tuple<Vector2, int, ResourceType>> returnResources = entityManager.Update(camera);
    for (const auto& [posn, count, resourceType] : returnResources) {
        Vector2 appendPosn = {posn.x+(TILE_SIZE-RESOURCE_SIZE)/2, posn.y+(TILE_SIZE-RESOURCE_SIZE)/2};
        resourceManager.Append(appendPosn, count, resourceType);
    }
}

/**
 * @brief   Encapsulates the overall drawing context for Raylib, calls Draw for members as well
*/
void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    worldMap.Draw(camera);
    resourceManager.Draw(camera);
    entityManager.Draw(camera);

    // inventory.Draw(camera);

    EndDrawing();
}

/**
 * @brief   Contains the overall game loop
*/
void Game::Run() {
    while (!WindowShouldClose()) {
        HandleEvents();
        Update();
        Draw();
        frameCount++;
    }
}