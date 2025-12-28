#include "game.hpp"
#include "raylib.h"
#include "resource_dir.h"
#include "assets.hpp"
#include "resource.hpp"
#include "../constants.hpp"

/**
 * @brief   Initialises the Raylib window context
*/
Game::Game() {
	srand(time(0));

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(3840, 2160, "Kingdom v0.2");
    ToggleFullscreen();
	SearchAndSetResourceDir("assets");
    
    InitAudioDevice();

    introMusic = LoadMusicStream("Music/song5.mp3");    // TODO: Integrate this by playing once before actual music
    music = LoadMusicStream("Music/song6.mp3");
    introMusic.looping = false;
    music.looping = true;

    PlayMusicStream(introMusic);

	SetTargetFPS(FRAMES_PER_SECOND);
    frameCount = 0;

    gameState = GAME_STATE_RUNNING;
}

/**
 * @brief   Initialises the various classes of the game
 */
void Game::Init() {     
    Assets::LoadAll();  // Initialises static sprites of used by all members of various classes

    worldMap.Init();
    entityManager.Init();
    camera.Init();
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
    
    // Handle game pause/play
    if (IsKeyPressed(KEY_SPACE)) {
        if (gameState == GAME_STATE_RUNNING) {
            gameState = GAME_STATE_PAUSED;
        } else if (gameState == GAME_STATE_PAUSED) {
            gameState = GAME_STATE_RUNNING;
        }
    }
    
    if (gameState == GAME_STATE_RUNNING) {
        camera.MotionCapture();

        // Pick up resources on left mouse click
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosn = {GetMousePosition().x+camera.GetPosn().x, GetMousePosition().y+camera.GetPosn().y};
            std::pair<int, ResourceType> returnResource = resourceManager.Delete(mousePosn);
            
            if (returnResource.second != RESOURCE_TYPE_NONE) {
                entityManager.PutResource(returnResource.first, returnResource.second);
            } else {
                entityManager.AttackDir(mousePosn, camera);
            }
        }
    }
}

/**
 * @brief   Executes computations in a single frame
*/
void Game::Update() {
    if (!IsMusicStreamPlaying(introMusic)) {
        if (!IsMusicStreamPlaying(music)) {
            PlayMusicStream(music);
        }
    }
    UpdateMusicStream(introMusic);
    UpdateMusicStream(music);

    int targetLevel = int(frameCount*15/(FRAMES_PER_SECOND*60*2));
    if (targetLevel == 0) targetLevel = 1;

    std::vector<Vector2> newChunksPosns = worldMap.GenerateChunks(camera); // If enemies too hard, change this
    entityManager.GenerateEntities(newChunksPosns, targetLevel);
    entityManager.CheckCollisions(camera);
    std::vector<std::tuple<Vector2, int, ResourceType>> returnResources = entityManager.Update(camera);
    for (const auto& [posn, count, resourceType] : returnResources) {
        if (resourceType == RESOURCE_TYPE_NONE) {
            continue;
        }
        Vector2 appendPosn = {posn.x+float(TILE_SIZE-RESOURCE_SIZE)/2, posn.y+float(TILE_SIZE-RESOURCE_SIZE)/2};
        resourceManager.Append(appendPosn, count, resourceType);
    }

    if (!entityManager.isPlayerAlive) {
        gameState = GAME_STATE_OVER;
    }

    if (frameCount % int(FRAMES_PER_SECOND * 60) == 0) {
        entityManager.SpawnEnemies(camera, targetLevel);
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

    EndDrawing();
}

/**
 * @brief   Contains the overall game loop
*/
void Game::Run() {
    while (!WindowShouldClose()) {
        HandleEvents();
        if (gameState == GAME_STATE_OVER) {
            break;
        }
        Draw();
        if (gameState == GAME_STATE_PAUSED) {
            continue;
        }
        Update();
        frameCount++;
    }
}