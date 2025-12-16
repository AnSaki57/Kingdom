#include "game.hpp"
#include "raylib.h"
#include "resource_dir.h"
#include "tree.hpp"
#include <iostream>
#include <thread>

/**
 * @brief   Initialises the Raylib window context
*/
Game::Game() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(3840, 2160, "Kingdom v0.2");
	// ToggleBorderlessWindowed(); // Makes the window full-screen
    ToggleFullscreen();

	SearchAndSetResourceDir("assets");

    Tree::LoadSprite();         // Initialises static sprite of Tree class used by all members

    /* worldMap.Init();
    player.Init();
    camera.Init();*/

	fps = 40;
	SetTargetFPS(fps);
    frameCount = 0;

    // WaitTime(1.0);// std::chrono::seconds(1);
}

/**
 * @brief   Initialises the various classes of the game
 */
void Game::Init() {
    worldMap.Init();
    player.Init();
    camera.Init();
}

/**
 * @brief   Destroys the Raylib context
*/
Game::~Game() {
    Tree::UnloadSprite();
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