#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"

/**
 * A bundle of all the static assets used in the game
 * 
 * Responsibilities:
 *  - Holds static copies of all the assets in the games
 */
class Assets {
public:
    inline static Font sansSerifBold;

    static void LoadAll();
    static void UnloadAll();
};

#endif