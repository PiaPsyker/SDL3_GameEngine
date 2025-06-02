//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//
#ifndef ENEMY_H
#define ENEMY_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "Entity.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Enemy : public Entity {

    public:

        using Entity::Entity;
        // Enemy();

};

#endif