#include "Map.hpp"
#include "Tilemap.hpp"
#include <cstdlib>
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

Map::~Map() {

    for(int i = 0; i < layer_count; i++) {

        delete layers[i];
    
    }
}

//---------------------------------------------------------//

void Map::addLayer(Tilemap* layer) {

    layers[layer_count] = layer;
    layer_count++;

}

//---------------------------------------------------------//

bool Map::isMoveable(int x, int y, int layer_id) {

    return layers[layer_id]->isMoveable(x, y);

}

//---------------------------------------------------------//

void Map::renderLayers() {

    for(int i = 0; i < layer_count; i++) {

        layers[i]->renderTileMap();
        
    }
}

//---------------------------------------------------------//

void Map::generateMap(int** index, int z) {

    // if(z == 0) {

    layers[z] = new Tilemap(Loader::getLoader()->getTexture("tileset.png"), 128, 128, 48, Loader::getLoader()->getCamera());
    layers[z]->processTileSet("resources/tilesets/demo_tileset/tileset.txt");
    
    // } else {
    //     layers[z] = new Tilemap(Loader::getLoader()->getTexture("tileset_overlay.png"), 128, 128, 48, Loader::getLoader()->getCamera());
    //     layers[z]->processTileSet("resources/tilesets/demo_tileset/tileset_overlay.txt");
    // }
    
    layers[z]->setGeneratedTileMap(index);
    layer_count = z+1;

}

//---------------------------------------------------------//

void Map::saveMap() {

    for(int i = 0; i < layer_count; i++) {

        std::cout << "Saving Map Layer " << i << std::endl;
        std::string path = "./build/testMap/layer" + std::to_string(i) + ".bin";
        layers[i]->saveTileMap(path);

    }
}

//---------------------------------------------------------//

void Map::loadMap(std::string path) {

    int i = 0;

    std::cout << "Loading Map in: " << path << std::endl;

    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(path)) {
        
        layer_count = 2;
        
        if(dirEntry.path().extension() == ".bin") {

            //if(i == 0) {
                layers[i] = new Tilemap(Loader::getLoader()->getTexture("tileset.png"), 128, 128, 48, Loader::getLoader()->getCamera());
                layers[i]->loadTileMap(path + "/" + (std::string)dirEntry.path().filename());
                layers[i]->processTileSet("resources/tilesets/demo_tileset/tileset.txt");
            //}else {
            //    layers[i] = new Tilemap(Loader::getLoader()->getTexture("tileset_overlay.png"), 128, 128, 48, Loader::getLoader()->getCamera());
            //    layers[i]->loadTileMap(path + "/" + (std::string)dirEntry.path().filename());
            //    layers[i]->processTileSet("resources/tilesets/demo_tileset/tileset_overlay.txt");
            //}
            
            layers[i]->setTileMap();

            i++;
        }
    }
    layer_count = i;
}

//---------------------------------------------------------//