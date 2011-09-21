#include "IMenuElement.h"
using namespace RedBox;

/**
 * Default constructor.
 */
IMenuElement::IMenuElement(std::string key): isSelected(false), key(key){
	
}

/**
 * Copy constructor.
 * @param src Emitter to make a copy of.
 */
IMenuElement::IMenuElement(const IMenuElement& src){
}

/**
 * Destructor.
 */
IMenuElement::~IMenuElement(){
}

void IMenuElement::setVisible(bool newVisible){
	Body::setVisible(newVisible);
}
std::string IMenuElement::getKey(){
	return key;
}