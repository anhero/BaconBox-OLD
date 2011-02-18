
#include "OpenGLDrawer.h"


using namespace RedBox;

void OpenGLDrawer::drawShapeWithTextureAndColor(GLfloat* vertices,
												RenderInfo& renderingInfo,
												unsigned int nbVertices){
	
	
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, renderingInfo.getColor());
	glEnableClientState(GL_COLOR_ARRAY);
        drawShapeWithTexture(vertices, renderingInfo, nbVertices);
	
	glDisableClientState(GL_COLOR_ARRAY);

}

void OpenGLDrawer::drawShapeWithTexture(GLfloat* vertices,
										RenderInfo& renderingInfo,
										unsigned int nbVertices){
	glBindTexture(GL_TEXTURE_2D, renderingInfo.getTexInfo().textureId);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	
	
	glTexCoordPointer(2, GL_FLOAT, 0, &(*(renderingInfo.getTexCoords().begin())));
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
	
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


void OpenGLDrawer::prepareScene(int xTranslation, int yTranslation, int angle, float zoom) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glRotatef(angle, 0, 0, 1);
	glTranslatef(xTranslation, xTranslation, 0);
	glScalef(zoom, zoom, 1);

}

void OpenGLDrawer::initializeDrawer(int screenWidth, int screenHeight) {
	glViewport(0,0,screenWidth, screenHeight);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef RB_IPHONE_PLATFORM
	glOrthof(0, screenWidth, 0, screenHeight, -1, 1);
#else
	glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
#endif

}


