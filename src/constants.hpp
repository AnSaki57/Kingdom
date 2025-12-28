#pragma once

#include <string>

// Fill this with useful game constants
constexpr double ONE_BY_ROOT2 = 0.707;

constexpr double DEFAULT_MONITOR_WIDTH = 3840;
constexpr double DEFAULT_MONITOR_HEIGHT = 2160;
constexpr double FRAMES_PER_SECOND = 40;
const double SCALING_FACTOR = 2.4;  // float(GetMonitorWidth(GetCurrentMonitor())/1600.0);
const double TILE_SIZE = 40 * SCALING_FACTOR;
const double TILE_BORDER_SIZE = 0.8 * SCALING_FACTOR;

constexpr double CHUNK_SIZE = 32;

const double RESOURCE_SIZE = TILE_SIZE * 0.6;
const double ENTITY_SIZE = TILE_SIZE * 0.8;
const double PROJECTILE_SIZE = TILE_SIZE * 0.1;

constexpr double BASE_LEVEL_MULTIPLIER = 1.03;
constexpr double BASE_ENTITY_HP = 100.0;
constexpr double BASE_ENTITY_ATTACK = 20.0;

const double CAMERA_SPEED = 8 * SCALING_FACTOR;
const double ENTITY_SPEED = 1 * SCALING_FACTOR;
const double ENEMY_SPEED = 1 * SCALING_FACTOR;
const double PROJECTILE_SPEED = 8 * SCALING_FACTOR;

const double POPUP_CIRCLE_SIZE = 6 * SCALING_FACTOR;
constexpr Color POPUP_CIRCLE_COLOUR = {240, 10, 10, 255};

constexpr double RESOURCE_MAX_COUNT = 25;

const double BOX_SIZE = float(TILE_SIZE * 1.2);
const double BOX_BORDER_WIDTH = TILE_BORDER_SIZE * 2;

const Color BOX_BGCOLOUR = {180, 90, 0, 255};
const Color BOX_EDGECOLOUR = {140, 70, 0, 255};

const std::string RESET_TEXT    = "\033[0m";
const std::string RED_TEXT      = "\033[31m";      /* Red */
const std::string GREEN_TEXT    = "\033[32m";      /* Green */
const std::string YELLOW_TEXT   = "\033[33m";      /* Yellow */
const std::string BLUE_TEXT     = "\033[34m";      /* Blue */
const std::string MAGENTA_TEXT  = "\033[35m";      /* Magenta */
const std::string CYAN_TEXT     = "\033[36m";      /* Cyan */
const std::string WHITE_TEXT    = "\033[37m";      /* White */