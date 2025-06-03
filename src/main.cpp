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
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "Loader.hpp"
#include "Timer.hpp"

#include "entities/Enemy.hpp"
#include "map/Tilemap.hpp"
#include "entities/Player.hpp"
#include "entities/Enemy.hpp"
#include "generator/MapGenerator.hpp"
#include "ui/UIHandler.hpp"


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
Enemy* gEnemy{nullptr};

UIHandler* uiEngine{nullptr};

Loader* loader;

float mx = -1.f, my = -1.f;
std::string positionText;
std::string tileInfoText;
std::string timeText;

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
                case SDLK_W:
                    gPlayer->move(0, -1);
                    uiEngine->setElementText("position",&positionText);
                    break;
                case SDLK_S:
                    gPlayer->move(0, 1);
                    uiEngine->setElementText("position",&positionText);
                    break;
                case SDLK_A:
                    gPlayer->move(-1, 0);
                    uiEngine->setElementText("position",&positionText);
                    break;
                case SDLK_D:
                    gPlayer->move(1, 0);
                    uiEngine->setElementText("position",&positionText);
                    break;
                case SDLK_F5:
                    loader->getMapEngine()->getMap()->saveMap();
                    break;
                case SDLK_F9:
                    std::cout << "Enter Map Name to load: " << std::endl;
                    std::cin >> mapName;
                    loader->getMapEngine()->getMap()->loadMap(mapName);
                    break;
                case SDLK_R:
                    loader->getMapEngine()->generateMap();
                    gPlayer->setMap(loader->getMapEngine()->getMap());
                    break;
            }
        } else if(e.type == SDL_EVENT_MOUSE_BUTTON_DOWN || e.type == SDL_EVENT_MOUSE_MOTION) {

            SDL_GetMouseState( &mx, &my );
            tileInfoText = loader->getMapEngine()->getMap()->getTileInfo((int)((mx + gPlayer->getPosX()) / 48) - 19,(int)((my + gPlayer->getPosY()) / 48) - 10, 1);
            uiEngine->setElementText("tileInfo",&tileInfoText);
            uiEngine->setElementText("position",&positionText);

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

            timeText = "Not yet started!";
            tileInfoText = "No Tile selected!";
            positionText = "No Position loaded!";

            uiEngine = new UIHandler();
            
            uiEngine->newElement("position","ByteBounce.ttf", &positionText, 10, 10);
            uiEngine->newElement("tileInfo","ByteBounce.ttf", &tileInfoText, 10, 50);
            uiEngine->newElement("timeInfo","ByteBounce.ttf", &timeText, 10, 90);

            //---------------------------------------------------------//

            loader->getMapEngine()->generateMap();
            
            gEnemy = new Enemy("sprite2.png", 2, 2, 48, 1, loader->getCamera());
            gEnemy->setMap(loader->getMapEngine()->getMap());
            
            // Move this to Map somehow? or at least have Map set Player position?
            gPlayer = new Player("sprite.png", 1, 1, 48, 1, loader->getCamera());
            gPlayer->setMap(loader->getMapEngine()->getMap());

            Timer fpsTimer;
            Timer capTimer;

            Uint64 renderedFrames = 0;
            Uint64 renderingNS = 0;
            fpsTimer.start(); 

            while(quit == false) {
       
                capTimer.start();

                SDL_RenderClear(loader->getRenderer());
                
                uiEngine->setElementText("timeInfo",&timeText);

                positionText = "PX: " + std::to_string(gPlayer->getMapX()) +
                    " | PY: " + std::to_string(gPlayer->getMapY()) +
                    " || GPX:" + std::to_string(gPlayer->getPosX()) +
                    " | GPY: "  + std::to_string(gPlayer->getPosY()) +
                    " || MX: " + std::to_string((int)((mx + gPlayer->getPosX()) / 48) - 19) + 
                    " | MY: " + std::to_string((int)((my + gPlayer->getPosY()) / 48) - 10);

                handleInput(&quit);
                
                if( renderedFrames != 0 ) {
                    
                    timeText = "FPS: " + std::to_string(static_cast<double>( renderedFrames ) / ( static_cast<double>( renderingNS ) / 1000000000.0 )); 

                }

                loader->getMapEngine()->getMap()->renderLayers();

                gPlayer->render();
                gEnemy->render();

                uiEngine->render();

                SDL_RenderPresent(loader->getRenderer());

                //---------------------------------------------------------//

                renderingNS = fpsTimer.getTicksNS();
                renderedFrames++;

                Uint64 frameNs = capTimer.getTicksNS();
                constexpr Uint64 nsPerFrame = 1000000000 / 60;

                if(frameNs < nsPerFrame) {

                   SDL_DelayNS(nsPerFrame - frameNs);

                }
            }
        }
    }

    std::cout << "Freeing Memory..." << std::endl; 
    
    uiEngine->~UIHandler();

    loader->~Loader();

    std::cout << "Done" << std::endl;
    std::cout << "Closing..." << std::endl;
    std::cout << "Goodbye :3" << std::endl;

    return exitCode;


}