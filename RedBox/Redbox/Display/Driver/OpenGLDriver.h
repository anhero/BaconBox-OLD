/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef RB_OPENGLDRIVER
#define RB_OPENGLDRIVER

#include "PlatformFlagger.h"

#include "GraphicDriver.h"

#include "RBOpenGL.h"

#include "Color.h"
#include "Vec2.h"

namespace RedBox {
	class RenderInfo;
    /** 
     * @class OpenGLDriver
     * @ingroup Driver
     *  OpenGl graphic driver. 
     */
	class OpenGLDriver {
		friend class GraphicDriver;
	private:
        /**
         * Draw a colored and textured shape with the given vertices, texture
		 * coordinate, rendering informations (colors array and textureID) and
         * number of vertices. Color information will blend with the textured
		 * (and background if alpha is not at max value of 255).
         * @param vertices Array of vertex to draw, must have this form (X1, Y1,
		 * X2, Y2, Xn, Yn). The order must be clockwise.
		 * @param renderingInfo Object of type RenderInfo, containing the color
		 * array, texture coordinates and textureID.
         * @param nbVertices Number of vertices to draw.
         */
		static void drawShapeWithTextureAndColor(GLfloat* vertices,
												 RenderInfo& renderingInfo,
												 unsigned int nbVertices);
        
        /**
         * Draw a textured shape with the given vertices, texture coordinate,
		 * rendering informations (textureID) and the number of vertices.
         * @param vertices Array of vertices to draw, must have this form (X1, Y1,
		 * X2, Y2, Xn, Yn). The order must be clock wise
         * @param renderingInfo Object of type RenderInfo, containing the color
		 * array, texture coordinates and textureID.
         * @param nbVertices Number of vertices to draw.
         */
		static void drawShapeWithTexture(GLfloat* vertices,
										 RenderInfo& renderingInfo,
										 unsigned int nbVertices);
		/**
		 * Draw a colored shape with the given vertices and rendering
		 * information.
		 * @param vertices Array of vertices to draw. They have to be like this:
		 * [x1, y1, x2, y2, x3, y3, ...]. The order must be clockwise.
		 * @param renderingInfo Contains the information about the shape's
		 * color.
		 * @param nbVertices Number of vertices the array contains.
		 */
		static void drawShapeWithColor(GLfloat* vertices,
									   RenderInfo& renderingInfo,
									   unsigned int nbVertices);
		
		/**
		 * Prepare the scene before rendering object.
		 * It clear the draw buffer and reset the transformation matrix with the given
		 * parameters.
		 * @param xTranslation Shift the matrix on the x axis.
		 * @param yTranslation Shift the matrix on the y axis.
		 * @param angle Apply a rotation to the matrix in degree.
		 * @param zoom Apply a scale factor to the matrix. 1 is unchanged, less than 1 zoom out,
		 * more than 1 zoom in.
		 * @param backgroundColor Color used for the glClearColor() function
		 * (the scene's background color). The alpha component is ignored.
		 */
		static void prepareScene(const Vec2& position, float angle, float zoom,
								 const Color& backgroundColor);
		
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
	private:
		static float clampColorComponent(unsigned int component);
	};
}

#endif

