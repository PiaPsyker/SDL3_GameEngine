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
#include <list>

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

struct Layer {

    int index;
    std::string tilemapName;
    std::string tilemapConfig;
    Tilemap* tilemap;

};

class Map{

    public:

        Map();
        ~Map();

        void addLayer(Tilemap* layer);

        bool isMoveable(int x, int y, int z_index);

        std::string getTileInfo(int x, int y, int z_index);

        void renderLayers();

        void generateMap(int** index, int z, std::string tileName);

        void saveMap(std::string name = "");

        void loadMap(std::string path);

    private:

        std::list<Layer*> layers;

        std::string mapName;

        int layer_count;

};

#endif