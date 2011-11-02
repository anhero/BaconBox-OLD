#include "LoopingMenu.h"
using namespace RedBox;
LoopingMenu::LoopingMenu():SelectingMenu(){
}
LoopingMenu::LoopingMenu(float width, float height, float spacing):SelectingMenu(){
	this->width = width;
	this->height = height;
	this->spacing = spacing;
	tweenValue = Vector2(spacing,0.0);
	theTween = Tween<Vector2>(Vector2(0.0,0.0), Vector2(0.0,0.0), 1, ease);
	theTween.start();
}
LoopingMenu::~LoopingMenu(){
	std::list<IMenuElement*>::const_iterator i = fillingElements.begin();
	while (i != fillingElements.end()) {
		delete (*i);
		i++;
	}
}
SelectingMenu* LoopingMenu::clone() const{
	return new LoopingMenu (*this);
}
void LoopingMenu::render(){
	SelectingMenu::render();
	std::list<IMenuElement*>::const_iterator i = fillingElements.begin();
	while (i != fillingElements.end()) {
		(*i)->render();
		i++;
	}
}
void LoopingMenu::scrollTo(std::list<IMenuElement *>::iterator dest, bool force){
	if(!elements.empty()){
		std::list<IMenuElement *>::iterator tempLeft = middle;
		std::list<IMenuElement *>::iterator tempRight = middle;
		unsigned int i = 0;
		while(tempLeft != dest && tempRight != dest && 
			  i <= elements.size()/2){
			if(tempLeft != elements.begin()){
				tempLeft--;
			}else{
				tempLeft = --elements.end();
			}
			if(tempRight != --elements.end()){
				tempRight++;
			}else{
				tempRight = elements.begin();
			}
			i++;
		}
		Vector2 temp = tweenValue;
		temp.rotate(getAngle());
		currentTween = theTween.getValue();
		(*middle)->deselect();
		while (middle != dest) {
			if(tempRight == dest){
				currentTween += temp;
				if(middle != --elements.end()){
					middle++;
				}else{
					middle = elements.begin();
				}
			}else if(tempLeft == dest){
				currentTween -= temp;
				if(middle != elements.begin()){
					middle--;
				}else{
					middle = --elements.end();
				}
			}
		}
		theTween.stop();
		theTween.setStartValue(currentTween);
		theTween.start();
		(*middle)->select();
		updateElementsPosition();
	}
}
void LoopingMenu::updateElementsPosition(){
	if(!elements.empty()){
		
		(*middle)->setPosition(this->getCenterPosition() + 
							   Vector2(-(*middle)->getWidth()/2,
									-(*middle)->getHeight()/2) +
							   theTween.getValue());
		for (std::list<IMenuElement*>::iterator i = elements.begin(); i != elements.end(); i++) {
			(*i)->setVisible(false);
		}
		for (std::list<IMenuElement*>::iterator i = fillingElements.begin(); i != fillingElements.end(); i++) {
			(*i)->setVisible(false);
		}
		
		(*middle)->setVisible(true);
		std::list<IMenuElement*>::iterator iLeft = middle;
		std::list<IMenuElement*>::iterator iRight = middle;
		//calculate the length of the left and right
		int lengthLeft = width/2-spacing/2+theTween.getValue().getX();
		int lengthRight = width/2-spacing/2-theTween.getValue().getX();
		Vector2 vect;
		int i =0;
		//Goes trought each elements
		while (lengthLeft > 0 || lengthRight > 0) {
			i++;
			if(lengthLeft > 0){
				if (iLeft == elements.begin()) {
					iLeft = elements.end();
				}
				iLeft--;
				
				vect = Vector2(spacing,0)*i;
				vect.rotate(getAngle());
				if((*iLeft)->isVisible()){
					//Setup a clone where the real object would be
					std::list<IMenuElement*>::iterator it = fillingElements.begin();
					while (it != fillingElements.end() && ((*it)->getKey() != (*iLeft)->getKey() || (*it)->isVisible())) {
						it++;
					}
					if (it != fillingElements.end()) {
						(*it)->setPosition((*middle)->getPosition()-vect);
						(*it)->setVisible(true);
					}
				}else{
					//Set the position of the real item
					(*iLeft)->setPosition((*middle)->getPosition()-vect);
					(*iLeft)->setVisible(true);
				}
				lengthLeft -= spacing;
			}
			if(lengthRight > 0){
				if (iRight == --elements.end()) {
					iRight = --elements.begin();
				}
				iRight++;
				
				vect = Vector2(spacing,0)*i;
				vect.rotate(getAngle());
				if((*iRight)->isVisible()){
					//Setup a clone where the real object would be
					std::list<IMenuElement*>::iterator it = fillingElements.begin();
					while ((*it)->getKey() != (*iRight)->getKey() || (*it)->isVisible()) {
						it++;
					}
					if (it != fillingElements.end()) {
						(*it)->setPosition((*middle)->getPosition()+vect);
						(*it)->setVisible(true);
					}
				}else{
					//Set the position of the real item
					(*iRight)->setPosition((*middle)->getPosition()+vect);
					(*iRight)->setVisible(true);
				}
				lengthRight -= spacing;
			}
		}
	}

}
void LoopingMenu::generateFillingList(){
	std::list<IMenuElement*>::iterator i = fillingElements.begin();
	if(!fillingElements.empty()){
		while (i != fillingElements.end()) {
			delete (*i);
			i++;
		}
	}
	fillingElements.clear();
	if(elements.size() < this->width/spacing+2){
		float nb = this->width/spacing+2 - elements.size();
		while (nb > 0) {
			for (i = elements.begin(); i != elements.end(); i++) {
				//TODO:faire une copie du IMenuElement vers fillingElements
				fillingElements.push_back((*i)->clone());
				nb--;
			}
		}
	}
}
void LoopingMenu::addElement(IMenuElement* newElement){
	SelectingMenu::addElement(newElement);
	generateFillingList();
	updateElementsPosition();
	
}
void LoopingMenu::setElementAngle(float newAngle){
	elementsAngle = newAngle;
	std::list<IMenuElement*>::iterator i = fillingElements.begin();
	while (i != fillingElements.end()) {
		(*i)->setAngle(newAngle);
		i++;
	}
	SelectingMenu::setElementAngle(newAngle);
}
void LoopingMenu::setInternalMask(GraphicElement<Transformable>* internalMask, bool inverted){
	SelectingMenu::setInternalMask(internalMask, inverted);
	std::list<IMenuElement*>::iterator i = fillingElements.begin();
	while (i != fillingElements.end()) {
		(*i)->setMask(internalMask, inverted);
		i++;
	}
}
void LoopingMenu::onClick(Vector2 ptr){
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
		std::list<IMenuElement*>::iterator i = fillingElements.begin();
		while (i != fillingElements.end() && !(*i)->isSelected) {
			if((*i)->getAxisAlignedBoundingBox().overlaps(ptr)){
				(*i)->select();
				(*i)->isSelected = true;
				(*middle)->deselect();
			}else{
				i++;
			}
		}
		(*middle)->isSelected = true;
		if(i != fillingElements.end()){
			SelectingMenu::scrollTo((*i)->getKey());
		}else{
			(*middle)->isSelected = true;
		}
	}
}