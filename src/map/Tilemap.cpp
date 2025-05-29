#include "Tilemap.hpp"
#include "LTexture.hpp"
#include "Tile.hpp"
#include <SDL3/SDL_rect.h>
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

    arr = new config[tilemapWidth * tilemapHeight];

    configMap = new std::string[tilemapWidth * tilemapHeight];

    map = new int*[tilemapWidth];
    tileArray = new Tile**[tilemapWidth];

    for (int i = 0; i < tilemapWidth; i++) {
        
        map[i] = new int[tilemapHeight];
        tileArray[i] = new Tile*[tilemapHeight];

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

            std::stringstream ss(s);
            std::string t;
            char del = '|';

            int i = 0;

            while(getline(ss,t,del)){

                std::stringstream temp;
                int index;

                if(i == 0) {

                    temp << t;
                    temp >> index;
                    arr[count].index = index;
                    index = -1;

                } else if(i == 1) {

                    arr[count].name = t;

                } else if(i == 2) {

                    temp << t;
                    temp >> index;
                    arr[count].moveable = (bool)index;
                    index = -1;

                } else if(i == 3) {

                    temp << t;
                    temp >> index;
                    arr[count].interaction = (bool)index;
                    index = -1;

                }

                i++;

            }
            //configMap[count] = s;
            count++;

        }

        std::cout << "Build configMap from " << cpath << " with following data:" << std::endl;
        
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
                map[i][j] = i3;

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

    // Somehow this doesnt work, when just calling the renderer on the filled array it only shows green tiles..
    for(int x = 0; x < tilemapWidth; x++){

        for(int y = 0; y < tilemapHeight; y++) {

            tileArray[x][y] = new Tile(tilemapTex, -1, 48.f, true, 6, camera);
            //tileArray[x][y]->setPosition(x * 48, y * 48);
            //tileArray[x][y]->init(map[x][y], tileSize, arr[map[x][y]].moveable, 6);
        }
    }

}

//---------------------------------------------------------//

void Tilemap::renderTileMap() {

    for(int i = 0; i < tilemapWidth; i++){

        for(int j = 0; j < tilemapHeight; j++) {

            // Cant set the tiles everytime we render cause that causes memory nom nom....
            //tileArray[i][j] = new Tile(tilemapTex, map[i][j], tileSize, arr[map[i][j]].moveable, 6, camera);
            tileArray[i][j]->init(map[i][j], tileSize, arr[map[i][j]].moveable, 6);
            tileArray[i][j]->setPosition(i * 48, j * 48);
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

    return map;

}

//---------------------------------------------------------//