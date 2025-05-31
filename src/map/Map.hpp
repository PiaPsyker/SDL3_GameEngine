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
#include "Tilemap.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Map{

    public:

        Map();
        ~Map();

        void addLayer(Tilemap* layer);

        bool isMoveable(int x, int y, int layer_id);

        void renderLayers();

        void generateMap(int** index, int z);

        void saveMap();

        void loadMap(std::string path);

    private:

        Tilemap* layers[5];

        std::string mapName;

        int layer_count;

};

#endif