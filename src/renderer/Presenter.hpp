
//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef PRESENTER_H
#define PRESENTER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <list>
#include "../map/LTexture.hpp"


//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Presenter{

    public:

        Presenter();    
        
        void setRenderer(SDL_Renderer* ren);

        void addRenderObject(LTexture* obj);

        void render();

        void free();

        SDL_Renderer* getRenderer();

    private:

        SDL_Renderer* mRenderer{nullptr};
        std::list<LTexture *> renderObjects;

};

#endif