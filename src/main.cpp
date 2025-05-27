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
#include "map/Map.hpp"
#include "map/Tilemap.hpp"
#include "entities/Player.hpp"
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

LTexture* backgroundTex2;

Presenter* gPresenter;

Tile* test_tile{nullptr};

Layer* test_layer{nullptr};
Layer* test_layer2{nullptr};

Map* test_map{nullptr};

Tilemap* test_tilemap{nullptr};

Player* test_player{nullptr};

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
    backgroundTex2 = new LTexture(gPresenter->getRenderer());

    bool success{true};

    if(success = playerTex->loadFromFile("resources/sprite.png"); !success) {
        SDL_Log("Couldnt load PNG image");
    }
    if(success = backgroundTex->loadFromFile("resources/Outside_A5.png"); !success) {
        SDL_Log("Couldnt load PNG image");
    }
    if(success = backgroundTex2->loadFromFile("resources/Outside_B.png"); !success) {
        SDL_Log("Couldnt load PNG image");
    }

    playerTex->setSize(48,48);
    playerTex->setClip(downX,downY,48,48);

    test_player = new Player(playerTex, 0, 0, 48, 0);

    //-------------------------------------

    test_layer = new Layer(backgroundTex);
    test_layer2 = new Layer(backgroundTex2);
    
    test_layer->readTileMap("tilemaps/test2.txt");
    test_layer2->readTileMap("tilemaps/test2.txt");

    test_map = new Map();
    
    test_map->addLayer(test_layer);
    test_map->addLayer(test_layer2);

    test_player->setMap(test_map);

    test_tilemap = new Tilemap(backgroundTex, 17, 17, 48);
    test_tilemap->processTileSet("tilemaps/Dungeon_A1.txt");
    test_tilemap->loadTileMap("tilemaps/test.txt");
    test_tilemap->setTileMap();
    //test_tilemap->getMap();
    
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
                    test_player->move(0, -1);
                    playerTex->setClip(upX,upY,48,48);
                    break;
                case SDLK_DOWN:
                    test_player->move(0, 1);
                    playerTex->setClip(downX,downY,48,48);
                    break;
                case SDLK_LEFT:
                    test_player->move(-1, 0);
                    playerTex->setClip(leftX,leftY,48,48);
                    break;
                case SDLK_RIGHT:
                    test_player->move(1, 0);
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

                //test_map->renderLayers();
                test_tilemap->renderTileMap();

                test_player->render();

                gPresenter->render();

            }
        }
    }

    close();

    return exitCode;

}