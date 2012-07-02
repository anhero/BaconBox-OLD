#include "BaconBox/Display/Driver/OpenGL/OpenGLDriver.h"

#include <stdint.h>

#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Display/Window/MainWindow.h"
#include "BaconBox/Display/VertexArray.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/Display/PixMap.h"
#include "BaconBox/Console.h"

#define GET_PTR(vertices) reinterpret_cast<const GLfloat *>(&(*vertices.getBegin()))
#define GET_TEX_PTR(textureCoordinates) reinterpret_cast<const GLfloat *>(&(*textureCoordinates.begin()))
#define GET_PTR_BATCH(vertices, adjustment) reinterpret_cast<const GLfloat *>(&(*(vertices.getBegin() + adjustment)))
#define GET_TEX_PTR_BATCH(textureCoordinates, adjustment) reinterpret_cast<const GLfloat *>(&(*(textureCoordinates.begin() + adjustment)))

namespace BaconBox {
	void OpenGLDriver::drawShapeWithTextureAndColor(const VertexArray &vertices,
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

	void OpenGLDriver::drawShapeWithTexture(const VertexArray &vertices,
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

			glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.getNbVertices());

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);

		}
	}

	void OpenGLDriver::drawShapeWithColor(const VertexArray &vertices,
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

			glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.getNbVertices());

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisable(GL_BLEND);

			glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
			           Color::WHITE.getBlue(), Color::WHITE.getAlpha());
		}
	}

	void OpenGLDriver::drawMaskShapeWithTextureAndColor(const VertexArray &vertices,
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

	void OpenGLDriver::drawMaskShapeWithTexture(const VertexArray &vertices,
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

			glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.getNbVertices());

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
	}

	void OpenGLDriver::drawMaskedShapeWithTextureAndColor(const VertexArray &vertices,
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
					glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE_MINUS_DST_ALPHA, GL_ZERO);
#else
					glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
					glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE_MINUS_DST_ALPHA, GL_ZERO);
#endif

					glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
					           Color::WHITE.getBlue(), Color::WHITE.getAlpha());

					glVertexPointer(2, GL_FLOAT, 0, GET_PTR(vertices));
					glEnableClientState(GL_VERTEX_ARRAY);

					glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.getNbVertices());

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

				glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.getNbVertices());

				// Third render, we must render the color according to the buffer alpha channel,
				glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
				           color.getAlpha());


#ifdef RB_OPENGLES
				glBlendEquationOES(GL_FUNC_ADD_OES);
#else
				glBlendEquation(GL_FUNC_ADD);
#endif
				glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);


				glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.getNbVertices());



				//Fourth render, we must reset the alpha channel and leave the RGB channels unchanged.
				glDisable(GL_TEXTURE_2D);
#ifdef RB_OPENGLES
				glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE, GL_ZERO);
#else
				glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE, GL_ZERO);
#endif
				glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
				           Color::WHITE.getBlue(), Color::WHITE.getAlpha());

				glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.getNbVertices());


				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glDisable(GL_BLEND);
			}
		}
	}

	void OpenGLDriver::unmaskShape(const VertexArray &vertices) {
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



		glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.getNbVertices());

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_BLEND);
	}

	void OpenGLDriver::drawBatchWithTextureAndColor(const VertexArray &vertices,
	                                                const TextureInformation *textureInformation,
	                                                const TextureCoordinates &textureCoordinates,
	                                                const IndiceArray &indices,
	                                                const IndiceArrayList &indiceList,
	                                                const ColorArray &colors) {
		for (IndiceArrayList::const_iterator i = indiceList.begin();
		     i != indiceList.end(); ++i) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4,
			               GL_UNSIGNED_BYTE,
			               0,
			               GET_TEX_PTR_BATCH(colors, i->first));

			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

