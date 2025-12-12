/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "types/chunk.hpp"
#include "types/grasstile.hpp"
#include "types/mudtile.hpp"
#include "types/player.hpp"
#include <iostream>

int main () {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(1600, 900, "Kingdom v0.1");
	ToggleBorderlessWindowed();
	SearchAndSetResourceDir("assets");

	constexpr int FPS = 40;
	SetTargetFPS(FPS);

	TopCamera camera({0,0});

	Chunk::TileCreator grassTileCreator = [](Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_) {
		return std::make_unique<GrassTile>(posn, std::move(tileEntity_));
	};
	Chunk::TileCreator mudTileCreator = [](Vector2 posn, std::unique_ptr<StationaryEntity> tileEntity_) {
		return std::make_unique<MudTile>(posn, std::move(tileEntity_));
	};

	Chunk grassChunk(grassTileCreator, {200, 200});
	Chunk mudChunk(mudTileCreator, {200 + CHUNK_SIZE * TILE_SIZE, 200 + CHUNK_SIZE * TILE_SIZE});

	Player player;

	// game loop
	while (!WindowShouldClose()) {
		// Events
		camera.Move();

		// drawing
		BeginDrawing();
		ClearBackground(BLACK);

		// Draw here
		grassChunk.Draw(camera);
		mudChunk.Draw(camera);
		player.Draw(camera);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup

	CloseWindow();
	return 0;
}
