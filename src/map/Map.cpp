#include "Map.hpp"
#include "Tilemap.hpp"
#include <cstddef>
#include <string>
#include <iostream>
#include <filesystem>
#include "../Loader.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Map::Map():
    layer_count(0)
{
    mapName = "";
}

Map::~Map() {

    for(Layer* lay : layers) {

        delete lay->tilemap;

    }

    layers.clear();

}

//---------------------------------------------------------//

void Map::addLayer(Tilemap* newLayer) {

    Layer* tempLayer = new Layer{layer_count,"test","test", newLayer};

    layers.push_front(tempLayer);
    
    layer_count++;

}

//---------------------------------------------------------//

bool Map::isMoveable(int x, int y, int z) {

    for(Layer* lay : layers) {

        if(lay->index == z) {
         
            return lay->tilemap->isMoveable(x, y);

        }
    }

    return true;

}

std::string Map::getTileInfo(int x, int y, int z_index) {

    for(Layer* lay : layers) {

        if(lay->index == z_index) {
         
            return lay->tilemap->getTileInfo(x, y);

        }
    }
    return "Not Found!";
}

//---------------------------------------------------------//

void Map::renderLayers() {

    for(Layer* lay : layers) {

        lay->tilemap->renderTileMap();
        
    }
}

//---------------------------------------------------------//

void Map::generateMap(int** index, int z, std::string tileName) {

    Layer* tempLayer = new Layer{z, tileName + ".png", "resources/tilesets/demo_tileset/" + tileName + ".txt", nullptr};

    Tilemap* tempTilemap = new Tilemap(Loader::getLoader()->getTexture(tileName + ".png"), 128, 128, 48, Loader::getLoader()->getCamera());

    tempTilemap->processTileSet("resources/tilesets/demo_tileset/" + tileName + ".txt");
    tempTilemap->setGeneratedTileMap(index);
    
    tempLayer->tilemap = tempTilemap;
    layers.push_back(tempLayer);

    layer_count = z+1;

}

//---------------------------------------------------------//

void Map::saveMap(std::string name) {

    mapName = name;
    if(mapName == "") {

        std::cout << "#########################" << std::endl;
        std::cout << "Enter Map Name to save: " << std::endl;
        std::cin >> mapName;
        std::cout << "#########################" << std::endl;

    }
    
    std::filesystem::create_directory("./build/maps/" + mapName);
    std::filesystem::create_directory("./build/maps/" + mapName + "/layers");

    std::fstream outputFile;
    outputFile.open("./build/maps/" + mapName + "/mapConfig.txt", std::ios::out);

    for(Layer* lay : layers) {

        std::cout << "Saving Map Layer " << lay->index << std::endl;

        outputFile << lay->index;
        outputFile << "|";
        outputFile << lay->tilemapName;
        outputFile << "|";
        outputFile << lay->tilemapConfig;
        outputFile << "\n";

        std::string path = "./build/maps/" + mapName + "/layers/layer" + std::to_string(lay->index) + ".bin";
        lay->tilemap->saveTileMap(path);

    }

    std::cout << "#########################" << std::endl;
    std::cout << "Saving complete!" << std::endl;
    std::cout << "#########################" << std::endl;

    outputFile.close();

}

//---------------------------------------------------------//

void Map::loadMap(std::string path) {

    for(Layer* lay : layers) {

        delete lay->tilemap;

    }

    layers.clear();

    std::cout << "#########################" << std::endl;
    std::cout << "Loading Map in: " << path << std::endl;

    std::fstream inputFile("./build/maps/" + path + "/mapConfig.txt");
    std::string delimitedString;
    

    if(!inputFile.is_open()) {

        SDL_Log("Error opening Tilemap Config file");

    } else {

        std::string s;
        
        std::cout << "#########################" << std::endl;
        
        while(getline(inputFile, s)){
            
            Layer* tempLayer = new Layer{-1, "nullptr", "nullptr"};
            std::stringstream fullLine(s);
            int i = 0;

            while(getline(fullLine,delimitedString, '|')){

                if(i == 0) {
                    tempLayer->index = std::stoi(delimitedString);
                    std::cout << "Set Index: " << std::stoi(delimitedString) << std::endl;
                } else if(i == 1) {
                    tempLayer->tilemapName = delimitedString;
                    std::cout << "Set TilemapName: " << delimitedString << std::endl;
                } else if(i == 2){
                    tempLayer->tilemapConfig = delimitedString;
                    std::cout << "Set TilemapConfig: " << delimitedString << std::endl;
                }

                i++;
                
            }
            
            layers.push_front(tempLayer);

        }
        
    }
    
    inputFile.close();

    layers.reverse();

    std::cout << "#########################" << std::endl;

    Tilemap* tempTilemap;
    
    for(Layer* lay : layers) {

        std::cout << "Processing Layer Index: " << lay->index << std::endl;

        tempTilemap = new Tilemap(Loader::getLoader()->getTexture(lay->tilemapName), 128, 128, 48, Loader::getLoader()->getCamera());

        tempTilemap->loadTileMap("./build/maps/" + path + "/layers" + "/layer" + std::to_string(lay->index) + ".bin");
        tempTilemap->processTileSet("./build/" + lay->tilemapConfig);

        tempTilemap->setTileMap();

        lay->tilemap = tempTilemap;
            
    }

    std::cout << "Proccessed " << layers.size() << " Layers" << std::endl;
    
    std::cout << "#########################" << std::endl;

    layer_count = layers.size();

}

//---------------------------------------------------------//