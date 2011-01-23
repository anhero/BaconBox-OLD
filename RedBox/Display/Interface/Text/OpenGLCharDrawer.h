/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef __OPENGLDRAWER_H
#define __OPENGLDRAWER_H


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


#include "../externalLib/simple-image/simple-image.h"


#include "OpenGLTextureHandleCollection.h"

namespace RedBox{
	/**
     * @ingroup TextDisplay
     */
	class OpenGLCharDrawer{
	private:
		std::string filename;
		int x;
		int y;
		int width;
		int height;
		int angle;
		GLuint tex;
		static const GLfloat vertexCoordArray[8];
		GLfloat textCoordArray[8];
		bool initialized;
	public:
		OpenGLCharDrawer();
		void render();
		void setPosition(int x, int y);
		void setSize(int width, int height);
		void setAngle(int angle);
		void setFilename(const std::string& path);
		void setTexCoord(float minX, float maxX, float minY, float maxY, int imageWidth, int imageHeight);
		int getHeight();
		int getWidth();
	};
}
#endif