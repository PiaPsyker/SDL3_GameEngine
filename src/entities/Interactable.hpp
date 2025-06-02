//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//
#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>


//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Interactable {

    public:

        virtual void interact(int x, int y, int z) {};

};

#endif