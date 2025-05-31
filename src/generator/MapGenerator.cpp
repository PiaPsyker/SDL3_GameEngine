#include "MapGenerator.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

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

    std::remove("build/currentMap.bin");
    outputFile.open("build/currentMap.bin", std::ios::out);

    int i = 0;
    int j = 0;

    while(i != mapW && j != mapH) {
        
        std::string outputIndex;

        int index = abs((int)((noiseEngine->noise(i, j, 0.f)) * 100));
        
        indexMap[i][j] = index;

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
        if(i == mapW) {
        
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

void MapGenerator::regenerate(float fq, float amp) {

    if(noiseEngine != nullptr) {

        delete noiseEngine;

    }

    noiseEngine = new FractalNoise();

    noiseEngine->setBaseFrequency(fq);
    noiseEngine->setBaseAmplitude(amp);
    noiseEngine->setOctaves(1);

    std::remove("build/currentMap.bin");
    outputFile.open("build/currentMap.bin", std::ios::out);

    int i = 0;
    int j = 0;

    while(i != mapW && j != mapH) {
        
        std::string outputIndex;

        int index = abs((int)((noiseEngine->noise(i, j, 0.f)) * 100));
        
        indexMap[i][j] = index;

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
        if(i == mapW) {
        
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

void MapGenerator::generateMap() {

    if(currentMap != nullptr) {

        currentMap->~Map();
        delete currentMap;

    }

    currentMap = new Map();

    currentMap->generateMap(indexMap, 0);

    int** tempIndex1 = indexMap;

    regenerate(0.1f, 0.1f);
    int** tempIndex2 = indexMap;

    int** tempIndex3 = indexMap;

    for(int x = 0; x < mapW; x++) {

        for(int y = 0; y < mapH; y++) {

            tempIndex3[x][y] = tempIndex1[x][y] + tempIndex2[x][y];
            //tempIndex3[x][y] -= 1;

        }

    }

    currentMap->generateMap(tempIndex3, 1);
}

//---------------------------------------------------------//

Map* MapGenerator::getMap() {

    return currentMap;

}