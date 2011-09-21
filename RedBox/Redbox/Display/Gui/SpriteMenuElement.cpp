#include "SpriteMenuElement.h"
using namespace RedBox;

SpriteMenuElement::SpriteMenuElement(std::string imageKey):IMenuElement(imageKey){
	image = new Sprite(imageKey);
}

SpriteMenuElement::SpriteMenuElement(const SpriteMenuElement &src):IMenuElement(src.key){
	image = new Sprite(src.key);
}
SpriteMenuElement* SpriteMenuElement::clone() const{
	return new SpriteMenuElement (*this);
}
SpriteMenuElement::~SpriteMenuElement(){
	delete image;
}
void SpriteMenuElement::update(){
	image->update();
}
void SpriteMenuElement::render(){
	if (isVisible()){
		image->render();
	}
}
float SpriteMenuElement::getWidth() const{
	return image->getWidth();
}
float SpriteMenuElement::getHeight() const{
	return image->getHeight();
}
void SpriteMenuElement::setPosition(float x, float y){
	GraphicBody::setPosition(x, y);
	image->setPosition(x,y);
}
void SpriteMenuElement::rotateFromPoint(float rotationAngle, const Vector2& vect){
	GraphicBody::rotateFromPoint(rotationAngle, vect);
	image->rotateFromPoint(rotationAngle, vect);
}
void SpriteMenuElement::setMask(GraphicBody* mask, bool inversed){
	currentMask = mask;
	image->setMask(currentMask,inversed);
}

GraphicBody* SpriteMenuElement::getMask(){
	return this->currentMask;
}
void SpriteMenuElement::mask(){
	image->mask();
}
void SpriteMenuElement::unmask(){
	image->unmask();
}