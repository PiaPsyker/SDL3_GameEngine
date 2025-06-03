//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//
#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include "../LTexture.hpp"
#include "../Loader.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Sprite {

    public:

        Sprite(std::string spriteName, int x, int y, int sz, SDL_FRect* cam, LTexture* tex = nullptr);

        void setPosition(int x, int y);

        LTexture* getSpriteTex();

    private:

        LTexture* spriteTex;
        SDL_FRect* camera;

        int posX;
        int posY;

        int mapX;
        int mapY;

        int size;

};

#endif