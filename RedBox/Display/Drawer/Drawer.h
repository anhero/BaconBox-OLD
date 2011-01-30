/**
 * @file
 * @ingroup Drawer
 */
#ifndef RB_DRAWER_H
#define RB_DRAWER_H

#include "PlatformFlagger.h"

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
         * @param vertices Array of vertices to draw, must have this form (X1, Y1,
		 * X2, Y2, Xn, Yn). The order must be clockwise
         * @param textCoordArray Array of texture coordinate, every value must be in the range 0 to 1.
         * @param renderingInfo Object of type RenderInfo, containing colors array and textureID
         * @param nbVertices Number equal to the number of vertices to draw
         */
		static void drawShapeWithTextureAndColor(float* vertices, 
												 float* textCoordArray,
												 RenderInfo* renderingInfo,
												 int nbVertices);
        /**
         * Draw a textured shape with the given vertices, texture coordinate,
		 * rendering informations (colors array and textureID) and number of
		 * vertices.
         * @param vertices Array of vertex to draw, must have this form (X1, Y1,
		 * X2, Y2, Xn, Yn). The order must be clockwise.
         * @param textCoordArray Array of texture coordinate, every value must be in the range 0 to 1.
         * @param renderingInfo Object of type RenderInfo, containing colors array and textureID.
         * @param nbVertices Number equal to the number of vertices to draw.
         */
		static void drawShapeWithTexture(float* vertices,
										 float* textCoordArray,
										 RenderInfo* renderingInfo,
										 int nbVertices);
	private:
	};
	
}

#endif
