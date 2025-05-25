#include "Layer.hpp"
#include "Tile.hpp"
#include <iostream>
#include <fstream>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Layer::Layer(LTexture* sheet) {

    tileArray[0][0] = {nullptr};
    tileSheet = sheet;
    
}

// void Layer::setTileSheet(LTexture* sheet) {

//     tileSheet = sheet;

// }

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

        std::cout << c2 << std::endl;

        int i = 0;
        int j = 0;

        for(int k = 0; k <= sizeof(c2); k++) {
            if(c2[k] != '\n'){
                //std::cout << i << (int)c - 48 << std::endl;
                arr[i][j] = (int)c2[k] - 48 ;
                i++;
                //std::cout << (int)c - 48 << std::endl;
            } else {
                j++;
                i = 0;
            }
        }

        

        for(int x = 0; x <= 15; x++){
            for(int y = 0; y <= 15; y++) {
                map[x][y] = arr[x][y];
                //std::cout << map[x][y] << std::endl;
            }
        }
        //std::cout << map[1][0] << std::endl;
    }
    
    //std::cout << tileArray[2][2]->isMoveable() << std::endl;
    
    f.close();
}

void Layer::renderTileMap() {
    for(int i = 0; i <= 15; i++) {
        for(int j = 0; j <= 15; j++) {
            tileArray[i][j] = new Tile(tileSheet, map[i][j], 32.f, true);
            tileArray[i][j]->setPosition(i* 32, j * 32);
            tileArray[i][j]->render();
        }
    }
}

