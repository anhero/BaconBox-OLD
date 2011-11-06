#include "DraggingMenu.h"
#include <cmath>
using namespace RedBox;

DraggingMenu::DraggingMenu():IMenu(){
	
}
DraggingMenu::DraggingMenu(float width, float height, float spacing):IMenu(),cursor(0),elementsAngle(0),isHolded(false),internalMask(0) {
	this->width = width;
	this->height = height;
	this->spacing = spacing;
}
DraggingMenu::DraggingMenu(const DraggingMenu &src):IMenu::IMenu(src){
}
DraggingMenu::~DraggingMenu(){
}
void DraggingMenu::update(){
	IMenu::update();
	updateCursor();
	if (!isHolded) {
		updateElementsPosition();
	}
	updateVisibility();
}
void DraggingMenu::render(){
	IMenu::render();
	if (cursor != NULL){
		cursor->render();
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
	if (cursor != NULL){
		cursor->move(vect-oldPos);
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
	if (cursor != NULL){
		cursor->move(Vector2(x,y)-oldPos);
	}
}
Vector2 DraggingMenu::getCenterPosition(){
	return this->getPosition() + Vector2(this->getWidth()/2, this->getHeight()/2);
}
void DraggingMenu::addElement(IMenuElement* newElement){
	IMenu::addElement(newElement);
	if(elements.size() == 1){
		newElement->setScaling(this->getScaling());
		newElement->setAngle(this->getElementAngle());
		newElement->setPosition(this->getPosition());
		newElement->setDrag(Vector2(750,750));
		selectedElement = newElement;
		updateCursor();
	}else{
		Vector2 vect = Vector2(spacing,0.0);
		newElement->setScaling(this->getScaling());
		newElement->setAngle(this->getElementAngle());
		newElement->setDrag(Vector2(750,750));
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
	if (cursor != NULL){
		cursor->rotateFromPoint(rotationAngle, rotationPoint);
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
	if (cursor != NULL){
	cursor->scaleFromPoint(xScaling, yScaling, fromPoint);
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
	if (cursor != NULL){
	cursor->setAngle(newAngle);
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
	if (cursor != NULL){
		cursor->setMask(mask,inverted);
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
void DraggingMenu::setCursor(const std::string& newCursor){
	if (cursor != 0) {
		delete cursor;
	}
	cursor = new Sprite(newCursor);
	updateCursor();
}
void DraggingMenu::onHold(const Vector2 lastPtr, const Vector2 newPtr){
	// Finds the movement to be done.
	if (lastPtr != newPtr) {
		Vector2 comparison = Vector2(1,0);
		comparison.rotate(this->getAngle());
		Vector2 final = Vector2(comparison.getX()*(newPtr-lastPtr).getX(),
								comparison.getY()*(newPtr-lastPtr).getY());
		
		std::list<IMenuElement*>::iterator i = elements.begin();
		while (i != elements.end()) {
			(*i)->setPosition((*i)->getPosition()+final);
			i++;
		}
	}
	isHolded = true;
}
void DraggingMenu::onRelease(const Vector2 lastPtr, const Vector2 newPtr){
	if (lastPtr == newPtr) {
		std::list<IMenuElement*>::iterator i = elements.begin();
		while (i != elements.end()) {
			if((*i)->getAxisAlignedBoundingBox().overlaps(newPtr)){
				selectedElement = (*i);
				updateCursor();
			}
			i++;
		}
	}else{
		Vector2 comparison = Vector2(1,0);
		comparison.rotate(this->getAngle());
		Vector2 final = Vector2(comparison.getX()*(newPtr-lastPtr).getX(),
								comparison.getY()*(newPtr-lastPtr).getY());
		std::list<IMenuElement*>::iterator i = elements.begin();
		while (i != elements.end()) {
			(*i)->setVelocity(final*10);
			i++;
		}
	}
	isHolded = false;
}
void DraggingMenu::updateCursor(){
	if (cursor != 0) {
		cursor->setAngle(this->getElementAngle());
		cursor->setScaling(this->getScaling());
		cursor->setPosition(selectedElement->getPositionCenter()-cursor->getSize()/2);
	}
}
void DraggingMenu::updateVisibility(){
	// Calculates the visibility of each element and the cursor.
	//TODO : optimize this part : when an element is to far set every element left to invisible without calculation.
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->getAxisAlignedBoundingBox().overlaps(this->getAxisAlignedBoundingBox())?
		(*i)->setVisible(true):(*i)->setVisible(false);
		i++;
	}
	cursor->getAxisAlignedBoundingBox().overlaps(this->getAxisAlignedBoundingBox())? 
	cursor->setVisible(true) : cursor->setVisible(false);
}
void DraggingMenu::updateElementsPosition(){
	
	Vector2 left, right;
	right = elements.front()->getPosition() - this->getPosition();
	
	left =  elements.back()->getPosition()+Vector2(elements.back()->getWidth(),0) - (this->getPosition()+Vector2(this->getWidth(),0));
	right.rotate(-this->getAngle());
	left.rotate(-this->getAngle());
	if (elements.front()->getAcceleration() == Vector2(0.0,0.0) && (right.getX() > 0 || left.getX() < 0)) {
		// If the elements aren't accelerating and are off limits.
		// This sets a completly arbiatrary acceleration to all elements.
		Vector2 acc = (right.getX() > 0) ? Vector2(-1500,0) : Vector2(1500,0);
		acc.rotate(this->getAngle());
		std::list<IMenuElement*>::iterator i = elements.begin();
		while (i != elements.end()) {
			(*i)->setAcceleration(acc);
			(*i)->setVelocity((*i)->getVelocity()/4);
			i++;
		}
	}else if (elements.front()->getAcceleration() != Vector2(0.0,0.0) && right.getX() < 0 && left.getX() > 0){
		// If the elements are within the limit but there's still an acceleration
		// This removes it and also the velocity.
		std::list<IMenuElement*>::iterator i = elements.begin();
		while (i != elements.end()) {
			(*i)->setVelocity(0,0);
			(*i)->setAcceleration(0,0);
			i++;
		}
	}
}
std::string DraggingMenu::getSelectedKey() const{
	if (selectedElement != 0) {
		return selectedElement->getKey();
	}else{
		return 0;
	}
}
void DraggingMenu::scaleMaskToMenu(float x, float y){
	internalMask->setScaling((width*x/internalMask->getWidth()), (height*y/internalMask->getHeight()));
	internalMask->setPosition(this->getCenterPosition()-Vector2(internalMask->getWidth()/2,internalMask->getHeight()/2));
}