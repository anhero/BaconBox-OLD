#include "Drawer.h"

#include "RenderInfo.h"
#ifdef RB_OPENGL
#include "OpenGLDrawer.h"
#endif

using namespace RedBox;

void Drawer::drawShapeWithTextureAndColor(std::vector<float>& vertices,
										  RenderInfo& renderingInfo,
										  unsigned int nbVertices) {
#ifdef RB_OPENGL
	OpenGLDrawer::drawShapeWithTextureAndColor(&(*(vertices.begin())),
												   renderingInfo,
												   nbVertices);
#endif
}

void Drawer::drawShapeWithTexture(std::vector<float>& vertices,
								  RenderInfo& renderingInfo,
								  unsigned int nbVertices) {
#ifdef RB_OPENGL
		OpenGLDrawer::drawShapeWithTexture(&(*(vertices.begin())),
										   renderingInfo,
										   nbVertices);
#endif
}


void Drawer::prepareScene(int xTranslation, int yTranslation, int angle, float zoom){

#ifdef RB_OPENGL
	OpenGLDrawer::prepareScene(xTranslation, yTranslation, angle, zoom);
#endif

}


void Drawer::initializeDrawer(int screenWidth, int screenHeight) {
#ifdef RB_OPENGL
	OpenGLDrawer::initializeDrawer(screenWidth, screenHeight);
#endif
}
