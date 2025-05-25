//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef MAP_H
#define MAP_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>
#include <list>
#include "Layer.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Map{

    public:

        Map();

    private:

        std::list<Layer *> layers;

};

#endif