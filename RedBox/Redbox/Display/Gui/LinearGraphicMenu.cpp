#include "LinearGraphicMenu.h"
#include "Pointer.h"

using namespace RedBox;


LinearGraphicMenu::LinearGraphicMenu():layout(Horizontal){}

LinearGraphicMenu::LinearGraphicMenu(Layout newLayout):layout(newLayout){}

 void LinearGraphicMenu::setLayout(Layout layout){
   
}

void LinearGraphicMenu::update(){
    Pointer *ptr = Pointer::getDefault();
    
    // We make sure the pointer is initialized.
    if (ptr) {
        
    }
}


void LinearGraphicMenu::updateElementPosition(){
    std::list<MenuElement*>::iterator i = menuElements.begin();
    std::list<MenuElement*>::iterator previousElement = i;
    (*i)->setPosition(this->getPosition()+elementOffset + (*i)->getOffset());
    i++;
    
    for (; i != menuElements.end(); i++) {
        (*i)->setPosition((*previousElement)->getPosition() + (*i)->getOffset());
        
        if (layout==Horizontal) {
            (*i)->moveX((*previousElement)->getWidth() + elementSpacing);
        }
        else{
            (*i)->moveY((*previousElement)->getHeight() + elementSpacing);
        }
    }
   
}

void LinearGraphicMenu::addElement(MenuElement* newElement){
    this->Menu::addElement(newElement);
    updateElementPosition();

    for (std::list<MenuElement*>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
        
    }
}


