/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef RB_GRAPHIC_DRIVER_H
#define RB_GRAPHIC_DRIVER_H

#include "ColorArray.h"
#include "IndiceArray.h"

#include "TextureCoordinates.h"

namespace RedBox {
	class VertexArray;
	struct TextureInformation;
	class Color;
	class PixMap;
	/**
	 * Graphic abstraction layer.
	 * A driver must handle rendering and loading (into graphic memory) of
	 * bitmap data.
	 * @class GraphicDriver
	 * @ingroup Driver
	 */
	class GraphicDriver {
		friend class Engine;
	public:
		/**
		 * Gets the graphic driver instance.
		 * @return Reference to the graphic driver singleton.
		 */
		static GraphicDriver &getInstance();

		/**
		 * Draw a colored and textured shape with the given vertices, texture
		 * coordinate, rendering informations (colors array and texture) and
		 * number of vertices. Color information will blend with the texture
		 * (and background if alpha is not at max value of 255).
		 * @param vertices Vertices to draw.
		 * @param textureInformation Pointer to the texture information.
		 * @param textureCoordinates Texture coordinates in the texture to
		 * draw.
		 * @param color Color to render.
		 */
		virtual void drawShapeWithTextureAndColor(const VertexArray &vertices,
		                                          const TextureInformation *textureInformation,
		                                          const TextureCoordinates &textureCoordinates,
		                                          const Color &color) = 0;

		/**
		 * Draw a textured shape with the given vertices, texture coordinate,
		 * rendering informations (colors array and textureID) and number of
		 * vertices.
		 * @param vertices Vertices to draw.
		 * @param textureInformation Pointer to the texture information.
		 * @param textureCoordinates Texture coordinates in the texture to
		 * draw.
		 */
		virtual void drawShapeWithTexture(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates) = 0;

		/**
		 * Draws a colored shape.
		 * @param vertices Vertices to draw.
		 * @param color Color to render.
		 */
		virtual void drawShapeWithColor(const VertexArray &vertices,
		                                const Color &color) = 0;

		/**
		 * Draws the alpha component of the given vertices and texture to the
		 * alpha component of the frame buffer, so the next call to any
		 * "drawMaskedShape..." functions can use the given mask as its inverted
		 * alpha value. This version of the function will also use the alpha
		 * component of the shape's color (in addition to the texture alpha
		 * component).
		 * @param vertices Vertices to draw.
		 * @param textureInformation Pointer to the texture information.
		 * @param textureCoordinates Texture coordinates in the texture to
		 * draw.
		 * @param color Color to render.
		 */
		virtual void drawMaskShapeWithTextureAndColor(const VertexArray &vertices,
		                                              const TextureInformation *textureInformation,
		                                              const TextureCoordinates &textureCoordinates,
		                                              const Color &color) = 0;

		/**
		 * Draw the alpha component of the given vertices and texture to the
		 * alpha component of the frame buffer, so the next call to any
		 * "drawMaskedShape..." functions can use the given mask as its
		 * inverted alpha value.
		 * @param vertices Vertices to draw.
		 * @param textureInformation Pointer to the texture information.
		 * @param textureCoordinates Texture coordinates in the texture to
		 * draw.
		 */
		virtual void drawMaskShapeWithTexture(const VertexArray &vertices,
		                                      const TextureInformation *textureInformation,
		                                      const TextureCoordinates &textureCoordinates) = 0;

		/**
		 * Draw the giver shape masked by using a blend between the alpha
		 * component of the shape and the inversed alpha component
		 * of the color buffer. So if a mask has been rendered with any
		 * "drawMaskShape..." function, the given shape will appear through
		 * the transparent part of the mask.
		 * This version of the function render with a texture and a color.
		 * @param vertices Array of vertices to draw. They have to be like this:
		 * [x1, y1, x2, y2, x3, y3, ...]. The order must be clockwise.
		 * @param textureInformation Pointer to the texture information.
		 * @param textureCoordinates Texture coordinates in the texture to
		 * draw.
		 * @param color Color to render.
		 * @param invertedMask If true, the mask effect will be inverted.
		 */
		virtual void drawMaskedShapeWithTextureAndColor(const VertexArray &vertices,
		                                                const TextureInformation *textureInformation,
		                                                const TextureCoordinates &textureCoordinates,
		                                                const Color &color,
		                                                bool invertedMask = false) = 0;

		/**
		 * Reset the alpha channel to it's original state after a call
		 * to any "drawMask..." function.
		 * @param vertices Vertices to draw.
		 */
		virtual void unmaskShape(const VertexArray &vertices) = 0;

		virtual void drawBatchWithTextureAndColor(const VertexArray &vertices,
		                                          const TextureInformation *textureInformation,
		                                          const TextureCoordinates &textureCoordinates,
												  const IndiceArray &indices,
												  const IndiceArrayList &indiceList,
												  const ColorArray &colors) = 0;

		virtual void drawBatchWithTexture(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
										  const IndiceArray &indices,
										  const IndiceArrayList &indiceList) = 0;

		virtual void drawMaskBatchWithTextureAndColor(const VertexArray &vertices,
		                                              const TextureInformation *textureInformation,
		                                              const TextureCoordinates &textureCoordinates,
													  const IndiceArray &indices,
													  const IndiceArrayList &indiceList,
		                                              const ColorArray &colors) = 0;

		virtual void drawMaskedBatchWithTextureAndColor(const VertexArray &vertices,
		                                                const TextureInformation *textureInformation,
		                                                const TextureCoordinates &textureCoordinates,
														const IndiceArray &indices,
														const IndiceArrayList &indiceList,
		                                                const ColorArray &colors,
		                                                bool invertedMask) = 0;

		virtual void unmaskBatch(const VertexArray &vertices,
								 const IndiceArray &indices,
								 const IndiceArrayList &indiceList) = 0;

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
		virtual void prepareScene(const Vector2 &position, float angle,
		                          const Vector2 &zoom,
		                          const Color &backgroundColor) = 0;


		virtual void initializeGraphicDriver() = 0;

		/**
		 * Pushes the current matrix on the stack.
		 */
		virtual void pushMatrix() = 0;

		/**
		 * Applies a translation on the current matrix.
		 * @param translation 2D translation to apply.
		 */
		virtual void translate(const Vector2 &translation) = 0;

		/**
		 * Loads the identity matrix as the current matrix.
		 */
		virtual void loadIdentity() = 0;

		/**
		 * Pops the current matrix from the stack.
		 */
		virtual void popMatrix() = 0;

		/**
		 * Load a texture into graphic memory.
		 * @param pixMap A pixmap object containing the buffer the driver must load.
		 */
		virtual TextureInformation *loadTexture(PixMap *pixMap) = 0;
	protected:
		/**
		 * Default constructor.
		 */
		GraphicDriver();

		/**
		 * Destructor.
		 */
		virtual ~GraphicDriver();
	};

}

#endif
