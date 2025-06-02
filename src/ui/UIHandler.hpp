//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef UIHANDLER_H
#define UIHANDLER_H

#include "UIElement.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <list>
#include "UIElement.hpp"

struct ElementInfo {

    std::string name;
    UIElement* element;

};

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class UIHandler {

    public:
        
        UIHandler();
        ~UIHandler();

        void newElement(std::string name, std::string fontName, std::string* text, int x, int y);
        void addElement(std::string name, UIElement* el);

        void setElementText(std::string name, std::string* text);
        void setElementColor(std::string name, SDL_Color color);
        void setElementPosition(std::string name, int x, int y);

        void render();

    private:

        std::list<ElementInfo*> elements;

};

#endif