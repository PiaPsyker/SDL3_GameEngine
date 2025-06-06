//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//
#ifndef PLAYERNEW_H
#define PLAYERNEW_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include "Entity.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Player : public Entity {

    public:

        using Entity::Entity;
        // Enemy();

        void move(int x, int y, int z);

};

#endif