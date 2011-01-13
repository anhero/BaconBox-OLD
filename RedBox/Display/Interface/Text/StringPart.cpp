#include "StringPart.h"

using namespace RedBox;

StringPart::StringPart():angle(0), drawer(NULL) {
	drawer = new OpenGLStringPartDrawer(this);
}

StringPart::~StringPart() {
	if (drawer) {
		delete drawer;
	}
}

int StringPart::getXPosition(){
	return x;
}

int StringPart::getYPosition(){
	return y;
}

int StringPart::getWidth(){
	return width;
}
int StringPart::getHeight(){
	return height;
}

void StringPart::setTotalXAdvance(int advance){
	totalXAdvance = advance;
}

int StringPart::getTotalXAdvance(){
	return totalXAdvance;
}

void StringPart::setXAdvance(int advance){
	xAdvance = advance;
}

int StringPart::getXAdvance(){
	return xAdvance;
}


void StringPart::setTopDisplacement(int displacement){
	topDisplacement = displacement;
}


int StringPart::getTopDisplacement(){
	return topDisplacement;
}

void StringPart::setBitmap(unsigned char * bitmap, const std::string& key){
	drawer->setBitmap(bitmap, key);
}

void StringPart::setXPosition(int x){
	this->x = x;
}

void StringPart::setYPosition(int y){
	this->y = y;
}

void StringPart::setupStringPart(int width, int height, int textureWidth, int textureHeight){
	this->width = width;
	this->height = height;
	drawer->setTextureInfo(0, width, 0, height, textureWidth, textureHeight);
}

void StringPart::render(){
	drawer->render();
}

void StringPart::setLeftDisplacement(int displacement){
	leftDisplacement = displacement;
}

int StringPart::getLeftDisplacement(){
	return  leftDisplacement;
}

void StringPart::setAngle(double angle){
	this->angle = angle;
}

double StringPart::getAngle(){
	return angle;
}

