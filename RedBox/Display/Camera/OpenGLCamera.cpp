
//TODO: NOT hardcoding the viewport size
//#define IPHONE_WIDTH 320
//#define IPHONE_HEIGHT 480


#include "OpenGLCamera.h"

using namespace RedBox;

OpenGLCamera::OpenGLCamera(): angle(0.0f), x(0.0), y(0.0), screenWidth(0), 
screenHeight(0), iPhoneOrientation(portrait), zoomFactor(1.0), 
initialized(false), offsetX(0.0), offsetY(0.0) {
}

OpenGLCamera::OpenGLCamera(int newScreenWidth, int newScreenHeight, 
						   IPhoneOrientationEnum orientation): angle(0.0f),
x(0.0), y(0.0), screenWidth(newScreenWidth), screenHeight(newScreenHeight), 
iPhoneOrientation(orientation), zoomFactor(1.0), initialized(false), 
offsetX(0.0), offsetY(0.0) {
	
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	
	[[UIApplication sharedApplication] setStatusBarHidden:YES animated:NO];
	
	if(iPhoneOrientation == landscapeLeft){
		[[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeLeft animated:NO];
	}
	else if(iPhoneOrientation == landscapeRight){
		[[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight animated:NO];
	}
	else{
		[[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationPortrait];
	}
#endif
	
}
void OpenGLCamera::setAngle(int angle){
	this->angle = angle;
}

int OpenGLCamera::getAngle(){
	return angle;
}

IPhoneOrientationEnum OpenGLCamera::getOrientation(){
	return iPhoneOrientation;
}


void OpenGLCamera::setOrientation(IPhoneOrientationEnum orientation){
	iPhoneOrientation = orientation;
	
	
	
	
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	
	if(iPhoneOrientation == landscapeLeft){
		[[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeLeft animated:NO];
	}
	else if(iPhoneOrientation == landscapeRight){
		[[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight animated:NO];
	}
	else if(iPhoneOrientation == portrait) {
		[[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationPortrait];
	}
	
#else
	int tempWidth = screenWidth; 
	screenWidth = screenHeight;
	screenHeight = tempWidth;	
#endif
	
	initialized = false;
	
}

void OpenGLCamera::setPosition(double x, double y){
	this->x = x;
	this->y = y;
}
void OpenGLCamera::zoom(double factor){
	zoomFactor=factor;
}
void OpenGLCamera::render(){
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
    glClear( GL_COLOR_BUFFER_BIT);
	
	
	
	if(!initialized){
		
		
		glViewport(0,0,screenWidth, screenHeight);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		GLint   viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
		//glOrthof(-screenWidth/2, screenWidth/2, -screenHeight/2, screenHeight/2, -1, 1);
		glOrthof(-viewport[2]/2, viewport[2]/2, -viewport[3]/2, viewport[3]/2, -1, 1);
#else
		//glOrtho(-screenWidth/2, screenWidth/2, -screenHeight/2, screenHeight/2, -1, 1);
		glOrtho(-viewport[2]/2, viewport[2]/2, -viewport[3]/2, viewport[3]/2, -1, 1);
#endif
		
		

		
		
		initialized=true;
		
		
	}
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	if (iPhoneOrientation == landscapeLeft) {
		glRotatef(90, 0, 0, 1);
	} else if (iPhoneOrientation == landscapeRight) {
		glRotatef(-90, 0, 0, 1);
	}
#endif
	glRotatef(angle, 0, 0, 1);
	
	
	glTranslatef(-x + offsetX, -y + offsetY, 0);
	
	
	glScalef(zoomFactor, zoomFactor, 1);
}

double OpenGLCamera::getZoomFactor() const {
	return zoomFactor;
}

double OpenGLCamera::getScreenWidth() const {
	return screenWidth;
}

double OpenGLCamera::getScreenHeight() const {
	return screenHeight;
}

double  OpenGLCamera::getXPosition() const {
	return x;
}
double OpenGLCamera::getYPosition() const {
	return y;
}

double OpenGLCamera::getOffsetX() const {
	return offsetX;
}

double OpenGLCamera::getOffsetY() const {
	return offsetY;
}

void OpenGLCamera::setOffsetX(double newOffsetX) {
	offsetX = newOffsetX;
}

void OpenGLCamera::setOffsetY(double newOffsetY) {
	offsetY	= newOffsetY;
}

