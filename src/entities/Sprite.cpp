#include "Sprite.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Sprite::Sprite(std::string spriteName, int x, int y, int sz, SDL_FRect* cam, LTexture* tex) {

    size = sz;
    mapX = x;
    mapY = y;
    posX = mapX * size;
    posY = mapY * size;
    camera = cam;

    if(tex != nullptr) {
        spriteTex = tex;
    } else {
        LTexture* tempTex = new LTexture(Loader::getLoader()->getRenderer());
        tempTex->loadFromFile("resources/sprites/" + spriteName);
        spriteTex = tempTex;
    }

    spriteTex->setSize(size, size);
    spriteTex->setPosition(posX, posY);
    spriteTex->setClip(0.f, 0.f, size, size);

}

void Sprite::setPosition(int x, int y) {

    spriteTex->setPosition(x, y);

}

LTexture* Sprite::getSpriteTex() {

    return spriteTex;

}