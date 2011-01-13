
#include "OpenGLDrawer.h"


using namespace RedBox;

void OpenGLDrawer::drawShapeWithTextureAndColor(GLfloat * vertexArray, GLfloat * textCoordArray, GLubyte * colorArray, GLuint textureID, int numberOfVertex){	
	
	
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colorArray);
	glEnableClientState(GL_COLOR_ARRAY);
	drawShapeWithTexture(vertexArray, textCoordArray, textureID, numberOfVertex);
	
	glDisableClientState(GL_COLOR_ARRAY);

}

void OpenGLDrawer::drawShapeWithTexture(GLfloat * vertexArray, GLfloat * textCoordArray, GLuint textureID, int numberOfVertex){
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glVertexPointer(2, GL_FLOAT, 0, vertexArray);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	
	
	glTexCoordPointer(2, GL_FLOAT, 0, textCoordArray);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertex);
	
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
