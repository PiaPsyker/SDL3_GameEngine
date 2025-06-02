#include "Entity.hpp"

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

    sprite = Loader::getLoader()->getTexture(spriteName);

    sprite->setSize(size, size);
    sprite->setPosition(posX, posY);
    sprite->setClip(0.f, 0.f, size, size);

}

//---------------------------------------------------------//

void Entity::setPosition(int x, int y, int z) {

    mapX += x;
    mapY += y;
    
    posX = mapX * size;
    posY = mapY * size;

    z_index = z;

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

    if(checkCollision(mapX + x, mapY + y) == true) {

        mapX += x;
        mapY += y;
        
        posX = mapX * size;
        posY = mapY * size;

        sprite->setPosition(posX, posY);

    }
}

void Entity::render() {

    sprite->render(camera);

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