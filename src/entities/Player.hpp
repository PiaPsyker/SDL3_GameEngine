//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "../map/LTexture.hpp"
#include "../map/Map.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Player {

    public:

        Player(LTexture* spr, int x, int y, int sz, int z);

        void move(int x, int y);

        void setMap(Map* m);

        bool checkCollision(int x, int y);

        void render();

    private:

        LTexture* sprite;
        
        Map* map;

        int size;
        int z_index;
        int posX,posY;
        int mapX, mapY;

};

#endif