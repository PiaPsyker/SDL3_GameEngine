#include "Tilemap.hpp"
#include <fstream>
#include <iostream>
#include <string>

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

    }
}

//---------------------------------------------------------//

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

//---------------------------------------------------------//

void Tilemap::loadTileMap(std::string path) {

    std::ifstream f(path);

    if(!f.is_open()) {
        SDL_Log("Error opening Tilemap Map file");
    } else {
        char c;
        
        while(f.get(c)) {
        
            std::cout << "Adding " << c << " to t[" << "]" << std::endl;
            t.push_front(c);

        }

        t.reverse();
    }
    
    f.close();
    
}

//---------------------------------------------------------//

void Tilemap::setTileMap() {

    int i = 0;
    int j = 0;

    int i1;
    int i2;
    int i3;

    int count = 0;

    for(char ch : t) {

        if(ch != '|' && ch != '\n') {

            if(count == 0) {

                i1 = (int)ch -48;
                count++;

            }
            else if(count == 1) {

                i2 = i1 * 10;
                i2 += (int)ch -48;
                count++;

            } else {

                i3 = i2 * 10;
                i3 += (int)ch -48;
                std::cout << "Adding " << i3 << " to map[" << i << "][" << j << "]" << std::endl;
                map[i][j] = i3;
                count++;

            }
        } else if(ch == '|') {

            count = 0;
            i++;

        } else if (ch == '\n') {

            j++;
            i = 0;

        }
    }
}

//---------------------------------------------------------//

int** Tilemap::getMap(){

    return map;

}