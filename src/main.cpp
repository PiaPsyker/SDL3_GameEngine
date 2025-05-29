//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

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

#include "noise/FractalNoise.hpp"

//---------------------------------------------------------//
/* Constants */
//---------------------------------------------------------//

#define s 48

constexpr int kScreenWidth{1920};
constexpr int kScreenHeight{1080};

constexpr float upX = 0.f;
constexpr float upY = s;

constexpr float downX = 0.f;
constexpr float downY = 0.f;

constexpr float leftX = s;
constexpr float leftY = 0.f;

constexpr float rightX = s;
constexpr float rightY = s;

//---------------------------------------------------------//
/* Function Prototypes */
//---------------------------------------------------------//

bool init();

bool loadMedia();

void handleInput(bool* quit);

void close();

//---------------------------------------------------------//
/* Global Variables */
//---------------------------------------------------------//

SDL_Window* gWindow{nullptr};
    
SDL_Renderer* gRenderer{nullptr};

SDL_FRect camera{ 0.f, 0.f, kScreenWidth, kScreenHeight };

LTexture* playerTex;
LTexture* backgroundTex;

Map* gMap{nullptr};

Tilemap* gTilemap{nullptr};

Player* gPlayer{nullptr};

FractalNoise *noiseMaker = new FractalNoise();


//---------------------------------------------------------//
/* Function Implementation */
//---------------------------------------------------------//

bool init() {
    
    bool success{true};

    if(!SDL_Init(SDL_INIT_VIDEO)) {

        SDL_Log("SDL couldnt initialize! SDL Error: %s\n", SDL_GetError());
        return false;

    }

    if(!SDL_CreateWindowAndRenderer("SDL3 Text", kScreenWidth, kScreenHeight, SDL_WINDOW_FULLSCREEN, &gWindow, &gRenderer)) {

        SDL_Log("Window couldnt be created! SDL Error: %s\n", SDL_GetError());
        return false;

    }

    // SDL_SetRenderVSync( gRenderer, ( true ) ? 1 : SDL_RENDERER_VSYNC_DISABLED );

    return success;

}

//---------------------------------------------------------//

bool loadMedia() {
    
    playerTex = new LTexture(gRenderer);
    backgroundTex = new LTexture(gRenderer);

    bool success{true};

    if(success = playerTex->loadFromFile("resources/sprite.png"); !success) {
        SDL_Log("Couldnt load PNG image");
    }
    if(success = backgroundTex->loadFromFile("resources/tileset.png"); !success) {
        SDL_Log("Couldnt load PNG image");
    }

    //-----------------------------------------------------//

    playerTex->setClip(downX,downY,s,s);

    gPlayer = new Player(playerTex, 6, 6, s, 0, &camera);

    gMap = new Map();
    
    gTilemap = new Tilemap(backgroundTex, 17, 17, s, &camera);
    gTilemap->processTileSet("resources/tileset.txt");
    gTilemap->loadTileMap("tilemaps/test.txt");
    gTilemap->setTileMap();

    gMap->addLayer(gTilemap);

    gPlayer->setMap(gMap);
    
    noiseMaker->setBaseFrequency(.25f);
    noiseMaker->setBaseAmplitude(.25f);
    noiseMaker->setOctaves(1);

    return success;

}

//---------------------------------------------------------//

void handleInput(bool* quit) {

    SDL_Event e;
    SDL_zero(e);

    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_EVENT_QUIT){
            *quit = true;
        } else if(e.type == SDL_EVENT_KEY_DOWN){
            switch(e.key.key){
                case SDLK_UP:
                    gPlayer->move(0, -1);
                    playerTex->setClip(upX,upY,s,s);
                    std::cout << abs((int)((noiseMaker->noise(gPlayer->getMapX(), gPlayer->getMapY(), .10f)) * 100)) << std::endl;
                    break;
                case SDLK_DOWN:
                    gPlayer->move(0, 1);
                    playerTex->setClip(downX,downY,s,s);
                    std::cout << abs((int)((noiseMaker->noise(gPlayer->getMapX(), gPlayer->getMapY(), .10f)) * 100)) << std::endl;
                    break;
                case SDLK_LEFT:
                    gPlayer->move(-1, 0);
                    playerTex->setClip(leftX,leftY,s,s);
                    std::cout << abs((int)((noiseMaker->noise(gPlayer->getMapX(), gPlayer->getMapY(), .10f)) * 100)) << std::endl;
                    break;
                case SDLK_RIGHT:
                    gPlayer->move(1, 0);
                    playerTex->setClip(rightX,rightY,s,s);
                    std::cout << abs((int)((noiseMaker->noise(gPlayer->getMapX(), gPlayer->getMapY(), .10f)) * 100)) << std::endl;
                    break;
            }
        }
    }
}

//---------------------------------------------------------//

void close() {

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    SDL_Quit();

}

//---------------------------------------------------------//
/* Main Loop */
//---------------------------------------------------------//

int main(int argc, char* args[]) {

    int exitCode{0};

    if(!init()){

        SDL_Log("Unable to init");
        exitCode = 1;

    } else {

        if(!loadMedia()) {

            SDL_Log("Unable to load media");
            exitCode = 2;

        } else {

            bool quit{false};

            

            while(quit == false) {

                SDL_RenderClear(gRenderer);

                camera.x = static_cast<int>( gPlayer->getPosX() + gPlayer->getSprite()->getWidth() / 2 - kScreenWidth / 2 );
                camera.y = static_cast<int>( gPlayer->getPosY() + gPlayer->getSprite()->getHeight() / 2 - kScreenHeight / 2 );

                handleInput(&quit);
                
                gMap->renderLayers();

                gPlayer->render();

                SDL_RenderPresent(gRenderer);

            }
        }
    }

    close();

    return exitCode;

}