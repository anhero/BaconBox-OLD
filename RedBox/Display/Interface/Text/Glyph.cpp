#include "Glyph.h"

using namespace RedBox;


void Glyph::setHoriAdvance(int horiAdvance){
	this->horiAdvance = horiAdvance;
}

int Glyph::getXAdvance(){
	return horiAdvance;
}

void Glyph::setHoriBearingX(int horiBearingX){
	this->horiBearingX = horiBearingX;
}

int Glyph::getHoriBearingX(){
	return horiBearingX;
}

void Glyph::setHoriBearingY(int topDisplacement){
	this->horiBearingY = horiBearingY;
}

int Glyph::getHoriBearingY(){
	return horiBearingY;

}

void Glyph::setTextureInfo( TextureInfo * textureInfo){
	this->textureInfo = textureInfo;
}
TextureInfo * Glyph::getTextureInfo(){
	return textureInfo;
}

int Glyph::getHeight(){
	return height;
}

void Glyph::setHeight(int height){
	this->height = height;
}

int Glyph::getWidth(){
	return width;
}

void Glyph::setWidth(int width){
	this->width = width;
}