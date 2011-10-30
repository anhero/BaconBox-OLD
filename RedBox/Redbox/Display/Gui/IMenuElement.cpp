#include "IMenuElement.h"
using namespace RedBox;

/**
 * Default constructor.
 */
IMenuElement::IMenuElement(const std::string& newKey): isSelected(false), key(newKey){
	
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
	setVisible(newVisible);
}
std::string IMenuElement::getKey(){
	return key;
}