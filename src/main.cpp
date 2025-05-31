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
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
//#include <iostream>

#include "map/LTexture.hpp"
//#include "map/Map.hpp"
#include "map/Tilemap.hpp"
#include "entities/Player.hpp"
#include "generator/MapGenerator.hpp"

#include "Loader.hpp"

//---------------------------------------------------------//
/* Constants */
//---------------------------------------------------------//

#define s 48
#define MAP_SIZE 128

//---------------------------------------------------------//
/* Function Prototypes */
//---------------------------------------------------------//

void handleInput(bool* quit);

//---------------------------------------------------------//
/* Global Variables */
//---------------------------------------------------------//

Map* gMap{nullptr};

Tilemap* gTilemap{nullptr};

Player* gPlayer{nullptr};

LTexture* gTextTexture{nullptr};

MapGenerator* mapEngine{nullptr};

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
                    break;
                case SDLK_DOWN:
                    gPlayer->move(0, 1);
                    break;
                case SDLK_LEFT:
                    gPlayer->move(-1, 0);
                    break;
                case SDLK_RIGHT:
                    gPlayer->move(1, 0);
                    break;
                case SDLK_E:
                    mapEngine->getMap()->saveMap();
                    break;
                case SDLK_S:
                    //mapEngine->getMap()->~Map();
                    mapEngine->getMap()->loadMap("./build/testMap");
                    break;
                case SDLK_R:
                    mapEngine->generateMap();
                    gPlayer->setMap(mapEngine->getMap());
                    break;
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

            //Move this into its own class thingy?
            gTextTexture = new LTexture(loader->getRenderer());

            SDL_Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF };
            std::string text;
            
            TTF_Font* gFont;
            gFont = loader->getFont("ByteBounce.ttf");
            
            gTextTexture->loadFromText(gFont, text, textColor);
            gTextTexture->setPosition(10,10);

            //---------------------------------------------------------//

            mapEngine = new MapGenerator(128, 128);
            mapEngine->generateMap();

            // Player creation in Map creation? or rather in loader?
            gPlayer = new Player("sprite.png", 1, 1, 48, 0, loader->getCamera());
            gPlayer->setMap(mapEngine->getMap());

            while(quit == false) {

                SDL_RenderClear(loader->getRenderer());
                gTextTexture->loadFromText(gFont, text, textColor );
                text = "PX: " + std::to_string(gPlayer->getMapX()) +
                    " | PY: " + std::to_string(gPlayer->getMapY()) +
                    " || GPX:" + std::to_string(gPlayer->getPosX()) +
                    " | GPY: "  + std::to_string(gPlayer->getPosY());

                handleInput(&quit);
                
                mapEngine->getMap()->renderLayers();

                gPlayer->render();

                gTextTexture->render();

                SDL_RenderPresent(loader->getRenderer());

            }
        }
    }

    gTextTexture->free();
    
    loader->~Loader();

    return exitCode;

}