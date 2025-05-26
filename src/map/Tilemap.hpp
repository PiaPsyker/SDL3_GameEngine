//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "LTexture.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Tilemap {

    public:

        Tilemap(int w, int h, int ts);

        void processTileSet(std::string cpath);

        int** getMap();

    private:

        int tilemapWidth;
        int tilemapHeight;
        int tileSize;

        LTexture* tilemapTex;
        
        std::string* configMap;
        int** map;

};

#endif