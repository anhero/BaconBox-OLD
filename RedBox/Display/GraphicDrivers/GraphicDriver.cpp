#include "Drawer.h"

#include "RenderInfo.h"
#ifdef RB_OPENGL
#include "OpenGLDrawer.h"
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


void GraphicDriver::prepareScene(int xTranslation, int yTranslation, int angle, float zoom){

#ifdef RB_OPENGL
	OpenGLDriver::prepareScene(xTranslation, yTranslation, angle, zoom);
#endif

}


void GraphicDriver::initializeDriver(int screenWidth, int screenHeight) {
#ifdef RB_OPENGL
	OpenGLDriver::initializeDriver(screenWidth, screenHeight);
#endif
}


TextureInfo * loadTexture(unsigned Byte * pixMap, int width, int height){
#ifdef RB_OPENGL
	return OpenGLDriver::loadTexture(buffer, width, height);
#endif
}
