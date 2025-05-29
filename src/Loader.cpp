#include "Loader.hpp"
#include "map/LTexture.hpp"
#include <SDL3/SDL_render.h>
#include <filesystem>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Loader::Loader() {



}

bool Loader::init() {
    
    bool success{true};

    if(!SDL_Init(SDL_INIT_VIDEO)) {

        SDL_Log("SDL couldnt initialize! SDL Error: %s\n", SDL_GetError());
        return false;

    }

    if(!SDL_CreateWindowAndRenderer("SDL3 Text", screenWidth, ScreenHeight, SDL_WINDOW_FULLSCREEN, &gWindow, &gRenderer)) {

        SDL_Log("Window couldnt be created! SDL Error: %s\n", SDL_GetError());
        return false;

    }

    SDL_SetRenderVSync( gRenderer, ( true ) ? 1 : SDL_RENDERER_VSYNC_DISABLED );

    genMap = new MapGenerator(128, 128);

    return success;

}

bool Loader::loadMedia() {

    bool success{true};

    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("resources")) {

        

        if(dirEntry.path().extension() == ".png") {

            LTexture* tempTex = new LTexture(gRenderer);
            tempTex->setCamera(camera);
            tempTex->loadFromFile(dirEntry.path());

            TextureInfo* tex = new TextureInfo{dirEntry.path().filename(), tempTex};

            textures.push_front(tex);

            std::cout << "Added Texture: " << dirEntry.path().filename() << std::endl;
    
        }
    }

    return success;

}

void Loader::close() {

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    for(TextureInfo* texInfo : textures) {
        texInfo->texture->free();
    }

    SDL_Quit();

}

void Loader::setRenderer(SDL_Renderer* ren) {

    gRenderer = ren;

}

SDL_Renderer* Loader::getRenderer() {

    return gRenderer;

}