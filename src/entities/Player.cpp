#include "Player.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Player::Player(LTexture* spr, int x, int y, int sz, int z) {

    sprite = spr;
    size = sz;
    z_index = z;
    mapX = x;
    mapY = y;
    posX = mapX * size;
    posY = mapY * size;

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

    //if(checkCollision(mapX + x, mapY + y) == true) {

        mapX += x;
        mapY += y;
        posX = mapX * size;
        posY = mapY * size;

        sprite->setPosition(posX, posY);
        
    //}
}

void Player::render() {

    sprite->render();

}
