#include "OpenGLDriver.h"

#include <stdint.h>

#include "PlatformFlagger.h"
#include "TextureInformation.h"
#include "MathHelper.h"
#include "MainWindow.h"
#include "VerticesArray.h"
#include "Color.h"
#include "PixMap.h"

#define GET_PTR(vertices) reinterpret_cast<const GLfloat *>(&(*vertices.getBegin()))
#define GET_TEX_PTR(textureCoordinates) reinterpret_cast<const GLfloat *>(textureCoordinates.data())

namespace RedBox {
	OpenGLDriver &OpenGLDriver::getInstance() {
		static OpenGLDriver instance;
		return instance;
	}

	void OpenGLDriver::drawShapeWithTextureAndColor(const VerticesArray &vertices,
	                                                const TextureInformation *textureInformation,
	                                                const TextureCoordinates &textureCoordinates,
	                                                const Color &color) {
		if (color.getAlpha() > 0u) {
			glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
			           color.getAlpha());

			drawShapeWithTexture(vertices, textureInformation,
			                     textureCoordinates);

			glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
			           Color::WHITE.getBlue(), Color::WHITE.getAlpha());
		}
	}

	void OpenGLDriver::drawShapeWithTexture(const VerticesArray &vertices,
	                                        const TextureInformation *textureInformation,
	                                        const TextureCoordinates &textureCoordinates) {
		// We make sure the texture information is valid.
		if (textureInformation) {
			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
#ifdef RB_OPENGLES
			glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#else
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#endif

			glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
			glEnableClientState(GL_VERTEX_ARRAY);

			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR(textureCoordinates));
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.getNbVertices());

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);

		}
	}

	void OpenGLDriver::drawShapeWithColor(const VerticesArray &vertices,
	                                      const Color &color) {
		if (color.getAlpha() > 0u) {
			glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
			           color.getAlpha());

			glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
			glEnable(GL_BLEND);

#ifdef RB_OPENGLES
			glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#else
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#endif
			glEnableClientState(GL_VERTEX_ARRAY);

			glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.getNbVertices());

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisable(GL_BLEND);

			glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
			           Color::WHITE.getBlue(), Color::WHITE.getAlpha());
		}
	}

	void OpenGLDriver::drawMaskShapeWithTextureAndColor(const VerticesArray &vertices,
	                                                    const TextureInformation *textureInformation,
	                                                    const TextureCoordinates &textureCoordinates,
	                                                    const Color &color) {
		if (color.getAlpha() > 0u) {
			glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
			           color.getAlpha());

			drawMaskShapeWithTexture(vertices, textureInformation,
			                         textureCoordinates);

			glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
			           Color::WHITE.getBlue(), Color::WHITE.getAlpha());
		}
	}

	void OpenGLDriver::drawMaskShapeWithTexture(const VerticesArray &vertices,
	                                            const TextureInformation *textureInformation,
	                                            const TextureCoordinates &textureCoordinates) {
		// We make sure the texture information is valid.
		if (textureInformation) {
			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

#ifdef RB_OPENGLES
			glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ZERO, GL_SRC_ALPHA);
#else
			glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ZERO, GL_SRC_ALPHA);
#endif

			glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
			glEnableClientState(GL_VERTEX_ARRAY);

			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR(textureCoordinates));
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.getNbVertices());

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
	}

	void OpenGLDriver::drawMaskedShapeWithTextureAndColor(const VerticesArray &vertices,
	                                                      const TextureInformation *textureInformation,
	                                                      const TextureCoordinates &textureCoordinates,
	                                                      const Color &color,
	                                                      bool invertedMask) {
		if (color.getAlpha() > 0u) {
			if (textureInformation) {

				glEnable(GL_BLEND);

				if (invertedMask) {
					//First render, if are drawing an invered mask, we must prepare the alpha buffer.
					glDisable(GL_TEXTURE_2D);
#ifdef RB_OPENGLES
					glBlendEquationSeparateOES(GL_FUNC_ADD_OES, GL_FUNC_ADD_OES);
#else
					glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
#endif


#ifdef RB_OPENGLES
					glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE_MINUS_DST_ALPHA, GL_ZERO);
#else
					glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE_MINUS_DST_ALPHA, GL_ZERO);
#endif
					glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
					           Color::WHITE.getBlue(), Color::WHITE.getAlpha());

					glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
					glEnableClientState(GL_VERTEX_ARRAY);

					glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.getNbVertices());

				}

				glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

				glEnable(GL_TEXTURE_2D);
				//Second render (we must use the minimum alpha between the source and destination and let the RGB component unchanged).
