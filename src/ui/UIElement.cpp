#include "UIElement.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

UIElement::UIElement(std::string fontName, std::string* text, int x, int y) {

    texture = new LTexture(Loader::getLoader()->getRenderer());
    textColor = { 0xFF, 0xFF, 0xFF, 0xFF };

    font = Loader::getLoader()->getFont(fontName);

    uiText = text;
    posX = x;
    posY = y;

    texture->loadFromText(font, uiText->c_str(), textColor);
    texture->setPosition(posX, posY);

}

UIElement::~UIElement() {

    texture->~LTexture();

}

void UIElement::setText(std::string* text) {

    uiText = text;
    texture->loadFromText(font, uiText->c_str(), textColor);

}

void UIElement::render() {

    texture->render();

}