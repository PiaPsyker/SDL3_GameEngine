#include "Tile.hpp"
#include "LTexture.hpp"


//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Tile::Tile(LTexture* sprite, int index) {
    spriteSheet = sprite;
    posX = spriteSheet->getWidth();
    posY = spriteSheet->getHeight();
}

bool Tile::isMoveable() {

    return moveable;

}

