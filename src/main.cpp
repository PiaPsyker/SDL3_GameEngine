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
#include <SDL3/SDL_timer.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <sstream>
//#include <iostream>

#include "map/LTexture.hpp"
//#include "map/Map.hpp"
#include "map/Tilemap.hpp"
#include "entities/Player.hpp"
#include "generator/MapGenerator.hpp"
#include "Timer.hpp"

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
LTexture* tileInfoTexture{nullptr};
LTexture* timeTexture{nullptr};

MapGenerator* mapEngine{nullptr};

Loader* loader;

float mx = -1.f, my = -1.f;
std::string tileInfo;
std::stringstream timeText;

//---------------------------------------------------------//
/* Function Implementation */
//---------------------------------------------------------//

void handleInput(bool* quit) {

    SDL_Event e;
    SDL_zero(e);
    std::string mapName;

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
                    std::cout << "Enter Map Name to load: " << std::endl;
                    std::cin >> mapName;
                    mapEngine->getMap()->loadMap(mapName);
                    break;
                case SDLK_R:
                    mapEngine->generateMap();
                    gPlayer->setMap(mapEngine->getMap());
                    break;
            }
        } else if(e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            SDL_GetMouseState( &mx, &my );
            tileInfo = mapEngine->getMap()->getTileInfo((int)((mx + gPlayer->getPosX()) / 48) - 19,(int)((my + gPlayer->getPosY()) / 48) - 10, 1);
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
            tileInfoTexture = new LTexture(loader->getRenderer());
            timeTexture = new LTexture(loader->getRenderer());

            SDL_Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF };
            std::string text;
            
            TTF_Font* gFont;
            gFont = loader->getFont("ByteBounce.ttf");
            
            gTextTexture->loadFromText(gFont, text, textColor);
            gTextTexture->setPosition(10,10);

            tileInfoTexture->loadFromText(gFont, tileInfo, textColor);
            tileInfoTexture->setPosition(10,50);

            timeTexture->loadFromText(gFont, timeText.str(), textColor);
            timeTexture->setPosition(10,90);

            //---------------------------------------------------------//

            mapEngine = new MapGenerator(128, 128);
            mapEngine->generateMap();

            // Player creation in Map creation? or rather in loader?
            gPlayer = new Player("sprite.png", 1, 1, 48, 1, loader->getCamera());
            gPlayer->setMap(mapEngine->getMap());

            Timer fpsTimer;
            Timer capTimer;

            Uint64 renderedFrames = 0;
            Uint64 renderingNS = 0;
            fpsTimer.start();
            //double seconds;

            while(quit == false) {
       
                capTimer.start();

                SDL_RenderClear(loader->getRenderer());

                gTextTexture->loadFromText(gFont, text, textColor );
                tileInfoTexture->loadFromText(gFont, tileInfo, textColor );

                SDL_GetMouseState( &mx, &my );

                text = "PX: " + std::to_string(gPlayer->getMapX()) +
                    " | PY: " + std::to_string(gPlayer->getMapY()) +
                    " || GPX:" + std::to_string(gPlayer->getPosX()) +
                    " | GPY: "  + std::to_string(gPlayer->getPosY()) +
                    " || MX: " + std::to_string((int)((mx + gPlayer->getPosX()) / 48) - 19) + 
                    " | MY: " + std::to_string((int)((my + gPlayer->getPosY()) / 48) - 10);

                handleInput(&quit);
                
                if( renderedFrames != 0 ) {
                    
                    timeText.str("");
                    //std::cout << "Seconds pass: " << seconds << std::endl;
                    //seconds += static_cast<double>(renderingNS) / 1000000000.0;
                    timeText << "FPS: " << static_cast<double>( renderedFrames ) / ( static_cast<double>( renderingNS ) / 1000000000.0 ); 
                    timeTexture->loadFromText(gFont, timeText.str().c_str(), textColor );

                }

                mapEngine->getMap()->renderLayers();

                gPlayer->render();

                gTextTexture->render();
                tileInfoTexture->render();
                timeTexture->render();

                SDL_RenderPresent(loader->getRenderer());

                renderingNS = fpsTimer.getTicksNS();
                renderedFrames++;

                Uint64 frameNs = capTimer.getTicksNS();
                constexpr Uint64 nsPerFrame = 1000000000 / 30;

                if(frameNs < nsPerFrame) {
                   SDL_DelayNS(nsPerFrame - frameNs);
                }
            }
        }
    }

    gTextTexture->~LTexture();
    tileInfoTexture->~LTexture();
    timeTexture->~LTexture();

    loader->~Loader();

    return exitCode;

}