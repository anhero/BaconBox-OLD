#include "GraphicChar.h"

using namespace RedBox;

GraphicChar::GraphicChar(): xAdvance(0), xOffset(0), yOffset(0) {
}

void GraphicChar::render(){
	renderedChar.render();
}
void GraphicChar::setPosition(int x, int y){
	renderedChar.setPosition(x, y);
}
void GraphicChar::setAngle(int angle){
	renderedChar.setAngle(angle);
}
void GraphicChar::setSize(int width, int height){
	renderedChar.setSize(width, height);
}
void GraphicChar::setFilename(const std::string& path){
	renderedChar.setFilename(path);
}

void GraphicChar::setTexCoord(float minX, float maxX, float minY, float maxY, int imageWidth, int imageHeight){
	renderedChar.setTexCoord(minX, maxX, minY, maxY, imageWidth, imageHeight);
}

void GraphicChar::setXOffset(int offset){
	xOffset = offset;
}
void GraphicChar::setYOffset(int offset){
	yOffset = offset;
}
void GraphicChar::setXAdvance(int advance){
	xAdvance = advance;
}

int GraphicChar::getXOffset(){
	return xOffset;
}

int GraphicChar::getYOffset(){
	return yOffset;
}

int GraphicChar::getXAdvance(){
	return xAdvance;
}

int GraphicChar::getWidth() {
	return renderedChar.getWidth();
}
int GraphicChar::getHeight() {
	return renderedChar.getHeight();
}
