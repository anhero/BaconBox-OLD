#include "ScrollingMenu.h"
using namespace RedBox;
ScrollingMenu::ScrollingMenu():SelectingMenu(){
}
ScrollingMenu::ScrollingMenu(float width, float height, float spacing):SelectingMenu(){
	this->width = width;
	this->height = height;
	this->spacing = spacing;
	tweenValue = Vector2(spacing,0.0);
}
ScrollingMenu* ScrollingMenu::clone() const{
	return new ScrollingMenu (*this);
}
void ScrollingMenu::scrollTo(std::list<IMenuElement *>::iterator dest, bool force){
	//TODO:onClick from the last to the first fix this!!!
	if(!elements.empty() && 
	   ((dest != elements.begin() || middle != --elements.end()) && 
	   (dest != --elements.end() || middle != elements.begin()) || force)){
		
		std::list<IMenuElement *>::iterator tempLeft = middle;
		std::list<IMenuElement *>::iterator tempRight = middle;
		unsigned int i = 0;
		while(tempLeft != dest && tempRight != dest && 
			  i <= elements.size()/2){
			if(tempLeft != elements.begin()){
				tempLeft--;
			}
			if(tempRight != --elements.end()){
				tempRight++;
			}
		}
		Vector2 temp = tweenValue;
		temp.rotate(getAngle());
		(*middle)->deselect();
		while (middle != dest) {
			if(tempRight == dest){
				currentTween += temp;
				middle++;
			}else if(tempLeft == dest){
				currentTween -= temp;
				middle--;
			}
		}
		//Tween::to(currentTween,Vector2(0.0,0), 1, ease);
		(*middle)->select();
		updateElementsPosition();
	}
}
void ScrollingMenu::addElement(IMenuElement* newElement){
	SelectingMenu::addElement(newElement);
	updateElementsPosition();
}
void ScrollingMenu::updateElementsPosition(){
	if(!elements.empty()){
		
		std::list<IMenuElement*>::iterator iLeft = middle;
		std::list<IMenuElement*>::iterator iRight = middle;
		
		(*middle)->setPosition(this->getCenterPosition() + 
							   Vector2(-(*middle)->getWidth()/2,
									-(*middle)->getHeight()/2) +
							   currentTween);
		
		//calculate the length of the left and right
		int lengthLeft = width/2-spacing/2+currentTween.getX();
		int lengthRight = width/2-spacing/2-currentTween.getX();
		Vector2 vect;
		int i =0;
		//Goes trought each elements
		while (iLeft != elements.begin() || iRight != --elements.end()) {
			i++;
			if(iLeft != elements.begin()){
				iLeft--;
				if(lengthLeft > 0){
					//Calculate the position
					vect = Vector2(spacing,0)*i;
					vect.rotate(getAngle());
					(*iLeft)->setPosition((*middle)->getPosition()-vect);
					(*iLeft)->setVisible(true);
					lengthLeft -= spacing;
				}else{
					(*iLeft)->setVisible(false);
				}
			}
			if(iRight != --elements.end()){
				iRight++;
				if(lengthRight > 0){
					//Calculate the position
					vect = Vector2(spacing,0)*i;
					vect.rotate(getAngle());
					(*iRight)->setPosition((*middle)->getPosition()+vect);
					(*iRight)->setVisible(true);
					lengthRight -= spacing;
				}else{
					(*iRight)->setVisible(false);
				}
			}
		}
		(*middle)->setVisible(true);
	}
}