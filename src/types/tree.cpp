#include <iostream>
#include <chrono>
#include "tree.hpp"
#include "../constants.hpp"

Texture2D Tree::sprite;
bool Tree::isTextureLoaded = false;

Tree::Tree() {
    posn = {0,0};
    hp = 100.0;
    level = 1;

    getTexture();   // Automatically initialises the sprite, if not initialised 
}

void Tree::SetPosn(Vector2 posn_) {
    this->posn = posn_;
}

Tree::Tree(Vector2 posn_) : Tree() {
    this->SetPosn(posn_);
    std::cout << YELLOW_TEXT << "Tree relocated to (" << posn.x << ", " << posn.y << ")\n" << RESET_TEXT;
}

const Texture2D& Tree::getTexture() {
    if (!isTextureLoaded) {
        Image imgsprite = LoadImage("Trees.jpg");

        if (!IsImageValid(imgsprite)) {
            std::cerr << "Tree img not found\n";
        } else {
            std::cout << YELLOW_TEXT << "Tree loaded successfully\n" << RESET_TEXT;
        }
        ImageCrop(&imgsprite, {100, 300, 300, 400});
        ImageResize(&imgsprite, TILE_SIZE, TILE_SIZE);
        sprite = LoadTextureFromImage(imgsprite);
        UnloadImage(imgsprite);

        isTextureLoaded = true;
    }

    return sprite;
} 

void Tree::Draw(const TopCamera& camera) {
    if (camera.isObjOnScreen(posn)) {
        DrawTexture(getTexture(), posn.x-camera.posn.x, posn.y-camera.posn.y, WHITE);
    }
}