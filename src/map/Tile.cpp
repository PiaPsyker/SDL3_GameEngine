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

    int x;
    int y;

    if(index != -1) {
        x = (index % cols) * spriteSize;
        y = (index / cols) * spriteSize;
    }
    

    if(spriteSheet!=nullptr) {
        spriteSheet->setClip(x,y,spriteSize,spriteSize);
        spriteSheet->setSize(spriteSize, spriteSize);
    }
    

}

void Tile::init(int index, float spriteSize, bool mv, int cols) {

    moveable = mv;

    int x = (index % cols) * spriteSize;
    int y = (index / cols) * spriteSize;

    spriteSheet->setClip(x,y,spriteSize,spriteSize);
    spriteSheet->setSize(spriteSize, spriteSize);

}

//---------------------------------------------------------//

bool Tile::isMoveable() {

    return moveable;

}

//---------------------------------------------------------//

int Tile::getPosX() {

    return (int)posX;

}

int Tile::getPosY() {

    return (int)posY;
    
}

void Tile::render() {

    spriteSheet->render(camera);

}

void Tile::setPosition(float x, float y) {

    posX = x;
    posY = y;
    spriteSheet->setPosition(posX, posY);

}