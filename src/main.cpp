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
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>

#include "map/LTexture.hpp"
#include "map/Map.hpp"
#include "map/Tilemap.hpp"
#include "entities/Player.hpp"

//#include "generator/MapGenerator.hpp"

#include "Loader.hpp"

//---------------------------------------------------------//
/* Constants */
//---------------------------------------------------------//

#define s 48
#define MAP_SIZE 128

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

//SDL_Window* gWindow{nullptr};
    
//SDL_Renderer* gRenderer{nullptr};

//SDL_FRect camera{ 0.f, 0.f, kScreenWidth, kScreenHeight };
// 
// LTexture* playerTex;
// LTexture* backgroundTex;

Map* gMap{nullptr};

Tilemap* gTilemap{nullptr};

Player* gPlayer{nullptr};
LTexture* playerTex{nullptr};

TTF_Font* gFont{nullptr};
LTexture* gTextTexture{nullptr};

Loader* loader;

//---------------------------------------------------------//
/* Function Implementation */
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
                    //playerTex->setClip(upX,upY,s,s);
                    break;
                case SDLK_DOWN:
                    gPlayer->move(0, 1);
                    //playerTex->setClip(downX,downY,s,s);
                    break;
                case SDLK_LEFT:
                    gPlayer->move(-1, 0);
                    //playerTex->setClip(leftX,leftY,s,s);
                    break;
                case SDLK_RIGHT:
                    gPlayer->move(1, 0);
                    //playerTex->setClip(rightX,rightY,s,s);
                    break;
                case SDLK_E:
                    gMap->saveMap();
                    break;
                case SDLK_S:
                    gMap->loadMap("build/testMap");
            }
        }
    }
}

//---------------------------------------------------------//
/* Main Loop */
//---------------------------------------------------------//

int main(int argc, char* args[]) {

    int exitCode{0};

    loader = Loader::getLoader();

    if(!loader->init()){

        SDL_Log("Unable to init");
        exitCode = 1;

    } else {

        if(!loader->loadTextures()) {

            SDL_Log("Unable to load media");
            exitCode = 2;

        } else {

            bool quit{false};

            gTextTexture = new LTexture(loader->getRenderer());

            gTextTexture->setCamera(loader->getCamera());

            std::string fontPath = "resources/ByteBounce.ttf";
            SDL_Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF };
            gFont = TTF_OpenFont( fontPath.c_str(), 48 );
            std::string text;
            
            gTextTexture->setPosition(10,10);



            gPlayer = new Player("sprite.png", 1, 1, 48, 0, loader->getCamera());

            gMap = new Map();
    
            gTilemap = new Tilemap(loader->getTexture("tileset.png"), MAP_SIZE, MAP_SIZE, s, loader->getCamera());
            gTilemap->loadTileMap("build/currentMap.bin");
            gTilemap->processTileSet("resources/tileset.txt");
            gTilemap->setTileMap();

            gMap->addLayer(gTilemap);

            gPlayer->setMap(gMap);

            while(quit == false) {

                SDL_RenderClear(loader->getRenderer());
                gTextTexture->loadFromText(gFont, text, textColor );
                text = "PX: " + std::to_string(gPlayer->getMapX()) + " | PY: " + std::to_string(gPlayer->getMapY());

                handleInput(&quit);
                
                gMap->renderLayers();

                gPlayer->render();

                gTextTexture->render();

                SDL_RenderPresent(loader->getRenderer());

            }
        }
    }

    loader->close();

    return exitCode;

}