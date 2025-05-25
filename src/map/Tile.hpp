//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef TILE_H
#define TILE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include "LTexture.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Tile {

    public:

        Tile(LTexture* sprite = nullptr, int index=0, float spriteSize = 0.f, bool mv = true);

        bool isMoveable();

        void setPosition(float x, float y);

        void render();

    private:

        LTexture* spriteSheet;

        bool moveable;

        float posX;
        float posY;

};

#endif