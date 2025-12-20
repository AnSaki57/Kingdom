#include "game.hpp"
#include "raylib.h"
#include "resource_dir.h"
#include "assets.hpp"
#include "wood.hpp" // TODO: Remove this after the introduction of the inventory class, and its integration with the player
#include "resource.hpp"
#include <iostream>
#include <thread>

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
    player.Init();
    camera.Init();

    // TODO: Delete these 2 lines after integrating inventories into other Entitys
    inv.Init(2, 3, {400, 400});
    inv.SetBox(0, 0, std::make_unique<Wood>(inv.GetPosn(), 5));
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
}

/**
 * @brief   Executes computations in a single frame
*/
void Game::Update() {
    worldMap.GenerateChunks(camera);
    player.Update();
}

/**
 * @brief   Encapsulates the overall drawing context for Raylib, calls Draw for members as well
*/
void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    worldMap.Draw(camera);
    player.Draw(camera);

    inv.Draw(camera);

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