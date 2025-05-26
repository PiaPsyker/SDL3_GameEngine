#include "Tilemap.hpp"
#include <SDL3/SDL_log.h>
#include <fstream>
#include <iostream>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Tilemap::Tilemap(int w, int h, int ts) {

    tilemapWidth = w;
    tilemapHeight = h;
    tileSize = ts;

    configMap = new std::string[tilemapWidth * tilemapHeight];

    map = new int*[tilemapWidth];

    for (int i = 0; i < tilemapWidth; i++) {
        
        map[i] = new int[tilemapHeight];

        for(int j = 0; j < tilemapHeight; j++) {
        
            map[i][j] = 0;
        
        }
    }
}

void Tilemap::processTileSet(std::string cpath) {

    std::ifstream cmap(cpath);

    if(!cmap.is_open()) {

        SDL_Log("Error opening Tilemap Config file");

    } else {

        std::string s;
        int count = 0;

        while(getline(cmap, s)){

            configMap[count] = s;
            count++;

        }

        std::cout << "Build configMap from " << cpath << " with following data:" << std::endl;
        
        for(int i = 0; i < tilemapWidth * tilemapHeight; i++){

            std::cout << "Index " << i << " : " << configMap[i] << std::endl;

        }
    }
}

int** Tilemap::getMap(){

    // for (int i = 0; i < tilemapWidth; i++) {

    //     for(int j = 0; j < tilemapHeight; j++) {
        
    //         std::cout << map[i][j] << std::endl;
        
    //     }
    // }

    return map;

}