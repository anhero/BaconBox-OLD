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
	private:
	};
	
}

#endif
