#include "Menu.h"

using namespace RedBox;

Menu::Menu():elementSpacing(0){}

Menu::Menu(float spacing):elementSpacing(spacing){}


void Menu::addElement(MenuElement* newElement){
    menuElements.push_back(newElement);
}

void Menu::removeElements(MenuElement* menuElement){
    menuElements.remove(menuElement);
}


void Menu::setSpacing(float spacing){
    elementSpacing = spacing;
}


float Menu::getSpacing(){
    return elementSpacing;
}

void Menu::render(){
    for (std::list<MenuElement*>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
        (*i)->render();
    }
}

void Menu::update(){
    for (std::list<MenuElement*>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
        (*i)->update();
    }
}


void Menu::move(float xDelta, float yDelta){
    this->Collidable::move(xDelta, yDelta);
    for (std::list<MenuElement*>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
        (*i)->move(xDelta,yDelta);
    }
}

float Menu::getWidth() const{
    std::list<MenuElement*>::const_iterator i = menuElements.begin();
    float temp = 0.0f;
    float min = (*i)->getXPosition();
    float max = (*i)->getXPosition()+ (*i)->getWidth();
    i++;
    for (; i != menuElements.end(); i++) {
        temp = (*i)->getXPosition()+ (*i)->getWidth();
        
        if (min > (*i)->getXPosition()) {
            min = (*i)->getXPosition();
        }
        
        if (max < temp) {
            max = temp;
        }
    }
    return max-min;
}

float Menu::getHeight() const{
    std::list<MenuElement*>::const_iterator i = menuElements.begin();
    float temp = 0.0f;
    float min = (*i)->getYPosition();
    float max = (*i)->getYPosition()+ (*i)->getHeight();
    i++;
    for (; i != menuElements.end(); i++) {
        temp = (*i)->getYPosition()+ (*i)->getHeight();
        
        if (min > (*i)->getYPosition()) {
            min = (*i)->getYPosition();
        }
        
        if (max < temp) {
            max = temp;
        }
    }
    return max-min;
}

Maskable * Menu::getMask() const{
    return renderMask;
}




void Menu::unmask(){
    for (std::list<MenuElement*>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
        (*i)->unmask();
    }
}

void Menu::mask(){
    for (std::list<MenuElement*>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
        (*i)->mask();
    }
}

void Menu::setMask(Maskable *newMask, bool inverted){
    renderMask = newMask;
    
    for (std::list<MenuElement*>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
        (*i)->setMask(newMask, inverted);
    }
}