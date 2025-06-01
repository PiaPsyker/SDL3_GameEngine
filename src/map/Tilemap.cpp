#include "Tilemap.hpp"
#include "LTexture.hpp"
#include "Tile.hpp"
#include <SDL3/SDL_rect.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Tilemap::Tilemap(LTexture* tex, int w, int h, int ts, SDL_FRect* cam) {

    tilemapWidth = w;
    tilemapHeight = h;
    tileSize = ts;
    tilemapTex = tex;
    camera = cam;

    configMap = new config[tilemapWidth * tilemapHeight];

    indexMap = new int*[tilemapWidth];
    tileArray = new Tile**[tilemapWidth];

    for (int i = 0; i < tilemapWidth; i++) {
        
        indexMap[i] = new int[tilemapHeight];
        tileArray[i] = new Tile*[tilemapHeight];

    }
}

Tilemap::~Tilemap() {

    for(int i = 0; i < tilemapWidth; i++){

        for(int j = 0; j < tilemapHeight; j++) {

            delete tileArray[i][j];

        }

        free(indexMap[i]);
        free(tileArray[i]);

    }

    free(tileArray);
    free(indexMap);

    delete[] configMap;

}


//---------------------------------------------------------//

void Tilemap::processTileSet(std::string cpath) {

    std::ifstream configFile(cpath);

    if(!configFile.is_open()) {

        SDL_Log("Error opening Tilemap Config file");

    } else {

        std::string s;
        int count = 0;

        while(getline(configFile, s)){

            std::stringstream fullLine(s);
            std::string delimitedString;
            char del = '|';

            int i = 0;

            while(getline(fullLine,delimitedString,del)){

                std::stringstream temp;
                int tempInt;

                if(i == 0) {

                    temp << delimitedString;
                    temp >> tempInt;
                    configMap[count].index = tempInt;
                    tempInt = -1;

                } else if(i == 1) {

                    configMap[count].name = delimitedString;

                } else if(i == 2) {

                    temp << delimitedString;
                    temp >> tempInt;
                    configMap[count].moveable = (bool)tempInt;
                    tempInt = -1;

                } else if(i == 3) {

                    temp << delimitedString;
                    temp >> tempInt;
                    configMap[count].interaction = (bool)tempInt;
                    tempInt = -1;

                }

                i++;

            }



            count++;

        }
    }

    configFile.close();

}

//---------------------------------------------------------//

void Tilemap::loadTileMap(std::string path) {

    std::ifstream mapFile(path);

    if(!mapFile.is_open()) {

        SDL_Log("Error opening Tilemap Map file");

    } else {

        char c;
        
        while(mapFile.get(c)) {

            configSettings.push_front(c);

        }

        configSettings.reverse();
    }
    
    mapFile.close();
    
}

//---------------------------------------------------------//

void Tilemap::setTileMap() {

    int i = 0;
    int j = 0;

    int i1;
    int i2;
    int i3;

    int count = 0;

    for(char ch : configSettings) {

        if(ch != '|' && ch != '\n') {

            if(count == 0) {

                i1 = (int)ch - 48;
                count++;

            }
            else if(count == 1) {

                i2 = i1 * 10;
                i2 += (int)ch - 48;
                count++;

            } else if(count == 2) {

                i3 = i2 * 10;
                i3 += (int)ch - 48;
                indexMap[i][j] = i3;
                //std::cout << "Adding : " << i3 << " to indexMap[" << i << "][" << j << "] " << std::endl;

            }
        } else if(ch == '|') {

            count = 0;
            i++;

        } else if (ch == '\n') {

            j++;
            i = 0;
            count = 0;

        }
    }

    for(int x = 0; x < tilemapWidth; x++){

        for(int y = 0; y < tilemapHeight; y++) {

            tileArray[x][y] = new Tile(tilemapTex, -1, tileSize, true, 6, camera);
            tileArray[x][y]->setPosition(x * tileSize, y * 48);
            tileArray[x][y]->init(indexMap[x][y], tileSize, configMap[indexMap[x][y]].moveable, 6);

        }
    }
}

//---------------------------------------------------------//

void Tilemap::setGeneratedTileMap(int** index) {

    for(int x = 0; x < tilemapWidth; x++){

        for(int y = 0; y < tilemapHeight; y++) {

            indexMap[x][y] = index[x][y];

            tileArray[x][y] = new Tile(tilemapTex, index[x][y], tileSize, true, 6, camera);
            tileArray[x][y]->setPosition(x * tileSize, y * 48);
            tileArray[x][y]->init(index[x][y], tileSize, configMap[index[x][y]].moveable, 6);

        }
    }
}


//---------------------------------------------------------//

void Tilemap::renderTileMap() {

    for(int i = 0; i < tilemapWidth; i++){

        for(int j = 0; j < tilemapHeight; j++) {

            tileArray[i][j]->render();

        }
    }
}

//---------------------------------------------------------//

bool Tilemap::isMoveable(int x, int y) {

    if(x >= 0 && x < tilemapWidth && y >= 0 && y < tilemapHeight){

        return tileArray[x][y]->isMoveable();

    }

    return false;

}

//---------------------------------------------------------//

int** Tilemap::getMap(){

    return indexMap;

}

std::string Tilemap::getTileInfo(int x, int y) {

    if(x < 0 || x >= tilemapWidth || y < 0 || y >= tilemapHeight) {
        return "Out of bounds!";
    }else {

        int tempIndex = indexMap[x][y];

        for(int i = 0; i < (tilemapWidth * tilemapHeight); i++) {

            if(configMap[i].index == tempIndex) {

                return configMap[i].name;

            }
        }
    }
    
    return "Not Found!";

}

//---------------------------------------------------------//

void Tilemap::saveTileMap(std::string path) {

    std::fstream outputFile;

    outputFile.open(path, std::ios::out);

    int i = 0;
    int j = 0;

    while(i != tilemapWidth && j != tilemapHeight) {
        
        std::string outputIndex;

        int index = indexMap[i][j];

        if(index < 10 ) {

            outputIndex = "00" + std::to_string(index);
            outputFile << outputIndex;
            i++;

        } else if(index >= 10 && index <= 99) {

            outputIndex = "0" + std::to_string(index);
            outputFile << outputIndex;
            i++;

        } else {

            outputIndex = std::to_string(index);
            outputFile << outputIndex;
            i++;

        }
        if(i == tilemapWidth) {

            outputFile << "\n";
            j++;
            i = 0;

        } else {

            outputFile << "|";

        }
    }

    outputFile.close();

}

//---------------------------------------------------------//