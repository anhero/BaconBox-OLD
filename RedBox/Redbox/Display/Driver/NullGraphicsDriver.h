/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef RB_NULLGRAPHICSDRIVER
#define RB_NULLGRAPHICSDRIVER

#include "PlatformFlagger.h"

#include "GraphicDriver.h"

#include "RBOpenGL.h"

#include "Color.h"

namespace RedBox {
	class RenderInfo;
	/**
	 * @class NullGraphicsDriver
	 * @ingroup Driver
	 *  OpenGl graphic driver.
	 */
	class NullGraphicsDriver {
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
		static void drawShapeWithTextureAndColor(float *vertices,
		                                         RenderInfo &renderingInfo,
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
		static void drawShapeWithTexture(float *vertices,
		                                 RenderInfo &renderingInfo,
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
		static void drawShapeWithColor(float *vertices,
		                               RenderInfo &renderingInfo,
		                               unsigned int nbVertices);

		/**
		 * Draw the alpha component of the given vertices and texture to the
		 * alpha component of the frame buffer, so the next call to any
		 * "drawMaskedShape..." functions can use the given mask as it's inversed
		 * alpha value.
		 * @param vertices Array of vertices to draw, must have this form (X1, Y1,
		 * X2, Y2, Xn, Yn). The order must be clock wise
		 * @param renderingInfo Object of type RenderInfo, containing the color
		 * array, texture coordinates and textureID.
		 * @param nbVertices Number of vertices to draw.
		 */
		static void drawMaskShapeWithTexture(GLfloat *vertices,
		                                     RenderInfo &renderingInfo,
		                                     unsigned int nbVertices);

		/**
		 * Reset the alpha channel to it's original state after a call
		 * to any "drawMask..." function.
		 * @param vertices Array of vertices to draw, must have this form (X1, Y1,
		 * X2, Y2, Xn, Yn). The order must be clock wise
		 * @param renderingInfo Object of type RenderInfo, containing the color
		 * array, texture coordinates and textureID.
		 * @param nbVertices Number of vertices to draw.
		 */
		static void unmask(GLfloat *vertices,
		                   RenderInfo &renderingInfo,
		                   unsigned int nbVertices);

		/**
		 * Draw the alpha component of the given vertices and texture to the
		 * alpha component of the frame buffer, so the next call to any
		 * "drawMaskedShape..." functions can use the given mask as it's inversed
		 * alpha value.This version of the function will also use the alpha component of
		 * the shape's color (in addition to the texture alpha component).
		 * @param vertices Array of vertices to draw. They have to be like this:
		 * [x1, y1, x2, y2, x3, y3, ...]. The order must be clockwise.
		 * @param renderingInfo Contains the information about the shape's
		 * color.
		 * @param nbVertices Number of vertices the array contains.
		 */
		static void drawMaskShapeWithTextureAndColor(GLfloat *vertices,
		                                             RenderInfo &renderingInfo,
		                                             unsigned int nbVertices);

		/**
		 * Draw the giver shape masked by using a blend between the alpha
		 * component of the shape and the inversed alpha component
		 * of the color buffer. So if a mask has been rendered with any
		 * "drawMaskShape..." function, the given shape will apear through
		 * the transparent part of the mask.
		 * This version of the function render with a texture and a color.
		 * @param vertices Array of vertices to draw. They have to be like this:
		 * [x1, y1, x2, y2, x3, y3, ...]. The order must be clockwise.
		 * @param renderingInfo Contains the information about the shape's
		 * color.
		 * @param nbVertices Number of vertices the array contains.
		 * @param inversedMask If true, the mask effect will be reversed.
		 */
		static void drawMaskedShapeWithTextureAndColor(GLfloat *vertices,
		                                               RenderInfo &renderingInfo,
		                                               unsigned int nbVertices,
		                                               bool inversedMask = false);
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
		static void prepareScene(int xTranslation, int yTranslation,
		                         int angle, float zoom,
		                         const Color &backgroundColor,
		                         const Vector2 &rotationCenterOffset);

		/**
		 * Pushes the current matrix on the stack.
		 */
		static void pushMatrix();

		/**
		 * Applies a translation on the current matrix.
		 * @param translation 2D translation to apply.
		 */
		static void translate(const Vector2 &translation);

		/**
		 * Pops the current matrix from the stack.
		 */
		static void popMatrix();

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
		static TextureInformation *loadTexture(PixMap *pixMap);
	};
}

#endif

