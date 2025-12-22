#pragma once

#include <string>

// Fill in with useful game constants
#define DEFAULT_MONITOR_WIDTH 3840
#define DEFAULT_MONITOR_HEIGHT 2160
#define SCALING_FACTOR float(GetScreenWidth()/1600.0)
#define TILE_SIZE 40 * SCALING_FACTOR
#define TILE_BORDER_SIZE 0.8 * SCALING_FACTOR

#define CHUNK_SIZE 32

#define RESOURCE_SIZE TILE_SIZE * 0.6

#define POPUP_CIRCLE_SIZE 6 * SCALING_FACTOR
#define POPUP_CIRCLE_COLOUR {240, 10, 10, 255}

#define BOX_SIZE float(TILE_SIZE * 1.2)
#define BOX_BORDER_WIDTH TILE_BORDER_SIZE * 2

#define BOX_BGCOLOUR {180, 90, 0, 255}
#define BOX_EDGECOLOUR {140, 70, 0, 255}

const std::string RESET_TEXT    = "\033[0m";
const std::string RED_TEXT      = "\033[31m";      /* Red */
const std::string GREEN_TEXT    = "\033[32m";      /* Green */
const std::string YELLOW_TEXT   = "\033[33m";      /* Yellow */
const std::string BLUE_TEXT     = "\033[34m";      /* Blue */
const std::string MAGENTA_TEXT  = "\033[35m";      /* Magenta */
const std::string CYAN_TEXT     = "\033[36m";      /* Cyan */
const std::string WHITE_TEXT    = "\033[37m";      /* White */