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
        camera.MotionCapture(borderSize);

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

    tilePosn.first = int((camera.GetPosn().x+GetScreenWidth()/2)/(TILE_SIZE));
    tilePosn.second = int((camera.GetPosn().y+GetScreenWidth()/2)/(TILE_SIZE));
    chunkPosn.first = int((camera.GetPosn().x+GetScreenWidth()/2)/(CHUNK_SIZE*TILE_SIZE));
    chunkPosn.second = int((camera.GetPosn().y+GetScreenWidth()/2)/(CHUNK_SIZE*TILE_SIZE));
    
    if (int(frameCount) % int(FRAMES_PER_SECOND*60*2 / 8) == 0) {
        worldLevel++;
    }

    std::vector<Vector2> newChunksPosns = worldMap.GenerateChunks(camera);

    int distanceDifficultyOffset = 3 * std::max(std::abs(chunkPosn.first), std::abs(chunkPosn.second));
    entityManager.GenerateEntities(newChunksPosns, worldLevel+distanceDifficultyOffset);

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
        entityManager.SpawnEnemies(camera, worldLevel);
    }

    if (borderSize<20)
        borderSize += 0.001;
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

    Color borderColour = RED;
    if (int(frameCount/FRAMES_PER_SECOND)%2 == 0)
        borderColour = YELLOW;
    DrawRectangleLinesEx({
        float(-TILE_SIZE*CHUNK_SIZE*borderSize-camera.GetPosn().x), 
        float(-TILE_SIZE*CHUNK_SIZE*borderSize-camera.GetPosn().y), 
        float(2*TILE_SIZE*CHUNK_SIZE*borderSize), 
        float(2*TILE_SIZE*CHUNK_SIZE*borderSize)
    }, 8, borderColour);

    std::string TilePosn = "Tile coords [" 
        + std::to_string(tilePosn.first) + ", "
        + std::to_string(tilePosn.second) + "]";
    DrawText(TilePosn.c_str(), 100, 100, 35, BLACK);
    std::string ChunkPosn = "Chunk coords [" 
        + std::to_string(chunkPosn.first) + ", "
        + std::to_string(chunkPosn.second) + "]";
    DrawText(ChunkPosn.c_str(), 100, 150, 35, BLACK);

    if (gameState == GAME_STATE_OVER) {
        DrawGameOver();
    }

    EndDrawing();
}

/**
 * @brief   Draws the "Game Over" screen after the player ends
 */
void Game::DrawGameOver() {
    const int width = 2000;
    const int height = 1200;
    const int fontSize = 250;
    DrawRectangle((GetScreenWidth()-width)/2, (GetScreenHeight()-height)/2, width, height, {230, 41, 0, 180});
    const std::string gameOverText = "GAME OVER";
    int textlen = MeasureText(gameOverText.c_str(), fontSize);
    DrawText(gameOverText.c_str(), (GetScreenWidth()-textlen)/2, (GetScreenHeight()-fontSize)/2, fontSize, WHITE); 

    // Add stats at the bottom
    const int subtextFontSize = 70;
    std::vector<int> countStats = entityManager.GetCountStats();
    for (int i = 0; i < countStats.size(); i++) {
        std::string text;
        switch (i) {
        case COUNTSTAT_PLAYER_LEVEL:
            text = "Player Level: " + std::to_string(countStats[COUNTSTAT_PLAYER_LEVEL]);
            break;
        case COUNTSTAT_ENEMIES_KILLED:
            text = "Enemies Killed: " + std::to_string(countStats[COUNTSTAT_ENEMIES_KILLED]);
            break;
        case COUNTSTAT_TREES_DESTROYED:
            text = "Trees Decimated: " + std::to_string(countStats[COUNTSTAT_TREES_DESTROYED]);
            break;
        case COUNTSTAT_WOOD_COLLECTED:
            text = "Wood Collected: " + std::to_string(countStats[COUNTSTAT_WOOD_COLLECTED]);
            break;
        
        default:
            break;
        }

        DrawText(text.c_str(), (GetScreenWidth()-width+subtextFontSize)/2, (GetScreenHeight()+fontSize+subtextFontSize)/2+i*(subtextFontSize*3)/2, subtextFontSize, WHITE);
    }
}

/**
 * @brief   Contains the overall game loop
*/
void Game::Run() {
    while (!WindowShouldClose()) {
        HandleEvents();
        Draw();
        if (gameState == GAME_STATE_PAUSED || gameState == GAME_STATE_OVER) {
            continue;
        }
        Update();
        frameCount++;
    }
}