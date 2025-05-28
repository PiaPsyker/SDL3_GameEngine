#include "Player.hpp"
#include <iostream>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Player::Player(LTexture* spr, int x, int y, int sz, int z, SDL_FRect* cam) {

    sprite = spr;
    size = sz;
    z_index = z;
    mapX = x;
    mapY = y;
    posX = mapX * size;
    posY = mapY * size;
    camera = cam;


    sprite->setSize(size, size);

}

void Player::setMap(Map* m){

    map = m;

}

bool Player::checkCollision(int x, int y){

    if(!map->isMoveable(x, y, z_index)){

        return false;

    }

    return true;

}

void Player::move(int x, int y) {

    if(checkCollision(mapX + x, mapY + y) == true) {

        mapX += x;
        mapY += y;
        posX = mapX * size;
        posY = mapY * size;

        std::cout << "PX: " << mapX << " | PY: " << mapY << std::endl;

        sprite->setPosition(posX, posY);

    }
}

void Player::render() {

    sprite->render(camera);

}

LTexture* Player::getSprite() {

    return sprite;

}

int Player::getPosX() {

    return posX;

}

int Player::getPosY() {

    return posY;

}