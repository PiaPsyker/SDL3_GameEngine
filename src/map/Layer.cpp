#include "Layer.hpp"
#include <fstream>
#include <iostream>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Layer::Layer(LTexture* sheet) {

    tileArray[0][0] = {nullptr};
    tileSheet = sheet;
    
}

bool Layer::isMoveable(int x, int y) {

    if(x >= 0 && x < 16 && y >= 0 && y < 16){

        return tileArray[x][y]->isMoveable();

    }

    return false;

}

//---------------------------------------------------------//

void Layer::processTileSet(std::string tpath, std::string cpath) {

    std::ifstream tmap(tpath);
    std::ifstream cmap(cpath);



}

//---------------------------------------------------------//

void Layer::readTileMap(std::string path) {

    std::ifstream f(path);
    std::string s;
    char c;

    if(!f.is_open()) {

        SDL_Log("Error opening tilemap");

    } else {

        char c;
        char c2[271];
        int arr[15][15];

        int count = 0;
        while(f.get(c)){

            c2[count] = c;
            count++;

        }

        int i = 0;
        int j = 0;

        for(int k = 0; k <= sizeof(c2); k++) {
            if(c2[k] != '\n') {
                arr[i][j] = (int)c2[k] - 48 ;
                i++;
            } else {
                j++;
                i = 0;
            }
        }
        for(int x = 0; x <= 15; x++){
            for(int y = 0; y <= 15; y++) {

                map[x][y] = arr[x][y];

            }
        }
    }
    
    f.close();

}

void Layer::loadTileMap() {
    for(int i = 0; i <= 15; i++) {
        for(int j = 0; j <= 15; j++) {

            tileArray[i][j] = new Tile(tileSheet, map[i][j], 48.f, true);
            tileArray[i][j]->setPosition(i* 48, j * 48);
            tileArray[i][j]->render();

        }
    }
}

