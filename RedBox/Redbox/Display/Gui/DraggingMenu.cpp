#include "DraggingMenu.h"
#include <cmath>
using namespace RedBox;

DraggingMenu::DraggingMenu():IMenu(){
	
}
DraggingMenu::DraggingMenu(float width, float height, float spacing):IMenu(),internalMask(0){
	this->width = width;
	this->height = height;
	this->spacing = spacing;
	theTween = Tween<Vector2>(Vector2(0.0,0.0), Vector2(0.0,0.0), 1, Ease::OUT_CUBIC);
	theTween.start();
	
}
DraggingMenu::DraggingMenu(const DraggingMenu &src):IMenu::IMenu(src){
}
DraggingMenu::~DraggingMenu(){
}
void DraggingMenu::update(){
	IMenu::update();
	if (theTween.getValue() != Vector2(0.0,0.0)) {
		updateElementsPosition();
	}
}
void DraggingMenu::setCenterPosition(Vector2 vect){
	Vector2 oldPos = this->getPositionCenter();
	IMenu::setPosition(vect.getX()-getWidth()/2, vect.getY()-getHeight()/2);
	if(internalMask != NULL){
		internalMask->setPosition(vect-Vector2(width/2, height/2));
	}
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->move(vect-oldPos);
		i++;
	}
}
void DraggingMenu::setPosition(float x, float y){
	Vector2 oldPos = this->getPosition();
	Collidable::setPosition(x, y);
	if(internalMask != NULL){
		internalMask->setPosition(x, y);
	}
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->move(Vector2(x,y)-oldPos);
		i++;
	}
}
Vector2 DraggingMenu::getCenterPosition(){
	return this->getPosition() + Vector2(this->getWidth()/2, this->getHeight()/2);
}
void DraggingMenu::addElement(IMenuElement* newElement){
	IMenu::addElement(newElement);
	if(elements.size() == 1){
		newElement->setPosition(this->getCenterPosition() - 
										 Vector2(newElement->getWidth(),
												 newElement->getHeight())/2);
		std::cout << newElement->getPosition().getX() << ", " << newElement->getPosition().getY() <<std::endl;
	}else{
		Vector2 vect = Vector2(spacing,0.0);
		vect.rotate(this->getAngle());
		newElement->setPosition((*--(--elements.end()))->getPosition()+vect);
	}
}
void DraggingMenu::rotateFromPoint(float rotationAngle, const Vector2& rotationPoint){
	// Rotates the menu, its elements, and its mask if he have one.
	this->Collidable::rotateFromPoint(rotationAngle, rotationPoint);
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->rotateFromPoint(rotationAngle, rotationPoint);
		i++;
	}
	if (internalMask != NULL) {
		internalMask->rotateFromPoint(rotationAngle, rotationPoint);
	}
}
void DraggingMenu::scaleFromPoint(float xScaling, float yScaling,const Vector2 &fromPoint){
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->scaleFromPoint(xScaling, yScaling, fromPoint);
		i++;
	}
	Transformable::scaleFromPoint(xScaling, yScaling, fromPoint);
}
void DraggingMenu::setElementAngle(float newAngle){
	elementsAngle = newAngle;
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->setAngle(newAngle);
		i++;
	}
}
void DraggingMenu::setInternalMask(GraphicElement<Transformable>* mask, bool inverted){
	internalMask = mask;
	internalMask->setPosition(this->getCenterPosition()-Vector2(internalMask->getWidth()/2,+internalMask->getHeight()/2));
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->setMask(mask,inverted);
		i++;
	}
}
void DraggingMenu::setMask(Maskable* mask, bool inverted){
	
}
Maskable* DraggingMenu::getMask() const{
	return this->currentMask;
}
Maskable* DraggingMenu::getInternalMask(){
	return this->internalMask;
}
float DraggingMenu::getElementAngle(){
	return elementsAngle;
}
void DraggingMenu::mask(){
}
void DraggingMenu::unmask(){
}
void DraggingMenu::onHoldNMove(const Vector2 lastPtr, const Vector2 newPtr){
	// Finds the movement to be done.
	Vector2 left, right;
	Vector2 comparison = Vector2(1,0);
	comparison.rotate(this->getAngle());
	Vector2 final = Vector2(comparison.getX()*(newPtr-lastPtr).getX(),comparison.getY()*(newPtr-lastPtr).getY());
	// Verify the maximal values.
	left = this->getPositionCenter()-elements.front()->getPositionCenter();
	right = this->getPositionCenter()-elements.back()->getPositionCenter();
	right.rotate(-this->getAngle());
	left.rotate(-this->getAngle());
	if ((left.getX() > 0 || final.getX() < 0) && (right.getX() < 0 || final.getX() > 0)) {
		theTween.stop();
		theTween.setStartValue(final);
		theTween.start();
	}
}
void DraggingMenu::onRelease(Vector2 ptr){
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		if((*i)->getAxisAlignedBoundingBox().overlaps(ptr)){
			selectedElement = (*i);
		}
	}
}
void DraggingMenu::updateElementsVisibility(){
	// Calculates the visibility of each element.
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		if ((*i)->collide(this).first) {
			(*i)->setVisible(true);
		}else{
			(*i)->setVisible(false);
		}
	}
}
void DraggingMenu::updateElementsPosition(){
	std::cout << theTween.getValue() << std::endl;
	Vector2 left, right;
	left = this->getPositionCenter()-elements.front()->getPositionCenter();
	right = this->getPositionCenter()-elements.back()->getPositionCenter();
	right.rotate(-this->getAngle());
	left.rotate(-this->getAngle());
	if (!(left.getX() > 0 || theTween.getValue().getX() < 0) || !(right.getX() < 0 || theTween.getValue().getX() > 0)) {
		theTween.setStartValue(Vector2(0,0));
	}else{
		std::list<IMenuElement*>::iterator i = elements.begin();
		while (i != elements.end()) {
			(*i)->move(theTween.getValue());
			i++;
		}
	}
}
void DraggingMenu::scaleMaskToMenu(float x, float y){
	internalMask->setScaling((width*x/internalMask->getWidth()), (height*y/internalMask->getHeight()));
	internalMask->setPosition(this->getCenterPosition()-Vector2(internalMask->getWidth()/2,internalMask->getHeight()/2));
}