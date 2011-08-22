#include "StringFX.h"

using namespace RedBox;

void StringFX::setMode(StringFXMode mode){
	this->mode = mode;
}

StringFXMode StringFX::getMode(){
	return mode;
}

void StringFX::setColor(int * color){
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
	this->color[3] = color[3];
}

void StringFX::setColor(int red, int green, int blue, int alpha){
	this->color[0] = red;
	this->color[1] = green;
	this->color[2] = blue;
	this->color[3] = alpha;
}

int* StringFX::getColor(){
	return color;	
}

void StringFX::setDirectionVector(const Vector2& newDirectionVector){
	this->directionVector = newDirectionVector;
}

const Vector2& StringFX::getDirectionVector() const {
	return directionVector;
}
