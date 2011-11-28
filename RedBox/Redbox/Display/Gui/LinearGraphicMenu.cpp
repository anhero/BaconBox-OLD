#include "LinearGraphicMenu.h"



using namespace RedBox;


LinearGraphicMenu::LinearGraphicMenu():layout(Horizontal), needPositionUpdate(false){}

LinearGraphicMenu::LinearGraphicMenu(Layout newLayout):layout(newLayout){}

 void LinearGraphicMenu::setLayout(Layout layout){
   
}

void LinearGraphicMenu::render(){
    if (needPositionUpdate) {
        needPositionUpdate = false;
        updateElementPosition();
    }
    Menu::render();
}

LinearGraphicMenu::Layout LinearGraphicMenu::getLayout(){
    return layout;
}

void LinearGraphicMenu::updateElementPosition(){
    std::list<MenuElement*>::iterator i = menuElements.begin();
    std::list<MenuElement*>::iterator previousElement = i;
    (*i)->setPosition(this->getPosition()+elementOffset + (*i)->getOffset());
    i++;
    
    for (; i != menuElements.end(); i++) {
        (*i)->setPosition((*previousElement)->getPosition()-(*previousElement)->getOffset() + (*i)->getOffset());
        
        if (layout==Horizontal) {
            (*i)->moveX((*previousElement)->getWidth() + elementSpacing);
        }
        else{
            (*i)->moveY((*previousElement)->getHeight() + elementSpacing);
        }
        previousElement = i;
    }
   
}

void LinearGraphicMenu::addElement(MenuElement* newElement){
    this->Menu::addElement(newElement);
    needPositionUpdate = true;
}


