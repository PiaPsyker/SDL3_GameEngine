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

    int x = (index % 8) * spriteSize;
    int y = (index / 8) * spriteSize;

    spriteSheet->setClip(x,y,spriteSize,spriteSize);
    spriteSheet->setSize(spriteSize, spriteSize);

}

//---------------------------------------------------------//

bool Tile::isMoveable() {

    return moveable;

}

//---------------------------------------------------------//

void Tile::render() {

    spriteSheet->render();

}

void Tile::setPosition(float x, float y) {

    spriteSheet->setPosition(x, y);

}