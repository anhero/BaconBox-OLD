
#include "OpenGLDrawer.h"


using namespace RedBox;

void OpenGLDrawer::drawShapeWithTextureAndColor(GLfloat * vertices,GLfloat *  textCoordArray , RenderInfo * renderingInfo, int nbVertices){
	
	
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, renderingInfo->colors);
	glEnableClientState(GL_COLOR_ARRAY);
        drawShapeWithTexture(vertices, textCoordArray, renderingInfo->textureID, nbVertices);
	
	glDisableClientState(GL_COLOR_ARRAY);

}

void OpenGLDrawer::drawShapeWithTexture(GLfloat * vertices,GLfloat *  textCoordArray , RenderInfo * renderingInfo, int nbVertices){
	glBindTexture(GL_TEXTURE_2D, renderingInfo->textureID);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	
	
	glTexCoordPointer(2, GL_FLOAT, 0, textCoordArray);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
	
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
