#include "UIElement.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

UIElement::UIElement(TTF_Font* newFont, std::string* text, int x, int y) {

    std::cout << "Creating new Element" << std::endl;

    texture = new LTexture(Loader::getLoader()->getRenderer());
    textColor = { 0xFF, 0xFF, 0xFF, 0xFF };

    std::cout << "Got Renderer from Loader" << std::endl;

    font = newFont;

    //std::cout << "Got Font " << fontName <<  " from Loader" << std::endl;

    uiText = text;
    posX = x;
    posY = y;

    std::cout << "Set Text:" << uiText << std::endl;
    std::cout << "Set PosX:" << posX << std::endl;
    std::cout << "Set PosY:" << posY << std::endl;

    texture->loadFromText(font, uiText->c_str(), textColor);

    texture->setPosition(posX, posY);
    
    std::cout << "Set Texture | Done" << std::endl;

}

UIElement::~UIElement() {

    texture->~LTexture();

}

void UIElement::setText(std::string* text) {

    uiText = text;
    texture->loadFromText(font, uiText->c_str(), textColor);

}

void UIElement::setColor(SDL_Color col) {

    textColor = col;
    texture->loadFromText(font, uiText->c_str(), textColor);

}

void UIElement::setPosition(int x, int y) {

    posX = x;
    posY = y;
    texture->setPosition(posX, posY);

}

void UIElement::render() {

    texture->render();

}