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

void Glyph::setTextureInfo(const TextureInfo & textureInfo){
	this->textureInfo = textureInfo;
}
TextureInfo & Glyph::getTextureInfo(){
	return textureInfo;
}

float * Glyph::getTextureCoordinates(){
	return textureCoordinates;
}
void Glyph::setTextureCoordinates(const float * textureCoordinates){
	for (int i = 0; i <8; i++) {
		this->textureCoordinates[i] = textureCoordinates[i];
	}
}
