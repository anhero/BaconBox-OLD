#include "OpenGLCharDrawer.h"
using namespace RedBox;

const GLfloat OpenGLCharDrawer::vertexCoordArray[8]= {
 	//-0.5, 0.5, 
//	0.5, 0.5, 
//	-0.5, -0.5, 
//	0.5,-0.5
	
//	0,1,
//	1,1,
//	0,0,
//	1,0
	
	0,0,
	1,0,
	0,-1,
	1,-1
};

OpenGLCharDrawer::OpenGLCharDrawer(): initialized(false), angle(0), x(0), y(0), 
width(0), height(0) {
}

void OpenGLCharDrawer::setSize(int width, int height){
	this->width = width;
	this->height = height;
}

void OpenGLCharDrawer::setPosition(int x, int y){
	this->x = x;
	this->y = y;
}
void OpenGLCharDrawer::setFilename(const std::string& path){
	this->filename = path;
}

void OpenGLCharDrawer::setTexCoord(float minX, float maxX, float minY, float maxY, int imageWidth, int imageHeight){
	
	
	textCoordArray[0] = minX/imageWidth;
	textCoordArray[1] = (imageHeight-maxY)/imageHeight;

	textCoordArray[2] = maxX/imageWidth;
	textCoordArray[3] = textCoordArray[1];
	
	textCoordArray[4] = textCoordArray[0];
	textCoordArray[5] = (imageHeight-minY)/imageHeight;
	
	textCoordArray[6] = textCoordArray[2];
	textCoordArray[7] = textCoordArray[5];
}

void OpenGLCharDrawer::setAngle(int angle){
	this->angle = angle;
}


void OpenGLCharDrawer::render(){
	if(!initialized){
		int tempTex = OpenGLTextureHandleCollection::getTextureHandleForPath(filename);
		
		if ( tempTex < 0) {
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			siTexImagePNG(GL_TEXTURE_2D, GL_RGBA, filename.c_str(), 0, 0);
			OpenGLTextureHandleCollection::addTextureHandle(filename, tex, NULL, NULL);
		}
		else {
			tex = tempTex;
			glBindTexture(GL_TEXTURE_2D, tex);
		}
		
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		initialized = true;
		
	}
	else {
		glBindTexture(GL_TEXTURE_2D, tex);
	}
	
	glPushMatrix();
	
	glRotatef(angle, 0, 0, 1);
	glTranslatef(x, y, 0);
	glScalef(width, height, 1);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	glVertexPointer(2, GL_FLOAT, 0, vertexCoordArray);
    glEnableClientState(GL_VERTEX_ARRAY);
	
	glTexCoordPointer(2, GL_FLOAT, 0, textCoordArray);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	glPopMatrix();
	
    glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

int OpenGLCharDrawer::getHeight() {
	return height;
}
int OpenGLCharDrawer::getWidth() {
	return width;
}