#ifdef RB_OPENGLES
				glBlendEquationSeparateOES(GL_FUNC_ADD_OES, GL_MIN_EXT);
#else
				glBlendEquationSeparate(GL_FUNC_ADD, GL_MIN);
#endif
				glBlendFunc(GL_ZERO, GL_ONE);

				glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
				glEnableClientState(GL_VERTEX_ARRAY);

				glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR(textureCoordinates));
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.getNbVertices());

				// Third render, we must render the color according to the buffer alpha channel,
				glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
				           color.getAlpha());


#ifdef RB_OPENGLES
				glBlendEquationOES(GL_FUNC_ADD_OES);
#else
				glBlendEquation(GL_FUNC_ADD);
#endif
				glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);


				glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.getNbVertices());



				//Fourth render, we must reset the alpha channel and leave the RGB channels unchanged.
				glDisable(GL_TEXTURE_2D);
#ifdef RB_OPENGLES
				glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE, GL_ZERO);
#else
				glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE, GL_ZERO);
#endif
				glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
				           Color::WHITE.getBlue(), Color::WHITE.getAlpha());

				glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.getNbVertices());


				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glDisable(GL_BLEND);
			}
		}
	}

	void OpenGLDriver::unmaskShape(const VerticesArray &vertices) {
		glEnable(GL_BLEND);
		glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
		glEnableClientState(GL_VERTEX_ARRAY);

#ifdef RB_OPENGLES
		glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE, GL_ONE);
#else
		glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE, GL_ONE);
#endif
		glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
		           Color::WHITE.getBlue(), Color::WHITE.getAlpha());



		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.getNbVertices());

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_BLEND);
	}

	void OpenGLDriver::drawBatchWithTextureAndColor(const VerticesArray &vertices,
	                                                const TextureInformation *textureInformation,
	                                                const TextureCoordinates &textureCoordinates,
	                                                const std::vector<unsigned short> &indices,
	                                                const std::vector<unsigned char> &colors) {
		drawBatchWithTextureAndColor(vertices, textureInformation, textureCoordinates, indices, colors, false);
	}

	void OpenGLDriver::drawBatchWithTextureAndColor(const VerticesArray &vertices,
	                                                const TextureInformation *textureInformation,
	                                                const TextureCoordinates &textureCoordinates,
	                                                const std::vector<unsigned short> &indices,
	                                                const std::vector<unsigned char> &colors,
	                                                bool printAlpha) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors.data());

		drawBatchWithTexture(vertices, textureInformation, textureCoordinates, indices, printAlpha);

		glDisableClientState(GL_COLOR_ARRAY);
	}

	void OpenGLDriver::drawBatchWithTexture(const VerticesArray &vertices,
	                                        const TextureInformation *textureInformation,
	                                        const TextureCoordinates &textureCoordinates,
	                                        const std::vector<unsigned short> &indices) {
		drawBatchWithTexture(vertices, textureInformation, textureCoordinates, indices, false);
	}

	void OpenGLDriver::drawBatchWithTexture(const VerticesArray &vertices,
	                          const TextureInformation *textureInformation,
	                          const TextureCoordinates &textureCoordinates,
	                          const std::vector<unsigned short> &indices,
	                          bool printAlpha) {
		glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		if (printAlpha) {
#ifdef RB_OPENGLES
			glBlendEquationSeparateOES(GL_FUNC_ADD_OES, GL_MAX_EXT);
			glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
#else
			glBlendEquationSeparate(GL_FUNC_ADD, GL_MAX);
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
#endif

		} else {
#ifdef RB_OPENGLES
			glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#else
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#endif
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
		glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR(textureCoordinates));

		glDrawElements(GL_TRIANGLE_STRIP, indices.size() , GL_UNSIGNED_SHORT, indices.data());

		if (printAlpha) {
#ifdef RB_OPENGLES
			glBlendEquationOES(GL_FUNC_ADD_OES);
#else
			glBlendEquation(GL_FUNC_ADD);
#endif
		}

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void OpenGLDriver::drawMaskBatchWithTextureAndColor(const VerticesArray &vertices,
	                                                    const TextureInformation *textureInformation,
	                                                    const TextureCoordinates &textureCoordinates,
	                                                    const std::vector<unsigned short> &indices,
	                                                    const std::vector<unsigned char> &/*colors*/) {
		// TODO: Check if there is a reason we're not using the "colors"
		// parameter.

		// We make sure the texture information is valid.
		if (textureInformation) {
			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

#ifdef RB_OPENGLES
			glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ZERO, GL_SRC_ALPHA);
#else
			glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ZERO, GL_SRC_ALPHA);
#endif
			glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
			glEnableClientState(GL_VERTEX_ARRAY);

			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR(textureCoordinates));
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, indices.data());


			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
	}

	void OpenGLDriver::drawMaskedBatchWithTextureAndColor(const VerticesArray &vertices,
	                                                      const TextureInformation *textureInformation,
	                                                      const TextureCoordinates &textureCoordinates,
	                                                      const std::vector<unsigned short> &indices,
	                                                      const std::vector<unsigned char> &colors,
	                                                      bool invertedMask) {
#ifdef RB_OPENGLES
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, maskedFramebuffer);
#else
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, maskedFramebuffer);
#endif
#ifdef RB_OPENGLES
		glFramebufferTexture2DOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES,
		                          GL_TEXTURE_2D, maskedTexture, 0);
