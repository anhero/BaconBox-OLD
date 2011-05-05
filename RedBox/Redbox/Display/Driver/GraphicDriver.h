/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef RB_GRAPHICDRIVER_H
#define RB_GRAPHICDRIVER_H

#include <vector>
#include "TextureInfo.h"
#include "PixMap.h"
#include "Color.h"
#include "Vec2.h"

namespace RedBox{
	class RenderInfo;
    /**
     * Graphic abstraction layer.
	 * A driver must handle rendering and loading (into graphic memory) of bitmap data.
     * @class GraphicDriver
     * @ingroup Driver
     */
	class GraphicDriver {
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
		static void drawShapeWithTextureAndColor(std::vector<float>& vertices, 
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
		static void drawShapeWithTexture(std::vector<float>& vertices,
										 RenderInfo& renderingInfo,
										 unsigned int nbVertices);
		/**
		 * Draws a colored shape.
		 * @param vertices Vertices' coordinates forming the shape to draw.
		 * @param renderingInfo Contains general and platform-specific
		 * information about how to render the shape.
		 * @param nbVertices Number of vertices the shape has.
		 */
		static void drawShapeWithColor(std::vector<float>& vertices,
									   RenderInfo& renderingInfo,
									   unsigned int nbVertices);
		
		/**
		 * Prepare the scene before rendering object.
		 * It clear the draw buffer and reset the transformation matrix with the given
		 * parameters.
		 * @param position Shift the matrix using this 2D vector.
		 * @param angle Apply a rotation to the matrix in degree.
		 * @param zoom Apply a scale factor to the matrix. 1 is unchanged, less than 1 zoom out,
		 * more than 1 zoom in.
		 * @param backgroundColor The scene's background color.
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
		
		static void pushMatrix();
		static void translate(const Vec2& translation);
		static void popMatrix();
		
		/**
		 * Load a texture into graphic memory.
		 * @param pixMap A pixmap object containing the buffer the driver must load.
		 */
		static TextureInfo * loadTexture(PixMap * pixMap);
	};
	
}

#endif
