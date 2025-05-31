#include "Tile.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Tile::Tile(LTexture* sprite, int index, float spriteSize, bool mv, int cols, SDL_FRect* cam) {

    spriteSheet = sprite;
    camera = cam;

    posX = 0;
    posY = 0;

    moveable = mv;

    this->spriteSize = spriteSize;

    if(index != -1) {
        tileX = (index % cols) * this->spriteSize;
        tileY = (index / cols) * this->spriteSize;
    }

    clip = new SDL_FRect{tileX,tileY,this->spriteSize,this->spriteSize};

}

//---------------------------------------------------------//

void Tile::init(int index, float spriteSize, bool mv, int cols) {

    moveable = mv;

    this->spriteSize = spriteSize;

    tileX = (index % cols) * this->spriteSize;
    tileY = (index / cols) * this->spriteSize;

}

//---------------------------------------------------------//

bool Tile::isMoveable() {

    return moveable;

}

//---------------------------------------------------------//

int Tile::getPosX() {

    return (int)posX;

}

//---------------------------------------------------------//

int Tile::getPosY() {

    return (int)posY;
    
}

//---------------------------------------------------------//

void Tile::render() {

    spriteSheet->setClip(tileX,tileY,spriteSize,spriteSize);
    spriteSheet->setSize(spriteSize, spriteSize);
    spriteSheet->setPosition(posX, posY);
    spriteSheet->render(camera);

}

//---------------------------------------------------------//

void Tile::setPosition(float x, float y) {

    posX = x;
    posY = y;
    
}