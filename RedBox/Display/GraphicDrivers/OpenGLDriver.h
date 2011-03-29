/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef RB_OPENGLDRIVER
#define RB_OPENGLDRIVER

#include "PlatformFlagger.h"

#if defined(RB_IPHONE_PLATFORM)
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#elif defined(RB_QT)
#include <QtOpenGL>
#endif

#include "GraphicDriver.h"

namespace RedBox {
	class RenderInfo;
    /** 
     * @class OpenGLDriver
     * @ingroup Driver
     *  OpenGl graphic driver. 
     */
	class OpenGLDriver {
		friend GraphicDriver;
	private:
        /**
         * Draw a colored and textured shape 
         * with the given vertices, texture coordinate, rendering informations (colors array and textureID) and
         * number of vertices
         * color information will blend with the textured (and background if alpha is not at max value of 255)
         *
         * @param vertices Array of vertex to draw, must have this form (X1, Y1, X2, Y2, Xn, Yn).
         * The order must be clock wise
         * @param texCoordArray Array of texture coordinate, every value must be in the range 0 to 1. 
         * @param renderingInfo object of type RenderInfo, containing colors array and textureID
         * @param nbVertices number of vertices to draw
         */
		static void drawShapeWithTextureAndColor(GLfloat* vertices,
												 RenderInfo& renderingInfo,
												 unsigned int nbVertices);
        
        /**
         * Draw a textured shape 
         * with the given vertices, texture coordinate, rendering informations (textureID) and
         * the number of vertices
         *
         * @param vertices Array of vertex to draw, must have this form (X1, Y1, X2, Y2, Xn, Yn).
         * The order must be clock wise
         * @param texCoordArray Array of texture coordinate, every value must be in the range 0 to 1.
         * @param renderingInfo object of type RenderInfo, containing colors array and textureID
         * @param nbVertices number of vertices to draw
         */
		static void drawShapeWithTexture(GLfloat* vertices,
										 RenderInfo& renderingInfo,
										 unsigned int nbVertices);
		
		/**
		 * Prepare the scene before rendering object.
		 * It clear the draw buffer and reset the transformation matrix with the given
		 * parameters.
		 * @param xTranslation Shift the matrix on the x axis.
		 * @param yTranslation Shift the matrix on the y axis.
		 * @param angle Apply a rotation to the matrix in degree.
		 * @param Apply a scale factor to the matrix. 1 is unchanged, less than 1 zoom out, 
		 * more than 1 zoom in.
		 */
		static void prepareScene(int xTranslation, int yTranslation, int angle, float zoom);
		
		/**
		 * Initialize the drawing backend an prepare the coordinate system with the given
		 * screen size.
		 * @param screenWidth Width of the screen. A camera with a zoom factor of 1, will
		 * show "screenWidth" pixels in width
		 * @param screenHeight Height of the screen. A camera with a zoom factor of 1, will
		 * show "screenHeight" pixels in height
		 */
		static void initializeGraphicDriver(int screenWidth, int screenHeight);
		
		/**
		 * Load a texture into graphic memory.
		 * @param pixMap A pixmap object containing the buffer the driver must load.
		 */
		static TextureInfo * loadTexture(PixMap * pixMap);

	
	};
}

#endif

