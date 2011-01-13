/*
 *  RBOpenGLDrawer.h
 *  RedboxEngine
 *
 *  Created by Joe Dupuis on 09-10-29.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __OPENGLCAMERA_H
#define __OPENGLCAMERA_H


#ifdef __APPLE__
#include "TargetConditionals.h"

#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#endif

#else

#ifdef _WIN32
#include <windows.h>
#endif //_WIN32

#include <GL/gl.h>
#include <GL/glut.h>
#endif



namespace RedBox{

#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	enum IPhoneOrientationEnum  {
		portrait, landscapeLeft, landscapeRight, defaultOrientation
	};
#endif


class OpenGLCamera {
	
	
private:
	double x,y, offsetX, offsetY;
	int screenWidth, screenHeight;
	IPhoneOrientationEnum iPhoneOrientation;
	double zoomFactor;
	float angle;
	bool initialized;
public:
	OpenGLCamera();
	OpenGLCamera(int screenWidth, int screenHeight, IPhoneOrientationEnum orientation);
	
	IPhoneOrientationEnum getOrientation();
	void setOrientation(IPhoneOrientationEnum orientation);
	void setPosition(double x, double y);
	void setAngle(int angle);
	void setOffsetX(double newOffsetX);
	void setOffsetY(double newOffsetY);
	void zoom(double factor);
	void render();
	int getAngle();
	
	double getZoomFactor() const;
	double getScreenWidth() const;
	double getScreenHeight() const;
	double getXPosition() const;
	double getYPosition() const;
	double getOffsetX() const;
	double getOffsetY() const;
};
}

#endif