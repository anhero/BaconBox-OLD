#include "GraphicMenuElement.h"
using namespace RedBox;

GraphicMenuElement::GraphicMenuElement(const std::string & textureKey): 
    MenuElement(textureKey){
        graphicElement = new GraphicElement<Transformable>(textureKey);
    }

GraphicMenuElement::GraphicMenuElement(const std::string & textureKey, const std::string & menuElementKey):
MenuElement(menuElementKey){
    graphicElement = new GraphicElement<Transformable>(textureKey);
}


GraphicMenuElement::~GraphicMenuElement(){
    delete graphicElement;
}

void GraphicMenuElement::render(){
    graphicElement->render();
}

void GraphicMenuElement::update(){
    graphicElement->update();
}

void GraphicMenuElement::mask(){
    graphicElement->mask();
}

void GraphicMenuElement::unmask(){
    graphicElement->unmask();
}


Maskable * GraphicMenuElement::getMask() const {
    return graphicElement->getMask();
}

void GraphicMenuElement::setMask(Maskable *newMask, bool inverted){
    graphicElement->setMask(newMask, inverted);
}

float GraphicMenuElement::getWidth() const{
    return graphicElement->getWidth();
}

float GraphicMenuElement::getHeight() const{
    return graphicElement->getHeight();
}

void GraphicMenuElement::move(float xDelta, float yDelta){
    graphicElement->move(xDelta, yDelta);
}