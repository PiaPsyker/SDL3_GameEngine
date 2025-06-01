#include "MapGenerator.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <filesystem>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

MapGenerator::MapGenerator(int width, int height):

    currentMap{nullptr}

{

    mapW = width;
    mapH = height;

    indexMap = new int*[mapW];

    for(int i = 0; i < mapW; i++) {

        indexMap[i] = new int[mapH];

    }

    noiseEngine = new FractalNoise();

    noiseEngine->setBaseFrequency(.02f);
    noiseEngine->setBaseAmplitude(.2f);
    noiseEngine->setOctaves(1);

    int i = 0;
    int j = 0;

    while(i != mapW && j != mapH) {

        int index = abs((int)((noiseEngine->noise(i, j, 0.f)) * 100));
        
        indexMap[i][j] = index;

        i++;

        if(i == mapW) {
        
            j++;
            i = 0;
        
        } 
    }

}

MapGenerator::~MapGenerator() {

    delete currentMap;
    delete noiseEngine;

    for(int i = 0; i < mapW; i++) {

        free(indexMap[i]);

    }

    free(indexMap);

}

//---------------------------------------------------------//

void MapGenerator::regenerate(float fq, float amp) {

    if(noiseEngine != nullptr) {

        delete noiseEngine;

    }

    noiseEngine = new FractalNoise();

    noiseEngine->setBaseFrequency(fq);
    noiseEngine->setBaseAmplitude(amp);
    noiseEngine->setOctaves(1);

    int i = 0;
    int j = 0;

    while(i != mapW && j != mapH) {

        int index = abs((int)((noiseEngine->noise(i, j, 0.f)) * 100));
        
        indexMap[i][j] = index;
        i++;

        if(i == mapW) {
        
            j++;
            i = 0;
        
        }
    }
}

//---------------------------------------------------------//

void MapGenerator::generateMap() {

    std::filesystem::remove_all("./build/maps/tempMap");

    std::cout << "Regenerating Map..." << std::endl;
    std::cout << "#########################" << std::endl;

    if(currentMap != nullptr) {

        delete currentMap;

    }

    currentMap = new Map();

    currentMap->generateMap(indexMap, 0, "tileset");

    int** tempIndex1 = indexMap;

    regenerate(0.1f, 0.1f);
    int** tempIndex2 = indexMap;

    int** tempIndex3 = indexMap;

    for(int x = 0; x < mapW; x++) {

        for(int y = 0; y < mapH; y++) {

            tempIndex3[x][y] = tempIndex1[x][y] + tempIndex2[x][y];

        }
    }

    currentMap->generateMap(tempIndex3, 1, "tileset");

    regenerate(0.025f, 0.05f);
    currentMap->generateMap(indexMap, 2, "tileset_overlay");
    currentMap->saveMap("tempMap");

    std::cout << "Finished generating Map..." << std::endl;
    std::cout << "#########################" << std::endl;

}

//---------------------------------------------------------//

Map* MapGenerator::getMap() {

    return currentMap;

}