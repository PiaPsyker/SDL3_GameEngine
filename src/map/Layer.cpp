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

        getline(f,s);

        for(int i = 0; i <= 15; i++) {
            for(int j = 0; j <= 15; j++) {
                tileArray[i][j] = new Tile(tileSheet, 0, 32.f, true);
                tileArray[i][j]->setPosition(i* 32, j * 32);
                tileArray[i][j]->render();
            }
        }
    }
    
    //std::cout << tileArray[2][2]->isMoveable() << std::endl;
    
    f.close();
}

