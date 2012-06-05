/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef RB_NULL_GRAPHIC_DRIVER_H
#define RB_NULL_GRAPHIC_DRIVER_H

#include "GraphicDriver.h"

namespace RedBox {
	/**
	 * Null graphic driver.
	 * @ingroup GraphicDrivers
	 */
	class NullGraphicDriver : public GraphicDriver {
	public:
		/**
		 * Gets the null graphic driver instance.
		 * @return Reference to the null graphic driver singleton.
		 */
		static NullGraphicDriver &getInstance();

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
		void drawShapeWithTextureAndColor(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const Color &color);

		/**
		 * Draw a textured shape with the given vertices, texture coordinate,
		 * rendering informations (colors array and textureID) and number of
		 * vertices.
		 * @param vertices Vertices to draw.
		 * @param textureInformation Pointer to the texture information.
		 * @param textureCoordinates Texture coordinates in the texture to
		 * draw.
		 */
		void drawShapeWithTexture(const VertexArray &vertices,
		                          const TextureInformation *textureInformation,
		                          const TextureCoordinates &textureCoordinates);

		/**
		 * Draws a colored shape.
		 * @param vertices Vertices to draw.
		 * @param color Color to render.
		 */
		void drawShapeWithColor(const VertexArray &vertices,
		                        const Color &color);

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
		void drawMaskShapeWithTextureAndColor(const VertexArray &vertices,
		                                      const TextureInformation *textureInformation,
		                                      const TextureCoordinates &textureCoordinates,
		                                      const Color &color);

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
		void drawMaskShapeWithTexture(const VertexArray &vertices,
		                              const TextureInformation *textureInformation,
		                              const TextureCoordinates &textureCoordinates);

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
		void drawMaskedShapeWithTextureAndColor(const VertexArray &vertices,
		                                        const TextureInformation *textureInformation,
		                                        const TextureCoordinates &textureCoordinates,
		                                        const Color &color,
		                                        bool invertedMask = false);

		/**
		 * Reset the alpha channel to it's original state after a call
		 * to any "drawMask..." function.
		 * @param vertices Vertices to draw.
		 */
		void unmaskShape(const VertexArray &vertices);

		void drawBatchWithTextureAndColor(const VertexArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const IndiceArray &indices,
		                                  const IndiceArrayList &indiceList,
		                                  const ColorArray &colors);

		void drawBatchWithTexture(const VertexArray &vertices,
		                          const TextureInformation *textureInformation,
		                          const TextureCoordinates &textureCoordinates,
		                          const IndiceArray &indices,
		                          const IndiceArrayList &indiceList);

		void drawMaskBatchWithTextureAndColor(const VertexArray &vertices,
		                                      const TextureInformation *textureInformation,
		                                      const TextureCoordinates &textureCoordinates,
		                                      const IndiceArray &indices,
		                                      const IndiceArrayList &indiceList,
		                                      const ColorArray &colors);

		void drawMaskedBatchWithTextureAndColor(const VertexArray &vertices,
		                                        const TextureInformation *textureInformation,
		                                        const TextureCoordinates &textureCoordinates,
		                                        const IndiceArray &indices,
		                                        const IndiceArrayList &indiceList,
		                                        const ColorArray &colors,
		                                        bool invertedMask);

		void unmaskBatch(const VertexArray &vertices,
		                 const IndiceArray &indices,
		                 const IndiceArrayList &indiceList);

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
		void prepareScene(const Vector2 &position, float angle,
		                  const Vector2 &zoom, const Color &backgroundColor);


		void initializeGraphicDriver();

		/**
		 * Pushes the current matrix on the stack.
		 */
		void pushMatrix();

		/**
		 * Applies a translation on the current matrix.
		 * @param translation 2D translation to apply.
		 */
		void translate(const Vector2 &translation);

		/**
		 * Loads the identity matrix as the current matrix.
		 */
		void loadIdentity();

		/**
		 * Pops the current matrix from the stack.
		 */
		void popMatrix();

		/**
		 * Load a texture into graphic memory.
		 * @param pixMap A pixmap object containing the buffer the driver must load.
		 */
		TextureInformation *loadTexture(PixMap *pixMap);
        
        
        /**
         *  Remove a texture from graphic memory
         */
        void deleteTexture(TextureInformation * textureInfo);
        
	private:
		/**
		 * Default constructor.
		 */
		NullGraphicDriver();

		/**
		 * Destructor.
		 */
		~NullGraphicDriver();
	};
}

#endif

