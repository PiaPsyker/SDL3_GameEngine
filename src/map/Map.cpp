#include "Map.hpp"
#include "Tilemap.hpp"
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

}

void Map::addLayer(Tilemap* layer) {

    layers[layer_count] = layer;
    layer_count++;

}

bool Map::isMoveable(int x, int y, int layer_id) {

    return layers[layer_id]->isMoveable(x, y);

}

void Map::renderLayers() {

    for(int i = 0; i < layer_count; i++) {

        layers[i]->renderTileMap();
        
    }
}

void Map::generateMap(int** index) {


    layers[0] = new Tilemap(Loader::getLoader()->getTexture("tileset.png"), 128, 128, 48, Loader::getLoader()->getCamera());
    layers[0]->processTileSet("resources/tileset.txt");
    layers[0]->setGeneratedTileMap(index);
    layer_count++;

}

void Map::saveMap() {

    for(int i = 0; i < layer_count; i++) {

        std::cout << "Saving Map Layer " << i << std::endl;
        std::string path = "build/testMap/layer" + std::to_string(i) + ".bin";
        layers[i]->saveTileMap(path);

    }
}

void Map::loadMap(std::string path) {

    int i = 0;

    std::cout << "Loading Map in: " << path << std::endl;

    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(path)) {
        
        layer_count = 1;
        
        if(dirEntry.path().extension() == ".bin") {
        
            std::cout << "Setting Tilemap: " << dirEntry.path().filename() << " in Index: " << i << std::endl;

            layers[i] = new Tilemap(Loader::getLoader()->getTexture("tileset.png"), 128, 128, 48, Loader::getLoader()->getCamera());
            layers[i]->loadTileMap(path + "/" + (std::string)dirEntry.path().filename());
            layers[i]->processTileSet("resources/tileset.txt");
            layers[i]->setTileMap();
            
            i++;
            layer_count++;
        
        }
    }
}