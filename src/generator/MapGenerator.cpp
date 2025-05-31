#include "MapGenerator.hpp"
#include <iostream>
#include <string>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

MapGenerator::MapGenerator(int width, int height) {


    indexMap = new int*[width];

    for(int i = 0; i < width; i++) {

        indexMap[i] = new int[height];

    }

    noiseEngine = new FractalNoise();

    noiseEngine->setBaseFrequency(.02f);
    noiseEngine->setBaseAmplitude(.2f);
    noiseEngine->setOctaves(1);

    std::remove("build/currentMap.bin");
    outputFile.open("build/currentMap.bin", std::ios::out);

    int i = 0;
    int j = 0;

    while(i != width && j != height) {
        
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
        if(i == width) {
            outputFile << "\n";
            j++;
            i = 0;
        } else {
            outputFile << "|";
        }
    }
    outputFile.close();
}

void MapGenerator::generateMap() {

    currentMap = new Map();
    currentMap->generateMap(indexMap);

}

Map* MapGenerator::getMap() {

    return currentMap;

}