#ifdef RB_OPENGLES
			glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#else
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#endif

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(2, GL_FLOAT, 0, GET_PTR_BATCH(vertices, i->first));
			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR_BATCH(textureCoordinates, i->first));

			if (i == --indiceList.end()) {
				glDrawElements(GL_TRIANGLE_STRIP, indices.size() - i->second, GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));

			} else {
				glDrawElements(GL_TRIANGLE_STRIP, (++IndiceArrayList::const_iterator(i))->second - i->second, GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
			}

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
		}
	}

	void OpenGLDriver::drawBatchWithTexture(const VertexArray &vertices,
	                                        const TextureInformation *textureInformation,
	                                        const TextureCoordinates &textureCoordinates,
	                                        const IndiceArray &indices,
	                                        const IndiceArrayList &indiceList) {
		for (IndiceArrayList::const_iterator i = indiceList.begin();
		     i != indiceList.end(); ++i) {
			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

#ifdef RB_OPENGLES
			glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#else
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
#endif

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(2, GL_FLOAT, 0, GET_PTR_BATCH(vertices, i->first));
			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR_BATCH(textureCoordinates, i->first));

			if (i == --indiceList.end()) {
				glDrawElements(GL_TRIANGLE_STRIP, indices.size() - i->second, GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));

			} else {
				glDrawElements(GL_TRIANGLE_STRIP, (++IndiceArrayList::const_iterator(i))->second - i->second, GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
			}

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	}

	void OpenGLDriver::drawMaskBatchWithTextureAndColor(const VertexArray &vertices,
	                                                    const TextureInformation *textureInformation,
	                                                    const TextureCoordinates &textureCoordinates,
	                                                    const IndiceArray &indices,
	                                                    const IndiceArrayList &indiceList,
	                                                    const ColorArray &/*colors*/) {
		// TODO: Check if there is a reason we're not using the "colors"
		// parameter.

		for (IndiceArrayList::const_iterator i = indiceList.begin();
		     i != indiceList.end(); ++i) {
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
				glVertexPointer(2, GL_FLOAT, 0, GET_PTR_BATCH(vertices, i->first));
				glEnableClientState(GL_VERTEX_ARRAY);

				glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR_BATCH(textureCoordinates, i->first));
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				if (i == --indiceList.end()) {
					glDrawElements(GL_TRIANGLE_STRIP, indices.size() - i->second, GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));

				} else {
					glDrawElements(GL_TRIANGLE_STRIP, (++IndiceArrayList::const_iterator(i))->second - i->second, GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
				}

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);

				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
			}
		}
	}

	void OpenGLDriver::drawMaskedBatchWithTextureAndColor(const VertexArray &vertices,
	                                                      const TextureInformation *textureInformation,
	                                                      const TextureCoordinates &textureCoordinates,
	                                                      const IndiceArray &indices,
	                                                      const IndiceArrayList &indiceList,
	                                                      const ColorArray &colors,
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

		glColor4ub(0, 0, 0, 0);
		glVertexPointer(2, GL_FLOAT, 0, GET_PTR(maskedGraphic->getVertices()));
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_BLEND);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glPopMatrix();
		glColor4ub(255, 255, 255, 255);
		for (IndiceArrayList::const_iterator i = indiceList.begin();
		     i != indiceList.end(); ++i) {

			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4,
			               GL_UNSIGNED_BYTE,
			               0,
			               GET_TEX_PTR_BATCH(colors, i->first));

			glBindTexture(GL_TEXTURE_2D, textureInformation->textureId);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

