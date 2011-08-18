#include "NullGraphicsDriver.h"

#include <stdint.h>

#include <iostream>

#include "RenderInfo.h"
#include "TextureInfo.h"
#include "MathHelper.h"

using namespace RedBox;

void NullGraphicsDriver::drawShapeWithTextureAndColor(float*, RenderInfo&,
        unsigned int) {
}

void NullGraphicsDriver::drawShapeWithTexture(float*, RenderInfo&,
        unsigned int) {
}

void NullGraphicsDriver::drawShapeWithColor(float*, RenderInfo&, unsigned int) {
}

void NullGraphicsDriver::drawMaskShapeWithTexture(GLfloat*, RenderInfo&,
        unsigned int) {
}

void NullGraphicsDriver::unmask(GLfloat*, RenderInfo&, unsigned int) {
}

void NullGraphicsDriver::drawMaskShapeWithTextureAndColor(GLfloat*, RenderInfo&,
        unsigned int) {
}

void NullGraphicsDriver::drawMaskedShapeWithTextureAndColor(GLfloat*,
        RenderInfo&,
        unsigned int, bool) {
}

void NullGraphicsDriver::prepareScene(int, int, int, float, const Color&,
                                      const Vector2&) {
}

void NullGraphicsDriver::initializeGraphicDriver(int, int) {
}


TextureInfo* NullGraphicsDriver::loadTexture(PixMap* pixMap) {
	//@TODO: Check this...

	TextureInfo* textureInfo = new TextureInfo();

	textureInfo->imageWidth = pixMap->getWidth();
	textureInfo->imageHeight = pixMap->getHeight();

	return textureInfo;
}

