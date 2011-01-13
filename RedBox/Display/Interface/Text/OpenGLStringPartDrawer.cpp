#include "OpenGLStringPartDrawer.h"

using namespace RedBox;

const GLfloat OpenGLStringPartDrawer::vertexCoordArray[8]= {
	0,0,
	1,0,
	0,-1,
	1,-1
}; 


OpenGLStringPartDrawer::OpenGLStringPartDrawer(StringPart * parent){
	parentStringPart = parent;
}

void OpenGLStringPartDrawer::setTextureInfo(float minX, float maxX, float minY, float maxY, int imageWidth, int imageHeight){
	textCoordArray[0] = 0;
	textCoordArray[1] = 0;
	
	textCoordArray[2] = maxX/imageWidth;
	textCoordArray[3] = 0;
	
	textCoordArray[4] = 0;
	textCoordArray[5] = maxY/imageHeight;
	
	textCoordArray[6] = maxX/imageWidth;
	textCoordArray[7] = textCoordArray[5];
	
	textureWidth = imageWidth;
	textureHeight = imageHeight;
}


void OpenGLStringPartDrawer::setBitmap(unsigned char * bitmap, const std::string& key){
	int tempTex = OpenGLTextureHandleCollection::getTextureHandleForPath(key);
	if ( tempTex < 0) {
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		OpenGLTextureHandleCollection::addTextureHandle(key, tex);
		
		glTexImage2D(
					 GL_TEXTURE_2D,
					 0,
					 //internalFormat
					 GL_ALPHA,
					 textureWidth,
					 textureHeight,
					 0,
					 GL_ALPHA,
					 GL_UNSIGNED_BYTE,
					 bitmap);
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		tex = tempTex;
	}
}

void OpenGLStringPartDrawer::render(){
	
	glBindTexture(GL_TEXTURE_2D, tex);

	glPushMatrix();
	
	glTranslatef(parentStringPart->getXPosition(), parentStringPart->getYPosition(), 0);

	glRotatef(parentStringPart->getAngle(), 0, 0, 1);
	
	glTranslatef(parentStringPart->getTotalXAdvance()+parentStringPart->getLeftDisplacement(), parentStringPart->getTopDisplacement(), 0);


	//glTranslatef(parentStringPart->getXPosition(), parentStringPart->getYPosition(), 0);
	

	glScalef(parentStringPart->getWidth(), parentStringPart->getHeight(), 1);
	//glScalef(xZoomFactor, yZoomFactor, 1);
	
	//static GLuint squareColors[] = { 135, 10, 253, 170,
//							  135, 10, 253, 170,
//							  135, 10, 253, 170,
//		135, 10, 253, 170,};
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	//glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
//	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, vertexCoordArray);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glTexCoordPointer(2, GL_FLOAT, 0, textCoordArray);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	glPopMatrix();
	
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}