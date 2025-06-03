//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>

#include "Moveable.hpp"

#include "Sprite.hpp"
#include "../map/Map.hpp"
#include "../Loader.hpp"

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Entity : public Moveable{

    public:

        Entity(std::string spriteName, int x, int y, int sz, int z, SDL_FRect* cam);

        void move(int x, int y, int z) override;
        void setPosition(int x, int y, int z) override;
        
        void interact(int x, int y, int z);

        void setMap(Map* m);
        
        bool checkCollision(int x, int y);
        
        void render();

        int getPosX();
        int getPosY();

        int getMapX();
        int getMapY();

        Sprite* getSprite();

    private:

        Sprite* sprite;
        SDL_FRect* camera;
        
        Map* map;

        int size;
        int z_index;
        int posX,posY;
        int mapX, mapY;

};

#endif