#include "Tile.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Tile::Tile(LTexture* sprite, int index, float spriteSize, bool mv) {

    spriteSheet = sprite;

    posX = spriteSheet->getWidth();
    posY = spriteSheet->getHeight();

    moveable = mv;

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