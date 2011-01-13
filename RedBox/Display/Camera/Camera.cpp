#include "Camera.h"

using namespace RedBox;

Camera::Camera(){
}
Camera::Camera(int screenWidth, int screenHeight, IPhoneOrientationEnum orientation){
	renderingCamera = new OpenGLCamera(screenWidth, screenHeight, orientation);
}


bool Camera::isInViewport(Renderable * aRenderable){	
	//return true;
	// We check if the renderable is in the camera's view.
	//TODO:fix the isInViewPort
	// C'est pas aussi optimisé, mais ça marche bien.
	/*if (aRenderable->getXPosition() + aRenderable->getWidth()*0.5 > renderingCamera->getXPosition() - renderingCamera->getScreenHeight()*0.75 &&
	 aRenderable->getXPosition() - aRenderable->getWidth()*0.5 < renderingCamera->getXPosition() + renderingCamera->getScreenHeight()*0.75 &&
	 aRenderable->getYPosition() + aRenderable->getHeight()*0.5 > renderingCamera->getYPosition() - renderingCamera->getScreenHeight()*0.75 &&
	 aRenderable->getYPosition() - aRenderable->getHeight()*0.5 < renderingCamera->getYPosition() + renderingCamera->getScreenHeight()*0.75) {
	 return true;
	 } else {
	 return false;
	 }*/
	//ça va chier dès qu'on touche à la cam dans le jeu mais c'est moins pire que sans
	/*if (renderingCamera->getAngle() == 0 || renderingCamera->getAngle() == 180){
	 if (aRenderable->getXPosition() + aRenderable->getWidth()*0.5 > renderingCamera->getYPosition() - renderingCamera->getScreenWidth()*0.5 &&
	 aRenderable->getXPosition() - aRenderable->getWidth()*0.5 < renderingCamera->getYPosition() + renderingCamera->getScreenWidth()*0.5 &&
	 aRenderable->getYPosition() + aRenderable->getHeight()*0.5 > renderingCamera->getXPosition() - renderingCamera->getScreenHeight()*0.5 &&
	 aRenderable->getYPosition() - aRenderable->getHeight()*0.5 < renderingCamera->getXPosition() + renderingCamera->getScreenHeight()*0.5) {
	 return true;
	 } else {
	 return false;
	 }
	 }
	 
	 if (aRenderable->getXPosition() + aRenderable->getWidth()*0.5 > renderingCamera->getXPosition() - renderingCamera->getScreenWidth()*0.5 &&
	 aRenderable->getXPosition() - aRenderable->getWidth()*0.5 < renderingCamera->getXPosition() + renderingCamera->getScreenWidth()*0.5 &&
	 aRenderable->getYPosition() + aRenderable->getHeight()*0.5 > renderingCamera->getYPosition() - renderingCamera->getScreenHeight()*0.5 &&
	 aRenderable->getYPosition() - aRenderable->getHeight()*0.5 < renderingCamera->getYPosition() + renderingCamera->getScreenHeight()*0.5) {
	 return true;
	 } else {
	 return false;
	 }*/
	
	double xDistance = aRenderable->getXPosition() - renderingCamera->getXPosition();
	if(xDistance <0) {
		xDistance *= -1;
	}
	
	double yDistance = aRenderable->getYPosition() - renderingCamera->getYPosition();
	if (yDistance<0) {
		yDistance *= -1;
	}
	
	//480?
	//int biggestBetweenHeightOrWidth = (renderingCamera->getScreenWidth() < renderingCamera->getScreenHeight()? 
	//								   renderingCamera->getScreenHeight(): renderingCamera->getScreenWidth());
	
	
	//xDistance -= (biggestBetweenHeightOrWidth/ renderingCamera->GetZoomFactor())/2.0;
	//yDistance -= (biggestBetweenHeightOrWidth/ renderingCamera->GetZoomFactor())/2.0;
	
	xDistance -= aRenderable->getWidth()*0.5;
	yDistance -= aRenderable->getHeight()*0.5;
	
	
	
	return (xDistance <= 300 && yDistance <= 300);
	//return true;
	
}

void Camera::render(){
	renderingCamera->render();
}

void Camera::zoom(double zoomLevel){
	renderingCamera->zoom(zoomLevel);
}

IPhoneOrientationEnum Camera::getIphoneOrientation(){
	return renderingCamera->getOrientation();
}

void Camera::setIphoneOrientation(IPhoneOrientationEnum orientation){
	renderingCamera->setOrientation( orientation);
}

void Camera::setPosition(double x, double y){
	renderingCamera->setPosition(x, y);
}

void Camera::setAngle(int angle){
	renderingCamera->setAngle(angle);
}
int Camera::getAngle(){
	return renderingCamera->getAngle();
}


void Camera::moveX(int displacement){
	move(displacement, 0);
}

void Camera::moveY(int displacement){
	move(0, displacement);
}

void Camera::move(int xDisplacement, int yDisplacement){
	renderingCamera->setPosition(getXPosition()+xDisplacement, getYPosition()+yDisplacement);
}

double  Camera::getXPosition(){
	return renderingCamera->getXPosition();
}

double Camera::getYPosition(){
	return renderingCamera->getYPosition();
}


Position Camera::screenToHUDCoordinate(int x, int y){
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	int resultX, resultY;
	//TODO: get rid of magic numbers
	if (getIphoneOrientation() == portrait) {
		resultX = x -160;
		resultY = y -240;
	}
	else if (getIphoneOrientation() == landscapeLeft){
		resultX = y * -1 + 240;
		resultY = x * -1 + 160;
	}
	else if (getIphoneOrientation() == landscapeRight){
		resultX = y - 240;
		resultY = x - 160;
	}
#endif
	return Position(resultX, resultY);
}

Position Camera::screenToWorldCoordinate(int x, int y){
	int resultX, resultY;
	Position hudPosition = screenToHUDCoordinate(x, y);
	
	if (getIphoneOrientation() == landscapeLeft || getIphoneOrientation() == landscapeRight) {
		if (getAngle() == 0) {
			resultX = hudPosition.x + getXPosition();
			resultY = hudPosition.y + getYPosition();
		}
		else if(getAngle() == -90) {
			resultX = hudPosition.y * -1 + getXPosition();
			resultY = hudPosition.x + getYPosition();
		}
	} else if (getIphoneOrientation() == portrait) {
		resultX = hudPosition.x + getXPosition();
		resultY = (hudPosition.y + getYPosition()) * -1;
	}
	
	return Position(resultX, resultY);
}

int Camera::getScreenWidth() {
	return renderingCamera->getScreenWidth();
}
int Camera::getScreenHeight() {
	return renderingCamera->getScreenHeight();
}

void Camera::setOffsetX(double newOffsetX) {
	renderingCamera->setOffsetX(newOffsetX);
}

void Camera::setOffsetY(double newOffsetY) {
	renderingCamera->setOffsetY(newOffsetY);
}