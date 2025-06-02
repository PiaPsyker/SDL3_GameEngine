#include "UIHandler.hpp"
#include "UIElement.hpp"
#include "../Loader.hpp"

//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

UIHandler::UIHandler() {



}

UIHandler::~UIHandler() {

    for(ElementInfo* e : elements) {

        delete e->element;

    }

    elements.clear();

}

void UIHandler::newElement(std::string name, std::string fontName, std::string* text, int x, int y) {

    UIElement* tempUIElement = new UIElement(Loader::getLoader()->getFont(fontName), text, x, y);

    ElementInfo* tempElement = new ElementInfo{name, tempUIElement};

    elements.push_front(tempElement);

}

void UIHandler::addElement(std::string name, UIElement* el) {

    ElementInfo* tempElement = new ElementInfo{name, el};
    elements.push_front(tempElement);

}

void UIHandler::setElementText(std::string name, std::string* text) {

    for(ElementInfo* e : elements) {

        if(e->name == name) {

            e->element->setText(text);

        }
    }
}

void UIHandler::setElementColor(std::string name, SDL_Color color) {

    for(ElementInfo* e : elements) {

        if(e->name == name) {

            e->element->setColor(color);

        }
    }
}

void UIHandler::setElementPosition(std::string name, int x, int y) {

    for(ElementInfo* e : elements) {

        if(e->name == name) {

            e->element->setPosition(x, y);

        }
    }
}

void UIHandler::render() {

    for(ElementInfo* e : elements) {

        e->element->render();

    }
}