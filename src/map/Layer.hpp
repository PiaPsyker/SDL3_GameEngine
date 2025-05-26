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
#include <string>
#include "LTexture.hpp"
#include "Tile.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Layer {

    public:

        Layer(LTexture* sheet = nullptr);

        bool isMoveable(int x, int y);

        void readTileMap(std::string path);

        void loadTileMap();

    private:

        int tileSize;

        LTexture* tileSheet;

        int map[15][15];

        Tile* tileArray[16][16];

};

#endif