#else
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
		                          GL_TEXTURE_2D, maskedTexture, 0);
#endif
		glPushMatrix();
		glLoadIdentity();
		//glScalef(3.0f, -3.0f, 1.0f);

		//We can't call glclearcolor on a texture binded framebuffer, so we draw quad to clear the texture
		glColor4ub(0, 0, 0, 255);
		glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
		glEnableClientState(GL_VERTEX_ARRAY);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glPopMatrix();
		drawBatchWithTextureAndColor(vertices, textureInformation, textureCoordinates, indices, colors, true);
#ifdef RB_OPENGLES
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, originalFramebuffer);
#else
		glBindFramebuffer(GL_FRAMEBUFFER, originalFramebuffer);
#endif

		glPushMatrix();
		glLoadIdentity();
		glScalef(1.0f, -1.0f, 1.0f);
		glTranslatef(0.0f, -(MainWindow::getInstance().getContextHeight()), 0.0f);

		drawMaskedShapeWithTextureAndColor(maskedGraphic->getVertices(),
		                                   maskedGraphic->getTextureInformation(),
		                                   maskedGraphic->getCurrentTextureCoordinates(),
		                                   maskedGraphic->getColor(),
		                                   invertedMask);
		glPopMatrix();
	}

	void OpenGLDriver::unmaskBatch(const VerticesArray &vertices,
	                               const std::vector<unsigned short> &indices) {
		glEnable(GL_BLEND);
		glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
		glEnableClientState(GL_VERTEX_ARRAY);

#ifdef RB_OPENGLES
		glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE, GL_ONE);
#else
		glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE, GL_ONE);
#endif
		glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
		           Color::WHITE.getBlue(), Color::WHITE.getAlpha());

		glDrawElements(GL_TRIANGLE_STRIP, indices.size() , GL_UNSIGNED_SHORT, indices.data());

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_BLEND);
	}

	void OpenGLDriver::prepareScene(const Vector2 &position, float angle,
	                                const Vector2 &zoom,
	                                const Color &backgroundColor) {
		glClearColor(clampColorComponent(backgroundColor.getRed()),
		             clampColorComponent(backgroundColor.getGreen()),
		             clampColorComponent(backgroundColor.getBlue()),
		             1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glScalef(zoom.getX(), zoom.getY(), 1);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-(position.getX()), -(position.getY()), 0);

	}

	void OpenGLDriver::initializeGraphicDriver(float contextWidth,
	                                           float contextHeight) {
		glShadeModel(GL_FLAT);

		glViewport(0, 0, static_cast<int>(contextWidth),
		           static_cast<int>(contextHeight));

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

#ifdef RB_OPENGLES
		glOrthof(0.0f, static_cast<float>(contextWidth), static_cast<float>(contextHeight), 0.0f, -1.0f, 1.0f);
#else
		glOrtho(0.0, static_cast<double>(contextWidth), static_cast<double>(contextHeight), 0.0, -1.0, 1.0);
#endif
#if defined(RB_MAC_PLATFORM) && defined(RB_SDL)
		int swapInterval = 1;
		CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
#endif

		//FBO and mask texture initialization
		GLint tempBuffer;
#ifdef RB_OPENGLES
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_OES, &tempBuffer);
#else
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &tempBuffer);
#endif
		originalFramebuffer = static_cast<GLuint>(tempBuffer);
