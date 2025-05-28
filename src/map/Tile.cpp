#include "Tile.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Tile::Tile(LTexture* sprite, int index, float spriteSize, bool mv, int cols, SDL_FRect* cam) {

    spriteSheet = sprite;
    camera = cam;

    posX = spriteSheet->getWidth();
    posY = spriteSheet->getHeight();

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

void Tile::render() {

    spriteSheet->render(camera);

}

void Tile::setPosition(float x, float y) {

    spriteSheet->setPosition(x, y);

}