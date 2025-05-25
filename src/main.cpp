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
#include <SDL3_image/SDL_image.h>
#include <string>
#include "map/LTexture.hpp"
#include "map/Tile.hpp"
#include "map/Layer.hpp"
#include "renderer/Presenter.hpp"

//---------------------------------------------------------//
/* Constants */
//---------------------------------------------------------//

constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

constexpr float upX = 0.f;
constexpr float upY = 48.f;

constexpr float downX = 0.f;
constexpr float downY = 0.f;

constexpr float leftX = 48.f;
constexpr float leftY = 0.f;

constexpr float rightX = 48.f;
constexpr float rightY = 48.f;

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

LTexture* playerTex;
LTexture* backgroundTex;

Presenter* gPresenter;

Tile* test_tile{nullptr};

Layer* test_layer{nullptr};

int px = 0;
int py = 0;

//---------------------------------------------------------//
/* Function Implementation */
//---------------------------------------------------------//

bool init() {
    
    bool success{true};

    if(!SDL_Init(SDL_INIT_VIDEO)) {

        SDL_Log("SDL couldnt initialize! SDL Error: %s\n", SDL_GetError());
        return false;

    }

    if(!SDL_CreateWindowAndRenderer("SDL3 Text", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer)) {

        SDL_Log("Window couldnt be created! SDL Error: %s\n", SDL_GetError());
        return false;

    }

    gPresenter = new Presenter();
    gPresenter->setRenderer(gRenderer);

    return success;

}

//---------------------------------------------------------//

bool loadMedia() {
    
    playerTex = new LTexture(gPresenter->getRenderer());
    backgroundTex = new LTexture(gPresenter->getRenderer());

    bool success{true};

    if(success = playerTex->loadFromFile("resources/sprite.png"); !success) {
        SDL_Log("Couldnt load PNG image");
    }
    if(success = backgroundTex->loadFromFile("resources/001-Grassland01.png"); !success) {
        SDL_Log("Couldnt load PNG image");
    }

    gPresenter->addRenderObject(playerTex);
    gPresenter->addRenderObject(backgroundTex);

    playerTex->setSize(48,48);
    playerTex->setClip(downX,downY,48,48);

    //
    test_layer = new Layer(backgroundTex);
    

    //test_tile = new Tile(backgroundTex, 0, 32.f, true);

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
                    playerTex->move(0.0f,-48.0f);
                    playerTex->setClip(upX,upY,48,48);
                    break;
                case SDLK_DOWN:
                    playerTex->move(0.0f,48.0f);
                    playerTex->setClip(downX,downY,48,48);
                    break;
                case SDLK_LEFT:
                    playerTex->move(-48.0f,0.0f);
                    playerTex->setClip(leftX,leftY,48,48);
                    break;
                case SDLK_RIGHT:
                    playerTex->move(48.0f,0.0f);
                    playerTex->setClip(rightX,rightY,48,48);
                    break;
            }
        }
    }
}

//---------------------------------------------------------//

void close() {

    gPresenter->free();

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

                handleInput(&quit);

                test_layer->readTileMap("tilemaps/test.txt");

                gPresenter->render();

            }
        }
    }

    close();

    return exitCode;

}