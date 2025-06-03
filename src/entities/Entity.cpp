#include "Entity.hpp"
#include "Sprite.hpp"
#include <SDL3/SDL_rect.h>

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Entity::Entity(std::string spriteName, int x, int y, int sz, int z, SDL_FRect* cam) {

    size = sz;
    z_index = z;
    mapX = x;
    mapY = y;
    posX = mapX * size;
    posY = mapY * size;
    camera = cam;

    sprite = new Sprite(spriteName, x, y, sz, cam);

}

//---------------------------------------------------------//

void Entity::setPosition(int x, int y, int z) {

    mapX += x;
    mapY += y;
    
    posX = mapX * size;
    posY = mapY * size;

    z_index = z;

    sprite->setPosition(posX, posY);

}

void Entity::setMap(Map* m){

    map = m;

}

bool Entity::checkCollision(int x, int y){

    if(!map->isMoveable(x, y, z_index)){

        return false;

    }

    return true;

}

void Entity::move(int x, int y, int z) {

    if(x > 0) {
        sprite->getSpriteTex()->setClip(size, size, size, size);
    }
    if(x < 0) {
        sprite->getSpriteTex()->setClip(size, 0.f, size, size);
    }
    if(y > 0) {
        sprite->getSpriteTex()->setClip(0.f, 0.f, size, size);
    }
    if(y < 0) {
        sprite->getSpriteTex()->setClip(0.f, size, size, size);
    }

    if(checkCollision(mapX + x, mapY + y) == true) {

        mapX += x;
        mapY += y;
        
        posX = mapX * size;
        posY = mapY * size;

        sprite->setPosition(posX, posY);

    }
}

void Entity::render() {

    sprite->getSpriteTex()->render(camera);

}

int Entity::getPosX() {

    return posX;

}

int Entity::getPosY() {

    return posY;

}

int Entity::getMapX() {

    return mapX;

}

int Entity::getMapY() {

    return mapY;

}

Sprite* Entity::getSprite() {

    return sprite;

}