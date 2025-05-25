#include "Tile.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Tile::Tile(LTexture* sprite, int index, float spriteSize, bool mv) {

    spriteSheet = sprite;

    posX = spriteSheet->getWidth();
    posY = spriteSheet->getHeight();

    moveable = mv;

    // tilesheet : x : 8 tiles; y: 18 tiles

    // index 0 -> x: 0, y: 0
    // index 1 -> x: tilesize *1, y: 0
    // index 8 -> x: 0, y: tilesize * 1
    // index 9 -> x: tilesize * 1, y: tilesize * 1

    int cols = 8;
    int rows = 18;

    int x = (index % cols) * spriteSize;
    int y = (index / rows) * spriteSize;

    sprite->setClip(x,y,spriteSize,spriteSize);
    sprite->setSize(spriteSize, spriteSize);

}

bool Tile::isMoveable() {

    return moveable;

}

void Tile::render(){

    spriteSheet->render();

}