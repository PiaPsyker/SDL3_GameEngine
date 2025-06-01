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
    mapName = "";
}

Map::~Map() {

    for(Layer* lay : layers) {

        delete lay->tilemap;

    }
}

//---------------------------------------------------------//

void Map::addLayer(Tilemap* newLayer) {

    Layer* tempLayer = new Layer{layer_count,"test","test", newLayer};

    layers.push_front(tempLayer);

    //layers[layer_count] = layer;
    
    layer_count++;

}

//---------------------------------------------------------//

bool Map::isMoveable(int x, int y, int z) {

    for(Layer* lay : layers) {

        if(lay->index == z) {
         
            std::cout << "Found Layer: " << lay->index << std::endl;
            std:: cout << "Is moveable: " << lay->tilemap->isMoveable(x, y) << std::endl;
            return lay->tilemap->isMoveable(x, y);

        }
    }

    return true;

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
    std::cout << tileName + ".png" << std::endl;

    Tilemap* tempTilemap = new Tilemap(Loader::getLoader()->getTexture(tileName + ".png"), 128, 128, 48, Loader::getLoader()->getCamera());

    std::cout << "resources/tilesets/demo_tileset/" + tileName + ".txt" << std::endl;
    tempTilemap->processTileSet("resources/tilesets/demo_tileset/" + tileName + ".txt");
    tempTilemap->setGeneratedTileMap(index);
    
    tempLayer->tilemap = tempTilemap;
    layers.push_back(tempLayer);

    layer_count = z+1;

    // if(z == 0 or z == 1) {
    // 
    //     layers[z] = new Tilemap(Loader::getLoader()->getTexture("tileset.png"), 128, 128, 48, Loader::getLoader()->getCamera());
    //     layers[z]->processTileSet("resources/tilesets/demo_tileset/tileset.txt");
    // 
    // } else {
    //      layers[z] = new Tilemap(Loader::getLoader()->getTexture("tileset_overlay.png"), 128, 128, 48, Loader::getLoader()->getCamera());
    //      layers[z]->processTileSet("resources/tilesets/demo_tileset/tileset_overlay.txt");
    // }
    // 
    // layers[z]->setGeneratedTileMap(index);
    // layer_count = z+1;

}

//---------------------------------------------------------//

void Map::saveMap() {

    if(mapName == "") {
        std::cout << "Enter Map Name to save: " << std::endl;
        std::cin >> mapName;
    }
    
    std::filesystem::create_directory("./build/maps/" + mapName);

    for(Layer* lay : layers) {
        std::cout << "Saving Map Layer " << lay->index << std::endl;
        std::string path = "./build/maps/" + mapName + "/layer" + std::to_string(lay->index) + ".bin";
        lay->tilemap->saveTileMap(path);
    }

    // for(int i = 0; i < layer_count; i++) {
    // 
    //     std::cout << "Saving Map Layer " << i << std::endl;
    //     std::string path = "./build/maps/" + mapName + "/layer" + std::to_string(i) + ".bin";
    //     layers[i]->saveTileMap(path);
    // 
    // }
}

//---------------------------------------------------------//

void Map::loadMap(std::string path) {

    // int i = 0;
// 
    // std::cout << "Loading Map in: " << path << std::endl;
// 
    // for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(path)) {
    //     
    //     layer_count = 2;
    //     
    //     if(dirEntry.path().extension() == ".bin") {
// 
    //         if(i == 0 or i == 1) {
    //             layers[i] = new Tilemap(Loader::getLoader()->getTexture("tileset.png"), 128, 128, 48, Loader::getLoader()->getCamera());
    //             layers[i]->loadTileMap(path + "/" + (std::string)dirEntry.path().filename());
    //             layers[i]->processTileSet("resources/tilesets/demo_tileset/tileset.txt");
    //         }else {
    //             layers[i] = new Tilemap(Loader::getLoader()->getTexture("tileset_overlay.png"), 128, 128, 48, Loader::getLoader()->getCamera());
    //             layers[i]->loadTileMap(path + "/" + (std::string)dirEntry.path().filename());
    //             layers[i]->processTileSet("resources/tilesets/demo_tileset/tileset_overlay.txt");
    //         }
    //         
    //         layers[i]->setTileMap();
// 
    //         i++;
    //     }
    // }
    // layer_count = i;
}

//---------------------------------------------------------//