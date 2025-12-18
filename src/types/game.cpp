#include "game.hpp"
#include "raylib.h"
#include "resource_dir.h"
#include "assets.hpp"
#include "tree.hpp"
#include <iostream>
#include <thread>

/**
 * @brief   Initialises the Raylib window context
*/
Game::Game() : wood({200, 300}, 15) {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(3840, 2160, "Kingdom v0.2");
    ToggleFullscreen();
	SearchAndSetResourceDir("assets");

    Tree::LoadSprite();         // Initialises static sprite of Tree class used by all members
    Assets::LoadAll();

	fps = 40;
	SetTargetFPS(fps);
    frameCount = 0;
}

/**
 * @brief   Initialises the various classes of the game
 */
void Game::Init() {
    worldMap.Init();
    player.Init();
    camera.Init();

    wood.setSprite();   // TODO: Remove this after the introduction of the inventory class, and its integration with the player
}

/**
 * @brief   Destroys the Raylib context
*/
Game::~Game() {
    Tree::UnloadSprite();
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

    wood.Draw(camera);

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