#ifdef RB_OPENGLES
			glBlendEquationSeparateOES(GL_FUNC_ADD_OES, GL_MAX_EXT);
			glBlendFuncSeparateOES(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
#else
			glBlendEquationSeparate(GL_FUNC_ADD, GL_MAX);
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
#endif

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(2, GL_FLOAT, 0, GET_PTR_BATCH(vertices, i->first));
			glTexCoordPointer(2, GL_FLOAT, 0, GET_TEX_PTR_BATCH(textureCoordinates, i->first));

			if (i == --indiceList.end()) {
				glDrawElements(GL_TRIANGLE_STRIP, indices.size() - i->second, GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));

			} else {
				glDrawElements(GL_TRIANGLE_STRIP, (++IndiceArrayList::const_iterator(i))->second - i->second, GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
			}

#ifdef RB_OPENGLES
			glBlendEquationOES(GL_FUNC_ADD_OES);
#else
			glBlendEquation(GL_FUNC_ADD);
#endif

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			glDisableClientState(GL_COLOR_ARRAY);
		}

		drawMaskedShapeWithTextureAndColor(maskedGraphic->getVertices(),
		                                   maskedGraphic->getTextureInformation(),
		                                   maskedGraphic->getCurrentTextureCoordinates(),
		                                   maskedGraphic->getColor(),
		                                   invertedMask);

		glPopMatrix();
	}

	void OpenGLDriver::unmaskBatch(const VertexArray &vertices,
	                               const IndiceArray &indices,
	                               const IndiceArrayList &indiceList) {
		glEnable(GL_BLEND);

		for (IndiceArrayList::const_iterator i = indiceList.begin();
		     i != indiceList.end(); ++i) {
			glVertexPointer(2, GL_FLOAT, 0, GET_PTR_BATCH(vertices, i->first));
			glEnableClientState(GL_VERTEX_ARRAY);

#ifdef RB_OPENGLES
			glBlendFuncSeparateOES(GL_ZERO, GL_ONE, GL_ONE, GL_ONE);
#else
			glBlendFuncSeparate(GL_ZERO, GL_ONE, GL_ONE, GL_ONE);
#endif
			glColor4ub(Color::WHITE.getRed(), Color::WHITE.getGreen(),
			           Color::WHITE.getBlue(), Color::WHITE.getAlpha());

			if (i == --indiceList.end()) {
				glDrawElements(GL_TRIANGLE_STRIP, indices.size() - i->second, GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));

			} else {
				glDrawElements(GL_TRIANGLE_STRIP, (++IndiceArrayList::const_iterator(i))->second - i->second, GL_UNSIGNED_SHORT, GET_TEX_PTR_BATCH(indices, i->second));
			}

			glDisableClientState(GL_VERTEX_ARRAY);
		}

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

		switch (MainWindow::getInstance().getOrientation().underlying()) {
		case WindowOrientation::HORIZONTAL_LEFT:
			glRotatef(-90.0f, 0, 0, 1);
			glTranslatef(-static_cast<float>(MainWindow::getInstance().getContextWidth()), 0.0f, 0.0f);
			break;

		case WindowOrientation::HORIZONTAL_RIGHT:
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, -static_cast<float>(MainWindow::getInstance().getContextHeight()), 0.0f);
			break;

		default:
			break;
		}

		glScalef(zoom.x, zoom.y, 1);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-(position.x), -(position.y), 0);

	}

	void OpenGLDriver::initializeGraphicDriver() {
		glShadeModel(GL_FLAT);

		if (MainWindow::getInstance().getOrientation() == WindowOrientation::NORMAL ||
		    MainWindow::getInstance().getOrientation() == WindowOrientation::UPSIDE_DOWN) {
			glViewport(0, 0, static_cast<int>(MainWindow::getInstance().getResolutionWidth()), static_cast<int>(MainWindow::getInstance().getResolutionHeight()));

		} else {
			glViewport(0, 0, static_cast<int>(MainWindow::getInstance().getResolutionHeight()), static_cast<int>(MainWindow::getInstance().getResolutionWidth()));
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float left, right, bottom, top;

		if (MainWindow::getInstance().getOrientation() == WindowOrientation::NORMAL) {
			left = 0.0f;
			right = static_cast<float>(MainWindow::getInstance().getContextWidth());
			bottom = static_cast<float>(MainWindow::getInstance().getContextHeight());
			top = 0.0f;

		} else if (MainWindow::getInstance().getOrientation() == WindowOrientation::UPSIDE_DOWN) {
			left = 0.0f;
			right = static_cast<float>(MainWindow::getInstance().getContextWidth());
			bottom = 0.0f;
			top = static_cast<float>(MainWindow::getInstance().getContextHeight());

		} else if (MainWindow::getInstance().getOrientation() == WindowOrientation::HORIZONTAL_LEFT) {
			left = static_cast<float>(MainWindow::getInstance().getContextHeight());
			right = 0.0f;
			bottom = 0.0f;
			top = static_cast<float>(MainWindow::getInstance().getContextWidth());

		} else if (MainWindow::getInstance().getOrientation() == WindowOrientation::HORIZONTAL_RIGHT) {
			left = static_cast<float>(MainWindow::getInstance().getContextHeight());
			right = 0.0f;
			bottom = 0.0f;
			top = static_cast<float>(MainWindow::getInstance().getContextWidth());
		}

#ifdef RB_OPENGLES
		glOrthof(left, right, bottom, top, -1.0f, 1.0f);
#else
		glOrtho(static_cast<double>(left), static_cast<double>(right), static_cast<double>(bottom), static_cast<double>(top), -1.0, 1.0);
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

		if (maskedTextureInformation) {
			glBindFramebufferOES(GL_FRAMEBUFFER_OES, 0);
			glDeleteFramebuffersOES(1, &maskedFramebuffer);
		}

		glGenFramebuffersOES(1, &maskedFramebuffer);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, maskedFramebuffer);
#else

		if (maskedTextureInformation) {
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
			glDeleteFramebuffersEXT(1, &maskedFramebuffer);
		}

		glGenFramebuffersEXT(1, &maskedFramebuffer);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, maskedFramebuffer);
#endif

		if (maskedTextureInformation) {
			glDeleteTextures(1, &maskedTexture);
		}

		glGenTextures(1, &maskedTexture);
		glBindTexture(GL_TEXTURE_2D, maskedTexture);

		if (maskedTextureInformation) {
			delete maskedTextureInformation;
		}

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


		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (maskedGraphic) {
			delete maskedGraphic;
		}

		maskedGraphic = new Graphic<Inanimate>();
		maskedGraphic->setTextureInformation(maskedTextureInformation);
#ifdef RB_OPENGLES
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, originalFramebuffer);
#else
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, originalFramebuffer);
#endif
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLDriver::pushMatrix() {
		glPushMatrix();
	}

	void OpenGLDriver::translate(const Vector2 &translation) {
		glTranslatef(-translation.x, -translation.y, 0.0f);
	}

	void OpenGLDriver::loadIdentity() {
		glLoadIdentity();
	}

	void OpenGLDriver::popMatrix() {
		glPopMatrix();
	}
    
    
    void OpenGLDriver::deleteTexture(TextureInformation * textureInfo){
        glDeleteTextures(1, &(textureInfo->textureId));
    }

	TextureInformation *OpenGLDriver::loadTexture(PixMap *pixMap) {


		TextureInformation *texInfo = new TextureInformation();
		glGenTextures(1, &(texInfo->textureId));
		glBindTexture(GL_TEXTURE_2D, texInfo->textureId);



		int widthPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getWidth());
		int heightPoweredToTwo = MathHelper::nextPowerOf2(pixMap->getHeight());


		PixMap poweredTo2Pixmap(widthPoweredToTwo, heightPoweredToTwo, pixMap->getColorFormat());
		poweredTo2Pixmap.insertSubPixMap(*pixMap);


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

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
