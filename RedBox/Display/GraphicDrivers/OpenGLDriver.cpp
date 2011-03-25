#include "OpenGLDrawer.h"

#include "RenderInfo.h"
#include "TextureInfo.h"
#include "MathHelper.h"
using namespace RedBox;

void OpenGLDriver::drawShapeWithTextureAndColor(GLfloat* vertices,
												RenderInfo& renderingInfo,
												unsigned int nbVertices){
	
	
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, renderingInfo.getColor());
	glEnableClientState(GL_COLOR_ARRAY);
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
}


void OpenGLDriver::prepareScene(int xTranslation, int yTranslation, int angle, float zoom) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glRotatef(angle, 0, 0, 1);
	glTranslatef(xTranslation, yTranslation, 0);
	glScalef(zoom, zoom, 1);

}

void OpenGLDriver::initializeDriver(int screenWidth, int screenHeight) {
	glViewport(0,0,screenWidth, screenHeight);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef RB_IPHONE_PLATFORM
	glOrthof(0, screenWidth, screenHeight, 0, -1, 1);
#else
	glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
#endif

}


TextureInfo * loadRGBATexture(unsigned Byte * pixMap, int width, int height){
	
	
	TextureInfo* texInfo = new TextureInfo();
	glGenTextures(1, &(texInfo->textureId));
	glBindTexture(GL_TEXTURE_2D, texInfo->textureId);
	
	

	
	int widthPoweredToTwo = MathHelper::nextPowerOf2(glyphWidth);
	int heightPoweredToTwo = MathHelper::nextPowerOf2(glyphHeight);

	unsigned char * poweredTo2RGBABuffer =  new unsigned Byte [(widthPoweredToTwo * 4)  * (heightPoweredToTwo * 4)];	

	///Place small buffer in powered buffer here TODO
	
	
	

	texInfo->imageWidth = widthPoweredToTwo;
	texInfo->imageWidth = heightPoweredToTwo;
	
	
	glTexImage2D(
				 GL_TEXTURE_2D,
				 0,
				 GL_RGBA,
				 widthPoweredToTwo,
				 heightPoweredToTwo,
				 0,
				 GL_RGBA,
				 GL_UNSIGNED_BYTE,
				 poweredTo2RGBABuffer);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

