#include "Player.hpp"
#include <iostream>
#include "../Loader.hpp"
//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Player::Player(std::string spriteName, int x, int y, int sz, int z, SDL_FRect* cam) {

    size = sz;
    z_index = z;
    mapX = x;
    mapY = y;
    posX = mapX * size;
    posY = mapY * size;
    camera = cam;


    sprite = Loader::getLoader()->getTexture(spriteName);


    sprite->setSize(size, size);
    sprite->setPosition(posX, posY);

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

        if(x > 0) {
            sprite->setClip(size, size, size, size);
        }
        if(x < 0) {
            sprite->setClip(size, 0.f, size, size);
        }
        if(y > 0) {
            sprite->setClip(0.f, 0.f, size, size);
        }
        if(y < 0) {
            sprite->setClip(0.f, size, size, size);
        }

        mapX += x;
        mapY += y;
        
        posX = mapX * size;
        posY = mapY * size;

        sprite->setPosition(posX, posY);
        std::cout << "PX: " << mapX << " | PY: " << mapY << std::endl;

        camera->x = static_cast<int>( posX + sprite->getWidth() / 2 - Loader::getLoader()->getScreenWidth() / 2 );
        camera->y = static_cast<int>( posY + sprite->getHeight() / 2 - Loader::getLoader()->getScreenHeight() / 2 );


    //}
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

int Player::getMapX() {

    return mapX;

}

int Player::getMapY() {

    return mapY;

}