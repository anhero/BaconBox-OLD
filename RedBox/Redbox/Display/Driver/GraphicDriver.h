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
#include "Vector2.h"
#include "CArray.h"

namespace RedBox {
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
		 * @param renderingInfo Object of type RenderInfo, containing colors array and textureID
		 * @param nbVertices Number equal to the number of vertices to draw
		 */
		static void drawShapeWithTextureAndColor(CArray<Vector2>& vertices,
		        RenderInfo& renderingInfo);
		/**
		 * Draw a textured shape with the given vertices, texture coordinate,
		 * rendering informations (colors array and textureID) and number of
		 * vertices.
		 * @param vertices Vertices to draw.
		 * @param renderingInfo Object of type RenderInfo, containing colors array and textureID.
		 * @param nbVertices Number equal to the number of vertices to draw.
		 */
		static void drawShapeWithTexture(CArray<Vector2>& vertices,
		                                 RenderInfo& renderingInfo);
		/**
		 * Draws a colored shape.
		 * @param vertices Vertices' coordinates forming the shape to draw.
		 * @param renderingInfo Contains general and platform-specific
		 * information about how to render the shape.
		 * @param nbVertices Number of vertices the shape has.
		 */
		static void drawShapeWithColor(CArray<Vector2>& vertices,
		                               RenderInfo& renderingInfo);

		/**
		 * Draw the alpha component of the given vertices and texture to the
		 * alpha component of the frame buffer, so the next call to any
		 * "drawMaskedShape..." functions can use the given mask as it's inversed
		 * alpha value.
		 * @param vertices Vertices to draw.
		 * @param renderingInfo Object of type RenderInfo, containing colors array and textureID.
		 * @param nbVertices Number equal to the number of vertices to draw.

		 */
		static void drawMaskShapeWithTexture(CArray<Vector2>& vertices,
		                                     RenderInfo& renderingInfo);
        
        static void drawMaskBatchWithTextureAndColor(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord, 
                                                     const CArray<unsigned short>& indices, const TextureInfo & textureInfo, 
                                                     const CArray<unsigned char> & colors);
        
        
        static void drawBatchWithTextureAndColor(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord, 
                                                 const CArray<unsigned short>& indices, const TextureInfo & textureInfo, const CArray<unsigned char> & colors);
        
        
        static void drawBatchWithTexture(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord, 
                                         const CArray<unsigned short>& indices, const TextureInfo & textureInfo);
        
        
        static void drawMaskedBatchWithTextureAndColor(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord, 
                                                       const CArray<unsigned short>& indices, const TextureInfo & textureInfo, const CArray<unsigned char>& colors, bool inversedMask);

		/**
		 * Reset the alpha channel to it's original state after a call
		 * to any "drawMask..." function.
		 * @param vertices Vertices to draw.
		 * @param renderingInfo Object of type RenderInfo, containing colors array and textureID.
		 * @param nbVertices Number equal to the number of vertices to draw.

		 */
		static void unmaskShape(CArray<Vector2>& vertices,
		                   RenderInfo& renderingInfo);

        static void unmaskBatch(const CArray<Vector2>& vertices, const CArray<unsigned short>& indices);
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
		static void drawMaskedShapeWithTextureAndColor(CArray<Vector2>& vertices,
		        RenderInfo& renderingInfo,
		        bool inversedMask = false);

		/**
		 * Draw the alpha component of the given vertices and texture to the
		 * alpha component of the frame buffer, so the next call to any
		 * "drawMaskedShape..." functions can use the given mask as it's inversed
		 * alpha value.This version of the function will also use the alpha component of
		 * the shape's color (in addition to the texture alpha component).
		 * @param vertices Vertices to draw.
		 * @param renderingInfo Object of type RenderInfo, containing colors array and textureID.
		 * @param nbVertices Number equal to the number of vertices to draw.

		 */
		static void drawMaskShapeWithTextureAndColor(CArray<Vector2>& vertices,
		        RenderInfo& renderingInfo);

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
		static void prepareScene(const Vector2& position, float angle, float zoom,
		                         const Color& backgroundColor,
		                         const Vector2& rotationCenterOffset);

	
		static void initializeGraphicDriver(float contextWidth,
		                                    float contextHeight);

		/**
		 * Pushes the current matrix on the stack.
		 */
		static void pushMatrix();

		/**
		 * Applies a translation on the current matrix.
		 * @param translation 2D translation to apply.
		 */
		static void translate(const Vector2& translation);

		/**
		 * Pops the current matrix from the stack.
		 */
		static void popMatrix();

		/**
		 * Load a texture into graphic memory.
		 * @param pixMap A pixmap object containing the buffer the driver must load.
		 */
		static TextureInfo* loadTexture(PixMap* pixMap);
	};

}

#endif
