#include "Loader.hpp"
#include "map/LTexture.hpp"
#include <SDL3/SDL_render.h>
#include <filesystem>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Loader * Loader::singleton = nullptr;

Loader* Loader::getLoader() {
    
    if (Loader::singleton == nullptr) {
        Loader::singleton = new Loader(1920, 1080, 128);

    }
    return Loader::singleton;
}


Loader::Loader(int screenW, int screenH, int mapS):

    window{nullptr},
    renderer{nullptr}

{

    screenWidth = screenW;
    screenHeight = screenH;

    mapSize = mapS;    

    camera = { 0.f, 0.f, (float)screenWidth, (float)screenHeight };

    genMap = new MapGenerator(mapSize, mapSize);


}

bool Loader::init() {
    
    bool success{true};

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL couldnt initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    if(!SDL_CreateWindowAndRenderer("SDL3 Text", screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Window couldnt be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderVSync( renderer, ( true ) ? 1 : SDL_RENDERER_VSYNC_DISABLED );

    return success;

}

bool Loader::loadTextures() {

    bool success{true};

    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("resources")) {

        if(dirEntry.path().extension() == ".png") {

            LTexture* tempTex = new LTexture(renderer);
            tempTex->setCamera(&camera);
            tempTex->loadFromFile(dirEntry.path());

            TextureInfo* tex = new TextureInfo{dirEntry.path().filename(), tempTex};

            textures.push_front(tex);

            std::cout << "Added Texture: " << dirEntry.path().filename() << std::endl;
    
        }
    }

    return success;

}

void Loader::close() {

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow( window );
    window = nullptr;

    for(TextureInfo* texInfo : textures) {
        texInfo->texture->free();
    }

    SDL_Quit();

}

void Loader::setRenderer(SDL_Renderer* ren) {

    renderer = ren;

}

int Loader::getScreenWidth() {

    return screenWidth;

}

int Loader::getScreenHeight() {

    return screenHeight;

}

LTexture* Loader::getTexture(std::string name) {

    for(TextureInfo* tex : textures) {

        if(tex->fileName == name) {

            return tex->texture;

        }

    }

}

SDL_FRect* Loader::getCamera() {

    return &camera;

}

SDL_Renderer* Loader::getRenderer() {

    return renderer;

}