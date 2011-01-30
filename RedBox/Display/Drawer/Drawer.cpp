#ifdef RB_OPENGL
#include "OpenGLDrawer.h"
#endif

#include "Drawer.h"

using namespace RedBox;

void Drawer::drawShapeWithTextureAndColor(float* vertices,
										  float*  textCoordArray,
										  RenderInfo* renderingInfo,
										  int nbVertices) {
#ifdef RB_OPENGL
    OpenGLDrawer::drawShapeWithTextureAndColor(vertices,
											   textCoordArray,
											   renderingInfo,nbVertices);
#endif
}

void Drawer::drawShapeWithTexture(float* vertices, float*  textCoordArray,
								  RenderInfo* renderingInfo, int nbVertices) {
#ifdef RB_OPENGL
    OpenGLDrawer::drawShapeWithTexture(vertices,
									   textCoordArray,
									   renderingInfo,
									   nbVertices);
#endif
}
