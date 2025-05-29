//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef LOADER_H
#define LOADER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>

#include "map/LTexture.hpp"
#include "map/Map.hpp"
#include "map/Tilemap.hpp"
#include "entities/Player.hpp"

#include "generator/MapGenerator.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

struct TextureInfo {
    std::string fileName;
    LTexture* texture;
};

class Loader {

    public:

        Loader();
        ~Loader();

        bool init();

        bool loadMedia();

        void close();

        SDL_Renderer* getRenderer();

    private:

        int screenWidth;
        int ScreenHeight;

        SDL_Window* gWindow;
    
        SDL_Renderer* gRenderer;

        SDL_FRect* camera;

        MapGenerator* genMap;

        std::list<TextureInfo*> textures;

};

#endif