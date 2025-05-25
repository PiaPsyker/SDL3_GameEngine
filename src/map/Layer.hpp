//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef LAYER_H
#define LAYER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include "Tile.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Layer {

    public:

        Layer();

        bool isMoveable(float x, float y);

    private:

        Tile tileArray[16][16];

};

#endif