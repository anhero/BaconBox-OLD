#include "MenuElement.h"

using namespace RedBox;

MenuElement::MenuElement(const std::string & key):elementKey(key){}

const std::string & MenuElement::getKey(){
    return elementKey;
}

void MenuElement::setOffset(Vector2 offset){
    this->offset = offset;
}

const Vector2 & MenuElement::getOffset(){
    return offset;
}