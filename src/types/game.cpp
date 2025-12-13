#include "game.hpp"
#include "resource_dir.h"

Game::Game() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(1600, 900, "Kingdom v0.1");
	ToggleBorderlessWindowed();

	SearchAndSetResourceDir("assets");

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
    if (frameCount % (fps * 3) == 0) {
        worldMap.GenerateChunks(camera);
    }
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
        std::cout << frameCount << "," << camera.posn.y << " ";
    }
}