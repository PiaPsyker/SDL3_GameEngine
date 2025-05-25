#include "Player.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Player::Player(LTexture* spr, int x, int y, int sz) {

    sprite = spr;
    posX = x;
    posY = y;
    size = sz;

}

void Player::move(int x, int y) {

    posX += x * size;
    posY += y * size;

    sprite->setPosition(posX, posY);

}

