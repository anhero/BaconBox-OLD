#include "NullGraphicsDriver.h"

#include <stdint.h>

#include <iostream>

#include "RenderInfo.h"
#include "TextureInfo.h"
#include "MathHelper.h"

using namespace RedBox;

void NullGraphicsDriver::drawShapeWithTextureAndColor(float* vertices,
												RenderInfo& renderingInfo,
												unsigned int nbVertices){
}

void NullGraphicsDriver::drawShapeWithTexture(float* vertices,
										RenderInfo& renderingInfo,
										unsigned int nbVertices){
}

void NullGraphicsDriver::drawShapeWithColor(float* vertices,
									  RenderInfo &renderingInfo,
									  unsigned int nbVertices) {
}

void NullGraphicsDriver::prepareScene(int xTranslation, int yTranslation,
									  int angle, float zoom,
									  const Color& backgroundColor,
									  const Vec2& rotationCenterOffset) {
}

void NullGraphicsDriver::initializeGraphicDriver(int screenWidth, int screenHeight) {
}


TextureInfo * NullGraphicsDriver::loadTexture(PixMap* pixMap){
	//@TODO: Check this...
	
	TextureInfo* textureInfo = new TextureInfo();
	
	textureInfo->imageWidth = pixMap->getWidth();
	textureInfo->imageHeight = pixMap->getHeight();
	
	return textureInfo;
}

float NullGraphicsDriver::clampColorComponent(unsigned int component) {
	return static_cast<float>(component) / static_cast<float>(Color::MAX_COMPONENT_VALUE);
}

