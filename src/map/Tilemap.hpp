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
#include "Tile.hpp"

//---------------------------------------------------------//

struct config{
    int index;
    std::string name;
    bool moveable;
    bool interaction;
};

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Tilemap {

    public:

        Tilemap(LTexture* tex, int w, int h, int ts, SDL_FRect* cam);

        void processTileSet(std::string cpath);

        void loadTileMap(std::string path);

        void setTileMap();

        void renderTileMap();

        bool isMoveable(int x, int y);

        int** getMap();

    private:

        int tilemapWidth;
        int tilemapHeight;
        int tileSize;

        LTexture* tilemapTex;
        SDL_FRect* camera;
        
        Tile*** tileArray;

        std::string* configMap;
        
        config* arr;

        std::list<char> t;
        int** map;

};

#endif