//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <fstream>
#include "../noise/FractalNoise.hpp"
#include "../map/Map.hpp"

//---------------------------------------------------------//

class MapGenerator {

    public:

        MapGenerator(int width, int height);
        ~MapGenerator();

        void regenerate(float fq, float amp);

        void generateMap();

        Map* getMap();

    private:

        FractalNoise* noiseEngine;
        int mapW;
        int mapH;

        Map* currentMap;

        int** indexMap;

        std::fstream outputFile;

};

#endif