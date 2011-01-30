#ifdef RB_OPENGL
#include "OpenGLDrawer.h"
#endif

#include "Drawer.h"

using namespace RedBox;

void Drawer::drawShapeWithTextureAndColor(VerticesGroup* vertices,
										  float*  textCoordArray,
										  RenderInfo* renderingInfo,
										  unsigned int nbVertices) {
#ifdef RB_OPENGL
	if(vertices && textCoordArray && renderingInfo && nbVertices > 0) {
		OpenGLDrawer::drawShapeWithTextureAndColor(&(vertices->getVerticesData()[0]),
												   textCoordArray,
												   renderingInfo,
												   nbVertices * 2);
	}
#endif
}

void Drawer::drawShapeWithTexture(VerticesGroup* vertices,
								  float*  textCoordArray,
								  RenderInfo* renderingInfo,
								  unsigned int nbVertices) {
#ifdef RB_OPENGL
	if(vertices && textCoordArray && renderingInfo && nbVertices > 0) {
		OpenGLDrawer::drawShapeWithTexture(&(vertices->getVerticesData()[0]),
										   textCoordArray,
										   renderingInfo,
										   nbVertices * 2);
	}
#endif
}
