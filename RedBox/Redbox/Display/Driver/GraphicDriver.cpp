#include "GraphicDriver.h"

#include "PlatformFlagger.h"

#include "RenderInfo.h"

#ifdef RB_OPENGL
#include "OpenGLDriver.h"
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

void GraphicDriver::prepareScene(const Vec2& position, float angle, float zoom,
								 const Color& backgroundColor) {

#ifdef RB_OPENGL
	OpenGLDriver::prepareScene(position, angle, zoom, backgroundColor);
#endif

}


void GraphicDriver::initializeGraphicDriver(int screenWidth, int screenHeight) {
#ifdef RB_OPENGL
	OpenGLDriver::initializeGraphicDriver(screenWidth, screenHeight);
#endif
}


TextureInfo * GraphicDriver::loadTexture(PixMap * pixMap){
#ifdef RB_OPENGL
	return OpenGLDriver::loadTexture(pixMap);
#endif
}
