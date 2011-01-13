#ifndef __CAMERA_H
#define __CAMERA_H
#include "Renderable.h"
#include "OpenGLCamera.h"
#include "BoundingBox.h"
#include <iostream>
namespace RedBox {
	
class Camera {
private:
	OpenGLCamera* renderingCamera;
	
public:
	Camera();
	Camera(int screenWidth, int screenHeight, IPhoneOrientationEnum orientation);
	bool isInViewport(Renderable * aRenderable);
	void render();
	void setIphoneOrientation(IPhoneOrientationEnum orientation);
	IPhoneOrientationEnum getIphoneOrientation();
	
	void zoom(double zoomLevel);
	
	double getXPosition();
	double getYPosition();
	void setPosition(double x, double y);
	void moveX(int displacement);
	void moveY(int displacement);
	void move(int xDisplacement, int yDisplacement);
	void setAngle(int angle);
	int getAngle();
	void setOffsetX(double newOffsetX);
	void setOffsetY(double newOffsetY);
	
	int getScreenWidth();
	int getScreenHeight();
	Position screenToHUDCoordinate(int x, int y);
	Position screenToWorldCoordinate(int x, int y);
};
	
	
}

#endif