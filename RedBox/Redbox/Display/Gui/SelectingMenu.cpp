#include "SelectingMenu.h"
#include <cmath>
using namespace RedBox;

SelectingMenu::SelectingMenu():IMenu(), ease(Ease::OUT_CUBIC){
	
}
SelectingMenu::SelectingMenu(float width, float height, float spacing):IMenu(), ease(Ease::OUT_CUBIC){
	this->width = width;
	this->height = height;
	this->spacing = spacing;
}
SelectingMenu::SelectingMenu(const SelectingMenu &src):IMenu::IMenu(src), ease(Ease::OUT_CUBIC){
}
SelectingMenu::~SelectingMenu(){
}
void SelectingMenu::update(){
	IMenu::update();
	if(currentTween != Vector2(0.0,0.0)){
		updateElementsPosition();
	}
//	Pointer* ptr = Pointer::getDefault();
//	// We make sure the pointer is initialized.
//	if(ptr) {
//		// If the cursor is over the menu.
//		if(AABB::overlaps(ptr->getPosition(), getAABB()) && ptr->isButtonPressed(CursorButton::LEFT)) {
//			onClick(ptr);
//		}
//	}
}
void SelectingMenu::addElement(IMenuElement* newElement){
	IMenu::addElement(newElement);
	if(elements.size() == 1){
		middle = elements.begin();
	}
}
void SelectingMenu::setCenterPosition(RedBox::Vector2 vect){
	
	IMenu::setPosition(vect.getX()-getWidth()/2, vect.getY()-getHeight()/2);
	if(internalMask != NULL){
		internalMask->setPosition(vect-Vector2(width/2, height/2));
	}
	updateElementsPosition();
}
void SelectingMenu::setPosition(float x, float y){
	
	Collidable::setPosition(x, y);
	if(internalMask != NULL){
		internalMask->setPosition(x, y);
	}
	updateElementsPosition();
}
Vector2 SelectingMenu::getCenterPosition(){
	
	//std::cout<< this->getWidth()/2 << " : "<< this->getHeight()/2 << std::endl;
	return this->getPosition() + Vector2(this->getWidth()/2, this->getHeight()/2);
}

void SelectingMenu::rotateFromPoint(float rotationAngle, const Vector2& rotationPoint){
	Vector2 vect = getCenterPosition();
	this->Collidable::rotateFromPoint(rotationAngle, rotationPoint);
	if (internalMask != NULL) {
		internalMask->rotateFromPoint(rotationAngle, rotationPoint);
	}
	setCenterPosition(vect);
	updateElementsPosition();
	if(internalMask != NULL){
		internalMask->setPosition(this->getCenterPosition()-Vector2(internalMask->getWidth()/2,internalMask->getHeight()/2));
	}
}
void SelectingMenu::setElementAngle(float newAngle){
	elementsAngle = newAngle;
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->setAngle(newAngle);
		i++;
	}
	updateElementsPosition();
}
void SelectingMenu::setInternalMask(GraphicElement<Transformable>* mask, bool inverted){
	internalMask = mask;
	internalMask->setPosition(this->getCenterPosition()-Vector2(internalMask->getWidth()/2,+internalMask->getHeight()/2));
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->setMask(mask,inverted);
		i++;
	}
}
void SelectingMenu::setMask(Maskable* mask, bool inverted){

}
Maskable* SelectingMenu::getMask() const{
	return this->currentMask;
}
Maskable* SelectingMenu::getInternalMask(){
	return this->internalMask;
}
float SelectingMenu::getElementAngle(){
	return elementsAngle;
}
void SelectingMenu::mask(){
}
void SelectingMenu::unmask(){
}
void SelectingMenu::onClick(Vector2 ptr){
	(*middle)->isSelected = false;
	std::list<IMenuElement*>::iterator i = elements.begin();
	while (i != elements.end() && !(*i)->isSelected) {
		if((*i)->getAxisAlignedBoundingBox().overlaps(ptr)){
			(*i)->select();
			(*i)->isSelected = true;
			(*middle)->deselect();
		}else{
			i++;
		}
	}
	if(i != elements.end()){
		scrollTo(i,true);
	}else{
		(*middle)->isSelected = true;
	}
}
void SelectingMenu::scrollForward(){
	std::list<IMenuElement *>::iterator dest = middle;
	++dest;
	if (dest == elements.end()) {
		dest = elements.begin();
	}
	scrollTo(dest);
}
void SelectingMenu::scrollBackward(){
	std::list<IMenuElement *>::iterator dest = middle;
	if (dest == elements.begin()) {
		dest = elements.end();
	}
	--dest;
	scrollTo(dest);
}
void SelectingMenu::scrollTo(std::string key){
	std::list<IMenuElement *>::iterator i = elements.begin();
	while ((*i)->getKey() != key && i != elements.end()) {
		i++;
	}
	if(i != elements.end()){
		scrollTo(i);
	}
}
void SelectingMenu::scaleMaskToMenu(float x, float y){
	internalMask->setScaling((width*x/internalMask->getWidth()), (height*y/internalMask->getHeight()));
	internalMask->setPosition(this->getCenterPosition()-Vector2(internalMask->getWidth()/2,internalMask->getHeight()/2));
}
std::string SelectingMenu::getSelectedKey() const{
	if (!elements.empty()) {
		return (*middle)->getKey();
	}else{
		return 0;
	}
}