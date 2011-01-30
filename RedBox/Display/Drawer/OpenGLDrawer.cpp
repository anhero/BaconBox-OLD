
#include "OpenGLDrawer.h"


using namespace RedBox;

void OpenGLDrawer::drawShapeWithTextureAndColor(GLfloat* vertices,
												const RenderInfo& renderingInfo,
												unsigned int nbVertices){
	
	
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, renderingInfo.color);
	glEnableClientState(GL_COLOR_ARRAY);
        drawShapeWithTexture(vertices, renderingInfo, nbVertices);
	
	glDisableClientState(GL_COLOR_ARRAY);

}

void OpenGLDrawer::drawShapeWithTexture(GLfloat* vertices,
										const RenderInfo& renderingInfo,
										unsigned int nbVertices){
	glBindTexture(GL_TEXTURE_2D, renderingInfo.textureID);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	
	
	glTexCoordPointer(2, GL_FLOAT, 0, &(*(renderingInfo.texCoords.begin())));
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, nbVertices);
	
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
