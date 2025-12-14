#pragma once

// #include "raylib.h"
#include <string>

// Fill in with useful game constants
#define SCALING_FACTOR float(/*GetMonitorWidth(GetCurrentMonitor()) / 1600*/2.4)
#define TILE_SIZE 40 * SCALING_FACTOR
#define TILE_BORDER_SIZE 2 * SCALING_FACTOR

const std::string RESET_TEXT    = "\033[0m";
const std::string RED_TEXT      = "\033[31m";      /* Red */
const std::string GREEN_TEXT    = "\033[32m";      /* Green */
const std::string YELLOW_TEXT   = "\033[33m";      /* Yellow */
const std::string BLUE_TEXT     = "\033[34m";      /* Blue */
const std::string MAGENTA_TEXT  = "\033[35m";      /* Magenta */
const std::string CYAN_TEXT     = "\033[36m";      /* Cyan */
const std::string WHITE_TEXT    = "\033[37m";      /* White */