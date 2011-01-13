/**
 * @file
 * @ingroup Drawer
 */


#ifndef OPENGLDRAWER
#define OPENGLDRAWER


#include "PlatformFlager.h"

#ifdef RB_IPHONE_PLATFORM
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#endif

namespace RedBox{
    /** 
     * @class OpenGLDrawer
     * @ingroup Drawer
     *  OpenGl graphic backend 
     */
	class OpenGLDrawer {
	private:
	public:
        /**
         * Draw a colored and textured shape 
         * with the given vertices, texture coordinate, color information and texture ID
         * color information will blend with the textured (and background if alpha is not at max value of 255)
         *
         * @param vertexArray Array of vertex to draw, must have this form (X1, Y1, X2, Y2, Xn, Yn).
         * The order must be clock wise
         * @param textCoordArray Array of texture coordinate, every value must be in the range 0 to 1. 
         * @param colorArray Array of colors. Must have this form (R1, G1, B1, A1, Rn, Gn, Bn, An). Value must be between 0 and 255.
         * @param textureID OpenGL texture handle.
         */
		static void drawShapeWithTextureAndColor(GLfloat * vertexArray, GLfloat * textCoordArray, GLubyte * colorArray, GLuint textureID, int numberOfVertex);
        
        /**
         * Draw a textured shape 
         * with the given vertices, texture coordinate and texture ID
         *
         * @param vertexArray Array of vertex to draw, must have this form (X1, Y1, X2, Y2, Xn, Yn).
         * The order must be clock wise
         * @param textCoordArray Array of texture coordinate, every value must be in the range 0 to 1. 
         * @param textureID OpenGL texture handle.
         */
		static void drawShapeWithTexture(GLfloat * vertexArray, GLfloat * textCoordArray, GLuint textureID, int numberOfVertex);

	};	

}

#endif

/** @} */