#ifdef RB_OPENGLES
		glGenFramebuffersOES(1, &maskedFramebuffer);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, maskedFramebuffer);
#else
		glGenFramebuffersEXT(1, &maskedFramebuffer);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, maskedFramebuffer);
#endif

		glGenTextures(1, &maskedTexture);
		glBindTexture(GL_TEXTURE_2D, maskedTexture);

		maskedTextureInformation = new TextureInformation();
		maskedTextureInformation->textureId = maskedTexture;
		maskedTextureInformation->imageWidth = MainWindow::getInstance().getResolutionWidth();
		maskedTextureInformation->imageHeight = MainWindow::getInstance().getResolutionHeight();
		maskedTextureInformation->poweredWidth = MathHelper::nextPowerOf2(maskedTextureInformation->imageWidth);
		maskedTextureInformation->poweredHeight = MathHelper::nextPowerOf2(maskedTextureInformation->imageHeight);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		             maskedTextureInformation->poweredWidth,
		             maskedTextureInformation->poweredHeight, 0,
		             GL_RGBA, GL_UNSIGNED_BYTE, NULL);


		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		maskedGraphic = new Graphic<Inanimate>();
		maskedGraphic->setTextureInformation(maskedTextureInformation);
#ifdef RB_OPENGLES
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, originalFramebuffer);
#else
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, originalFramebuffer);
#endif

	}

	void OpenGLDriver::pushMatrix() {
		glPushMatrix();
	}

	void OpenGLDriver::translate(const Vector2 &translation) {
		glTranslatef(-translation.getX(), -translation.getY(), 0.0f);
	}

	void OpenGLDriver::popMatrix() {
		glPopMatrix();
	}

	TextureInformation *OpenGLDriver::loadTexture(PixMap *pixMap) {


		TextureInformation *texInfo = new TextureInformation();
		glGenTextures(1, &(texInfo->textureId));
		glBindTexture(GL_TEXTURE_2D, texInfo->textureId);



		int widthPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getWidth());
		int heightPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getHeight());


		PixMap poweredTo2Pixmap(widthPoweredToTwo, heightPoweredToTwo, pixMap->getColorFormat());
		poweredTo2Pixmap.insertSubPixMap(pixMap);


		texInfo->imageWidth = pixMap->getWidth();
		texInfo->imageHeight = pixMap->getHeight();

		texInfo->poweredWidth = widthPoweredToTwo;
		texInfo->poweredHeight = heightPoweredToTwo;

		GLint format;
		texInfo->colorFormat = pixMap->getColorFormat();

		if (pixMap->getColorFormat() == ColorFormat::RGBA) {
			format = GL_RGBA;

		} else if (pixMap->getColorFormat() == ColorFormat::ALPHA) {
			format = GL_ALPHA;
		}

		glTexImage2D(
		    GL_TEXTURE_2D,
		    0,
		    format,
		    widthPoweredToTwo,
		    heightPoweredToTwo,
		    0,
		    format,
		    GL_UNSIGNED_BYTE,
		    poweredTo2Pixmap.getBuffer());

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		return texInfo;
	}

	float OpenGLDriver::clampColorComponent(unsigned short component) {
		return static_cast<float>(component) / static_cast<float>(Color::MAX_COMPONENT_VALUE);
	}

	OpenGLDriver::OpenGLDriver() : GraphicDriver(), maskedTexture(0),
		maskedFramebuffer(0), originalFramebuffer(0), maskedGraphic(NULL),
		maskedTextureInformation(NULL) {
	}

	OpenGLDriver::~OpenGLDriver() {
		if (maskedGraphic) {
			delete maskedGraphic;
		}

		if (maskedTextureInformation) {
			delete maskedTextureInformation;
		}
	}
}

