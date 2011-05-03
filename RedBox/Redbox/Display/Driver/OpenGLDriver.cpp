#include "OpenGLDriver.h"

#include <stdint.h>

#include <iostream>

#include "RenderInfo.h"
#include "TextureInfo.h"
#include "MathHelper.h"

using namespace RedBox;

void OpenGLDriver::drawShapeWithTextureAndColor(GLfloat* vertices,
												RenderInfo& renderingInfo,
												unsigned int nbVertices){
	 //@TODO: Check for possible optimizations
	const uint8_t* tempColor = renderingInfo.getColor().getComponents();
	uint8_t color[nbVertices * 4];
	unsigned int componentCount = nbVertices * 4;
	for	(unsigned int i = 0; i < componentCount; i++) {
		color[i] = tempColor[i % 4];
	}

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, color);
	drawShapeWithTexture(vertices, renderingInfo, nbVertices);
	
	glDisableClientState(GL_COLOR_ARRAY);

}

void OpenGLDriver::drawShapeWithTexture(GLfloat* vertices,
										RenderInfo& renderingInfo,
										unsigned int nbVertices){
	glBindTexture(GL_TEXTURE_2D, renderingInfo.getTexInfo().textureId);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	
	
	glTexCoordPointer(2, GL_FLOAT, 0, &(renderingInfo.getTexCoords()[renderingInfo.getCurrentFrame()][0]));
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void OpenGLDriver::drawShapeWithColor(GLfloat* vertices,
									  RenderInfo &renderingInfo,
									  unsigned int nbVertices) {
	const uint8_t* tempColor = renderingInfo.getColor().getComponents();
	unsigned int componentCount = nbVertices * 4;
	uint8_t color[componentCount];
	for(unsigned int i = 0; i < componentCount; ++i) {
		color[i] = tempColor[i % 4];
	}
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, color);

	glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BLEND);
	glDisableClientState(GL_COLOR_ARRAY);
}

void OpenGLDriver::prepareScene(int xTranslation, int yTranslation,
								int angle, float zoom,
								const Color& backgroundColor) {
	glClearColor(clampColorComponent(backgroundColor.getRed()),
				 clampColorComponent(backgroundColor.getGreen()),
				 clampColorComponent(backgroundColor.getBlue()),
				 1.0f);
    glClear( GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glRotatef(angle, 0, 0, 1);
	glTranslatef(xTranslation, yTranslation, 0);
	glScalef(zoom, zoom, 1);

}

void OpenGLDriver::initializeGraphicDriver(int screenWidth, int screenHeight) {
	glShadeModel(GL_FLAT);
	
	glViewport(0,0,screenWidth, screenHeight);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef RB_IPHONE_PLATFORM
	glOrthof(0, screenWidth, screenHeight, 0, -1, 1);
#else
	glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
#endif
#ifdef RB_MAC_PLATFORM
	int swapInterval = 1;
	CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
#endif
}


TextureInfo * OpenGLDriver::loadTexture(PixMap * pixMap){
	
	
	TextureInfo* texInfo = new TextureInfo();
	glGenTextures(1, &(texInfo->textureId));
	glBindTexture(GL_TEXTURE_2D, texInfo->textureId);
	
	
	
	int widthPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getWidth());
	int heightPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getHeight());

	
	PixMap poweredTo2Pixmap(widthPoweredToTwo, heightPoweredToTwo, pixMap->getColorFormat());
	poweredTo2Pixmap.insertSubPixMap(pixMap);


	texInfo->imageWidth = pixMap->getWidth();
	texInfo->imageHeight = pixMap->getHeight();
	
	texInfo->poweredWidth = widthPoweredToTwo;
	texInfo->poweredHeight = heightPoweredToTwo;
	
	GLint format;
	
	if(pixMap->getColorFormat() == RGBA){
		format = GL_RGBA;
	}
	else if (pixMap->getColorFormat() == Alpha) {
		format = GL_ALPHA;
	}
	
	glTexImage2D(
				 GL_TEXTURE_2D,
				 0,
				 format,
				 widthPoweredToTwo,
				 heightPoweredToTwo,
				 0,
				 format,
				 GL_UNSIGNED_BYTE,
				 poweredTo2Pixmap.getBuffer());
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	return texInfo;
}

float OpenGLDriver::clampColorComponent(unsigned int component) {
	return static_cast<float>(component) / static_cast<float>(Color::MAX_COMPONENT_VALUE);
}

