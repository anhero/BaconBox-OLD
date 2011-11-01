#include "SpriteMenuElement.h"
using namespace RedBox;

SpriteMenuElement::SpriteMenuElement(const std::string& imageKey):IMenuElement(imageKey){
	image = new Sprite(imageKey);
}
SpriteMenuElement::SpriteMenuElement(const std::string& imageKey,const std::string& idKey):IMenuElement(idKey){
	image = new Sprite(imageKey);
}
SpriteMenuElement::SpriteMenuElement(const SpriteMenuElement &src):IMenuElement(src.key){
	image = new Sprite(src.key);
}
IMenuElement* SpriteMenuElement::clone() const{
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
void SpriteMenuElement::move(float xDelta, float yDelta){
	Collidable::move(xDelta, yDelta);
	image->move(xDelta, yDelta);
}
void SpriteMenuElement::rotateFromPoint(float rotationAngle, const Vector2& vect){
	Collidable::rotateFromPoint(rotationAngle, vect);
	image->rotateFromPoint(rotationAngle, vect);
}
void SpriteMenuElement::setMask(Maskable* mask, bool inversed){
	currentMask = mask;
	image->setMask(currentMask,inversed);
}

Maskable* SpriteMenuElement::getMask(){
	return this->currentMask;
}
void SpriteMenuElement::mask(){
	image->mask();
}
void SpriteMenuElement::unmask(){
	image->unmask();
}