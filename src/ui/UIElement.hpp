//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <list>
#include "../Loader.hpp"


//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class UIElement {

    public:

        UIElement(std::string fontName, std::string* text, int x, int y);
        ~UIElement();

        void setText(std::string* text);

        void render();

    private:

        int posX;
        int posY;

        TTF_Font* font;
        std::string* uiText;
        LTexture* texture;
        SDL_Color textColor;

};

#endif