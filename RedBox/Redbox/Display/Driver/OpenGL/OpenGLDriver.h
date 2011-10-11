/**
 * @file
 * @ingroup GraphicDrivers
 */
#ifndef RB_OPENGLDRIVER
#define RB_OPENGLDRIVER

#include "GraphicDriver.h"
#include "RBOpenGL.h"
#include "Color.h"
#include "Vector2.h"
#include "Graphic.h"
#include "Inanimate.h"

namespace RedBox {
	/**
	 * OpenGl graphic driver.
	 * @ingroup GraphicDrivers
	 */
	class OpenGLDriver : public GraphicDriver {
	public:
		/**
		 * Gets the OpenGL driver instance.
		 * @return Reference to the OpenGL driver singleton.
		 */
		static OpenGLDriver &getInstance();

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
		void drawShapeWithTextureAndColor(const VerticesArray &vertices,
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
		void drawShapeWithTexture(const VerticesArray &vertices,
		                          const TextureInformation *textureInformation,
		                          const TextureCoordinates &textureCoordinates);
		/**
		 * Draws a colored shape.
		 * @param vertices Vertices to draw.
		 * @param color Color to render.
		 */
		void drawShapeWithColor(const VerticesArray &vertices,
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
		void drawMaskShapeWithTextureAndColor(const VerticesArray &vertices,
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
		void drawMaskShapeWithTexture(const VerticesArray &vertices,
		                              const TextureInformation *textureInformation,
		                              const TextureCoordinates &textureCoordinates);

		/**
		 * Draw the giver shape masked by using a blend between the alpha
		 * component of the shape and the inversed alpha component
		 * of the color buffer. So if a mask has been rendered with any
		 * "drawMaskShape..." function, the given shape will apear through
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
		void drawMaskedShapeWithTextureAndColor(const VerticesArray &vertices,
		                                        const TextureInformation *textureInformation,
		                                        const TextureCoordinates &textureCoordinates,
		                                        const Color &color,
		                                        bool invertedMask = false);

		/**
		 * Reset the alpha channel to it's original state after a call
		 * to any "drawMask..." function.
		 * @param vertices Vertices to draw.
		 */
		void unmaskShape(const VerticesArray &vertices);

		void drawBatchWithTextureAndColor(const VerticesArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const std::vector<unsigned short> &indices,
		                                  const std::vector<unsigned char> &colors);

		void drawBatchWithTextureAndColor(const VerticesArray &vertices,
		                                  const TextureInformation *textureInformation,
		                                  const TextureCoordinates &textureCoordinates,
		                                  const std::vector<unsigned short> &indices,
		                                  const std::vector<unsigned char> &colors,
		                                  bool printAlpha);

		void drawBatchWithTexture(const VerticesArray &vertices,
		                          const TextureInformation *textureInformation,
		                          const TextureCoordinates &textureCoordinates,
		                          const std::vector<unsigned short> &indices);

		void drawBatchWithTexture(const VerticesArray &vertices,
		                          const TextureInformation *textureInformation,
		                          const TextureCoordinates &textureCoordinates,
		                          const std::vector<unsigned short> &indices,
		                          bool printAlpha);

		void drawMaskBatchWithTextureAndColor(const VerticesArray &vertices,
		                                      const TextureInformation *textureInformation,
		                                      const TextureCoordinates &textureCoordinates,
		                                      const std::vector<unsigned short> &indices,
		                                      const std::vector<unsigned char> &colors);

		void drawMaskedBatchWithTextureAndColor(const VerticesArray &vertices,
		                                        const TextureInformation *textureInformation,
		                                        const TextureCoordinates &textureCoordinates,
		                                        const std::vector<unsigned short> &indices,
		                                        const std::vector<unsigned char> &colors,
		                                        bool invertedMask);

		void unmaskBatch(const VerticesArray &vertices,
		                 const std::vector<unsigned short> &indices);

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


		void initializeGraphicDriver(float contextWidth,
		                             float contextHeight);

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
		 * Pops the current matrix from the stack.
		 */
		void popMatrix();

		/**
		 * Load a texture into graphic memory.
		 * @param pixMap A pixmap object containing the buffer the driver must load.
		 */
		TextureInformation *loadTexture(PixMap *pixMap);
	private:
		static float clampColorComponent(unsigned short component);

		GLuint maskedTexture;
		GLuint maskedFramebuffer;
		GLuint originalFramebuffer;
		Graphic<Inanimate> *maskedGraphic;
		TextureInformation *maskedTextureInformation;

		/**
		 * Default constructor.
		 */
		OpenGLDriver();

		/**
		 * Destructor.
		 */
		~OpenGLDriver();
	};
}

#endif
