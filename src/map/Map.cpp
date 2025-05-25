#include "Map.hpp"
#include <iostream>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Map::Map():
    layer_count(0)
{

}

void Map::addLayer(Layer* layer) {

    layers[layer_count] = layer;
    layer_count++;

}

bool Map::isMoveable(int x, int y, int layer_id) {

    return layers[layer_id]->isMoveable(x, y);

}

void Map::renderLayers() {

    for(int i = 0; i < layer_count; i++) {
        layers[i]->loadTileMap();
    }
}