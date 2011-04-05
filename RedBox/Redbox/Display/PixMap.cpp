#include "PixMap.h"
#include "Debug.h"
#include <algorithm>

using namespace RedBox;

PixMap::PixMap(int width, int height, ColorFormat colorFormat){
	int pixelByteCount;
	if(colorFormat == RGBA){
		pixelByteCount = 4;
	}
	else if (colorFormat == Alpha){
		pixelByteCount = 1;
	}
	
	buffer = new uint8_t[width * height * pixelByteCount * pixelByteCount];
	this->width = width;
	this->height = height;
	this->colorFormat = colorFormat;
	
}

PixMap::PixMap(uint8_t * buffer, int width, int height, ColorFormat colorFormat){
	this->buffer = buffer;
	this->width = width;
	this->height = height;
	this->colorFormat = colorFormat;
}

PixMap::~PixMap(){
	delete [] buffer;
}


int PixMap::getWidth(){
	return width;
}

int PixMap::getHeight(){
	return height;
}

ColorFormat PixMap::getColorFormat(){
	return colorFormat;
}

uint8_t * PixMap::getBuffer(){
	return buffer;
}

void PixMap::insertSubPixMap(PixMap * subPixMap, int xOffset, int yOffset){
	if (subPixMap->getColorFormat() == colorFormat){
		insertSubPixMap(subPixMap->getBuffer(), subPixMap->getWidth(), subPixMap->getHeight(), xOffset, yOffset);
	}
	else {
		$ECHO("Can't insert sub pixmap into current pixmap, because the color format isn't compatible.");
	}
}


void PixMap::insertSubPixMap(uint8_t * subBuffer, int width, int height, int xOffset, int yOffset){
	int pixelByteCount;
	
	int currentWidth = this->width;
	int currentHeight = this->height;
	
	int maxX = std::min(width - 1 + xOffset, currentWidth);
	int maxY = std::min(height -1  + yOffset, currentHeight);
	
	int baseX = std::max(xOffset, 0);
	int baseY = std::max(yOffset, 0);
	
	if (maxX > baseX && maxY > baseX) {
		
		if(colorFormat == RGBA){
			pixelByteCount = 4;
		}
		else if (colorFormat == Alpha){
			pixelByteCount = 1;
		}
		
		for (int i = baseY ; i <= maxY; i++){
			for (int j = baseX; j <= maxX; j++) {
				for(int k = 0 ; k < pixelByteCount; k++){
					buffer[(currentWidth * ( i - yOffset) + (j - xOffset)) * pixelByteCount +k] =
					subBuffer[(width * i + j) * pixelByteCount + k];
				}
			}
		}
	}
}
