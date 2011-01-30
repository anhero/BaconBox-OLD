#ifdef RB_OPENGL
#include "OpenGLDrawer.h"
#endif

#include "Drawer.h"

using namespace RedBox;

void Drawer::drawShapeWithTextureAndColor(VerticesGroup* vertices,
										  const RenderInfo& renderingInfo,
										  unsigned int nbVertices) {
#ifdef RB_OPENGL
		OpenGLDrawer::drawShapeWithTextureAndColor(&(*(vertices->getVerticesData().begin())),
												   renderingInfo,
												   nbVertices * 2);
#endif
}

void Drawer::drawShapeWithTexture(VerticesGroup* vertices,
								  const RenderInfo& renderingInfo,
								  unsigned int nbVertices) {
#ifdef RB_OPENGL
		OpenGLDrawer::drawShapeWithTexture(&(*(vertices->getVerticesData().begin())),
										   renderingInfo,
										   nbVertices * 2);
#endif
}
