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
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>

#include "map/LTexture.hpp"

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

        static Loader * getLoader();    

        bool init();

        bool loadMedia();

        bool loadTextures();

        bool loadMap();

        void close();

        void setRenderer(SDL_Renderer* ren);

        int getScreenWidth();
        int getScreenHeight();

        LTexture* getTexture(std::string name);

        SDL_FRect* getCamera();

        SDL_Renderer* getRenderer();

    private:

        Loader(int screenW, int screenH, int mapS);
        ~Loader();

        static Loader* singleton;

        int screenWidth;
        int screenHeight;
        int mapSize;

        SDL_Window* window;
    
        SDL_Renderer* renderer;

        SDL_FRect camera;

        MapGenerator* genMap;

        std::list<TextureInfo*> textures;

};

#endif