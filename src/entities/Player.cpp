#include "Player.hpp"
#include "Entity.hpp"
#include <SDL3/SDL_camera.h>

void Player::move(int x, int y, int z) {

    Entity::move(x, y, z);
    
    Loader::getLoader()->getCamera()->x = static_cast<int>( getPosX() + getSprite()->getSpriteTex()->getWidth() / 2 - Loader::getLoader()->getScreenWidth() / 2 );
    Loader::getLoader()->getCamera()->y = static_cast<int>( getPosY() + getSprite()->getSpriteTex()->getHeight() / 2 - Loader::getLoader()->getScreenHeight() / 2 );

}