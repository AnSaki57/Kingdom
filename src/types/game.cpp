#include "game.hpp"
#include "resource_dir.h"
#include "tree.hpp"
#include <iostream>
#include <thread>

Game::Game() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(1600, 900, "Kingdom v0.1");
	ToggleBorderlessWindowed();

	SearchAndSetResourceDir("assets");

    Tree::LoadSprite();

    worldMap.Init();
    player.Init();
    camera.Init();

	fps = 40;
	SetTargetFPS(fps);
    frameCount = 0;
}

Game::~Game() {
    CloseWindow();
}


void Game::HandleEvents() {
    camera.Move();
}

void Game::Update() {
    worldMap.GenerateChunks(camera);
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    worldMap.Draw(camera);
    player.Draw(camera);

    EndDrawing();
}


void Game::Run() {
    while (!WindowShouldClose()) {
        HandleEvents();
        Update();
        Draw();
        frameCount++;
    }
}