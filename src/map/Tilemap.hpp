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
#include <list>
#include "LTexture.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Tilemap {

    public:

        Tilemap(int w, int h, int ts);

        void processTileSet(std::string cpath);

        void loadTileMap(std::string path);

        void setTileMap();

        int** getMap();

    private:

        int tilemapWidth;
        int tilemapHeight;
        int tileSize;

        LTexture* tilemapTex;
        
        std::string* configMap;
        std::list<char> t;
        int** map;

};

#endif