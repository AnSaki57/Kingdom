#include <iostream>
#include <chrono>
#include "tree.hpp"
#include "../constants.hpp"

Texture2D Tree::sprite;
bool Tree::isTextureLoaded = false;

Tree::Tree(Vector2 posn_) {
    posn = posn_;
    hp = 100.0;
    level = 1;
}

void Tree::LoadSprite() {
    if (!isTextureLoaded) {
        if (isTextureLoaded) return;

        Image imgsprite = LoadImage("Trees.jpg");

        if (!IsImageValid(imgsprite)) {
            std::cerr << "Tree img not found\n";
        } else {
            std::cout << YELLOW_TEXT << "Tree loaded successfully\n" << RESET_TEXT;
        }
        ImageCrop(&imgsprite, {90, 300, 300, 400});
        ImageResize(&imgsprite, TILE_SIZE, TILE_SIZE);
        sprite = LoadTextureFromImage(imgsprite);
        UnloadImage(imgsprite);

        isTextureLoaded = true;
    }
}

void Tree::UnloadSprite() {
    UnloadTexture(sprite);
}

void Tree::Draw(const TopCamera& camera) const {
    if (camera.isObjOnScreen(posn)) {
        DrawTexture(sprite, posn.x-camera.posn.x, posn.y-camera.posn.y, WHITE);
    }
}