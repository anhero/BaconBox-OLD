#ifdef RB_OPENGL
#include "OpenGLDrawer.h"
#endif

#include "Drawer.h"

using namespace RedBox;

void Drawer::drawShapeWithTextureAndColor(VerticesGroup* vertices,
										  RenderInfo& renderingInfo,
										  unsigned int nbVertices) {
#ifdef RB_OPENGL
		OpenGLDrawer::drawShapeWithTextureAndColor(&(*(vertices->getVerticesData().begin())),
												   renderingInfo,
												   nbVertices);
#endif
}

void Drawer::drawShapeWithTexture(VerticesGroup* vertices,
								  RenderInfo& renderingInfo,
								  unsigned int nbVertices) {
#ifdef RB_OPENGL
		OpenGLDrawer::drawShapeWithTexture(&(*(vertices->getVerticesData().begin())),
										   renderingInfo,
										   nbVertices);
#endif
}
