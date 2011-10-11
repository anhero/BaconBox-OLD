#include "IMenu.h"
using namespace RedBox;

IMenu::IMenu(){
	
}
IMenu::~IMenu(){
	std::list<IMenuElement*>::const_iterator i = elements.begin();
	while (i != elements.end()) {
		delete (*i);
		i++;
	}
}
IMenu::IMenu(const IMenu &src){
	std::list<IMenuElement*>::const_iterator i = src.elements.begin();
	while (i != src.elements.end()) {
		elements.push_back((*i)->clone());
		i++;
	}
}
void IMenu::addElement(IMenuElement* newElement){
	elements.push_back(newElement);
}
void IMenu::removeElement(IMenuElement* toBeRemoved){
	elements.remove(toBeRemoved);
}
void IMenu::render(){
	std::list<IMenuElement*>::const_iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->render();
		i++;
	}
}
void IMenu::update(){
	std::list<IMenuElement*>::const_iterator i = elements.begin();
	while (i != elements.end()) {
		(*i)->update();
		i++;
	}
}
float IMenu::getWidth() const{
	if(!elements.empty()){
		Vector2 vect = Vector2(width, height);
		vect.rotate(getAngle());
		//the absolute X value of the vect is the width
		return (vect.getX() > -vect.getX())? vect.getX() : -vect.getX();
	}else{
		return 0;
	}
}
float IMenu::getHeight() const{
	if(!elements.empty()){
		Vector2 vect = Vector2(width, height);
		vect.rotate(getAngle());
		//the absolute Y value of the vect is the height
		return (vect.getY() > -vect.getY())? vect.getY() : -vect.getY();
	}else{
		return 0;
	}
}