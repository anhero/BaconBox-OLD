#include "GraphicDriver.h"

#include "PlatformFlagger.h"

#include "RenderInfo.h"

#ifdef RB_OPENGL
#include "OpenGLDriver.h"
#else
#include "NullGraphicsDriver.h"
#endif

using namespace RedBox;

void GraphicDriver::drawShapeWithTextureAndColor(std::vector<float>& vertices,
										  RenderInfo& renderingInfo,
										  unsigned int nbVertices) {
#ifdef RB_OPENGL
	OpenGLDriver::drawShapeWithTextureAndColor(&(*(vertices.begin())),
												   renderingInfo,
												   nbVertices);
#endif
}

void GraphicDriver::drawShapeWithTexture(std::vector<float>& vertices,
								  RenderInfo& renderingInfo,
								  unsigned int nbVertices) {
#ifdef RB_OPENGL
		OpenGLDriver::drawShapeWithTexture(&(*(vertices.begin())),
										   renderingInfo,
										   nbVertices);
#endif
}

void GraphicDriver::drawShapeWithColor(std::vector<float>& vertices,
									   RedBox::RenderInfo &renderingInfo,
									   unsigned int nbVertices) {
#ifdef RB_OPENGL
	OpenGLDriver::drawShapeWithColor(&(*(vertices.begin())), renderingInfo,
									 nbVertices);
#endif
}


void GraphicDriver::drawMaskShapeWithTexture(std::vector<float>& vertices,
									   RedBox::RenderInfo &renderingInfo,
									   unsigned int nbVertices) {
#ifdef RB_OPENGL
	OpenGLDriver::drawMaskShapeWithTexture(&(*(vertices.begin())), renderingInfo,
									 nbVertices);
#endif
}

void GraphicDriver::unmask(std::vector<float>& vertices,
                                             RedBox::RenderInfo &renderingInfo,
                                             unsigned int nbVertices) {
#ifdef RB_OPENGL
	OpenGLDriver::unmask(&(*(vertices.begin())), renderingInfo,
                                           nbVertices);
#endif
}

void GraphicDriver::drawMaskShapeWithTextureAndColor(std::vector<float>& vertices,
                           RedBox::RenderInfo &renderingInfo,
                           unsigned int nbVertices) {
#ifdef RB_OPENGL
	OpenGLDriver::drawMaskShapeWithTextureAndColor(&(*(vertices.begin())), renderingInfo,
                         nbVertices);
#endif
}


void GraphicDriver::drawMaskedShapeWithTextureAndColor(std::vector<float>& vertices,
                                                       RenderInfo& renderingInfo,
                                                       unsigned int nbVertices, 
                                                       bool inversedMask) {
#ifdef RB_OPENGL
	OpenGLDriver::drawMaskedShapeWithTextureAndColor(&(*(vertices.begin())), renderingInfo,
                                                   nbVertices, inversedMask);
#endif
}

void GraphicDriver::prepareScene(const Vec2& position, float angle, float zoom,
								 const Color& backgroundColor) {

#ifdef RB_OPENGL
	OpenGLDriver::prepareScene(position, angle, zoom, backgroundColor);
#endif

}

void GraphicDriver::pushMatrix() {
#ifdef RB_OPENGL
	OpenGLDriver::pushMatrix();
#endif
}

void GraphicDriver::translate(const Vec2 &translation) {
#ifdef RB_OPENGL
	OpenGLDriver::translate(translation);
#endif
}

void GraphicDriver::popMatrix() {
#ifdef RB_OPENGL
	OpenGLDriver::popMatrix();
#endif
}

void GraphicDriver::initializeGraphicDriver(unsigned int screenWidth, unsigned int screenHeight) {
#ifdef RB_OPENGL
	OpenGLDriver::initializeGraphicDriver(screenWidth, screenHeight);
#endif
}


TextureInfo * GraphicDriver::loadTexture(PixMap * pixMap){
#ifdef RB_OPENGL
	return OpenGLDriver::loadTexture(pixMap);
#endif
}
