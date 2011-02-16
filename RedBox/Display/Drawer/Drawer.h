/**
 * @file
 * @ingroup Drawer
 */
#ifndef RB_DRAWER_H
#define RB_DRAWER_H

#include "PlatformFlagger.h"
#include "VerticesGroup.h"

namespace RedBox{
    /**
     * Graphic abstraction layer.
     * @class Drawer
     * @ingroup Drawer
     */
	class Drawer {
	public:
        /**
         * Draw a colored and textured shape with the given vertices, texture 
		 * coordinate, rendering informations (colors array and textureID) and 
		 * number of vertices. Color information will blend with the texture
		 * (and background if alpha is not at max value of 255).
         * @param vertices Vertices to draw.
         * @param textCoordArray Array of texture coordinate, every value must be in the range 0 to 1.
         * @param renderingInfo Object of type RenderInfo, containing colors array and textureID
         * @param nbVertices Number equal to the number of vertices to draw
         */
		static void drawShapeWithTextureAndColor(VerticesGroup* vertices, 
												 RenderInfo& renderingInfo,
												 unsigned int nbVertices);
        /**
         * Draw a textured shape with the given vertices, texture coordinate,
		 * rendering informations (colors array and textureID) and number of
		 * vertices.
         * @param vertices Vertices to draw.
         * @param textCoordArray Array of texture coordinate, every value must be in the range 0 to 1.
         * @param renderingInfo Object of type RenderInfo, containing colors array and textureID.
         * @param nbVertices Number equal to the number of vertices to draw.
         */
		static void drawShapeWithTexture(VerticesGroup* vertices,
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
		static void initializeDrawer(int screenWidth, int screenHeight);

	private:
	};
	
}

#endif
