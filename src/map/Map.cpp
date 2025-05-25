#include "Map.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Map::Map() {

}

void Map::addLayer(Layer* layer) {

    layers.push_front(layer);

}

void Map::renderLayers() {

    for(Layer* layer : layers) {

        layer->loadTileMap();

    }

}