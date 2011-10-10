#include "GraphicDriver.h"

#include "PlatformFlagger.h"

#include "RenderInfo.h"

#ifdef RB_OPENGL
#include "OpenGLDriver.h"
#else
#include "NullGraphicsDriver.h"
#endif

using namespace RedBox;

void GraphicDriver::drawShapeWithTextureAndColor(CArray<Vector2>& vertices,
                                                 RenderInfo &renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawShapeWithTextureAndColor(reinterpret_cast<GLfloat *>(vertices.array),
	                                           renderingInfo, vertices.elementCount);
#endif
}

void GraphicDriver::drawShapeWithTexture(CArray<Vector2>& vertices,
                                         RenderInfo &renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawShapeWithTexture(reinterpret_cast<GLfloat *>(vertices.array),
	                                   renderingInfo,
	                                   vertices.elementCount);
#endif
}

void GraphicDriver::drawShapeWithColor(CArray<Vector2>& vertices,
                                       RedBox::RenderInfo &renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawShapeWithColor(reinterpret_cast<GLfloat *>(vertices.array),
	                                 renderingInfo, vertices.elementCount);
#endif
}

void GraphicDriver::drawMaskBatchWithTextureAndColor(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord,
                                                     const CArray<unsigned short>& indices, const TextureInformation &textureInfo,
                                                     const CArray<unsigned char> & colors) {
#ifdef RB_OPENGL
	OpenGLDriver::drawMaskBatchWithTextureAndColor(vertices, textureCoord, indices, textureInfo, colors);
#endif

}

void GraphicDriver::drawMaskShapeWithTexture(CArray<Vector2>& vertices,
                                             RedBox::RenderInfo &renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawMaskShapeWithTexture(reinterpret_cast<GLfloat *>(vertices.array),
	                                       renderingInfo, vertices.elementCount);
#endif
}
void GraphicDriver::unmaskBatch(const CArray<Vector2>& vertices, const CArray<unsigned short>& indices) {
#ifdef RB_OPENGL
	OpenGLDriver::unmaskBatch(vertices, indices);
#endif
}
void GraphicDriver::unmaskShape(CArray<Vector2>& vertices,
                                RedBox::RenderInfo &renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::unmaskShape(reinterpret_cast<GLfloat *>(vertices.array),
	                          renderingInfo, vertices.elementCount);
#endif
}

void GraphicDriver::drawBatchWithTexture(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord,
                                         const CArray<unsigned short>& indices, const TextureInformation &textureInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawBatchWithTexture(vertices, textureCoord, indices, textureInfo);
#endif

}

void GraphicDriver::drawBatchWithTextureAndColor(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord,
                                                 const CArray<unsigned short>& indices, const TextureInformation &textureInfo, const CArray<unsigned char> & colors) {
#ifdef RB_OPENGL
	OpenGLDriver::drawBatchWithTextureAndColor(vertices, textureCoord, indices, textureInfo, colors);
#endif

}

void GraphicDriver::drawMaskedBatchWithTextureAndColor(const CArray<Vector2>& vertices, const CArray<Vector2>& textureCoord,
                                                       const CArray<unsigned short>& indices, const TextureInformation &textureInfo, const CArray<unsigned char>& colors, bool inversedMask) {

#ifdef RB_OPENGL
	OpenGLDriver::drawMaskedBatchWithTextureAndColor(vertices, textureCoord,
	                                                 indices, textureInfo, colors, inversedMask);
#endif
}

void GraphicDriver::drawMaskShapeWithTextureAndColor(CArray<Vector2>& vertices,
                                                     RedBox::RenderInfo &renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawMaskShapeWithTextureAndColor(reinterpret_cast<GLfloat *>(vertices.array),
	                                               renderingInfo, vertices.elementCount);
#endif
}


void GraphicDriver::drawMaskedShapeWithTextureAndColor(CArray<Vector2>& vertices,
                                                       RenderInfo &renderingInfo,
                                                       bool inversedMask) {
#ifdef RB_OPENGL
	OpenGLDriver::drawMaskedShapeWithTextureAndColor(reinterpret_cast<GLfloat *>(vertices.array),
	                                                 renderingInfo, vertices.elementCount, inversedMask);
#endif
}

void GraphicDriver::prepareScene(const Vector2 &position, float angle, float zoom,
                                 const Color &backgroundColor,
                                 const Vector2 &rotationCenterOffset) {

#ifdef RB_OPENGL
	OpenGLDriver::prepareScene(position, angle, zoom, backgroundColor,
	                           rotationCenterOffset);
#endif

}

void GraphicDriver::pushMatrix() {
#ifdef RB_OPENGL
	OpenGLDriver::pushMatrix();
#endif
}

void GraphicDriver::translate(const Vector2 &translation) {
#ifdef RB_OPENGL
	OpenGLDriver::translate(translation);
#endif
}

void GraphicDriver::popMatrix() {
#ifdef RB_OPENGL
	OpenGLDriver::popMatrix();
#endif
}

void GraphicDriver::initializeGraphicDriver(float contextWidth, float contextHeight) {
#ifdef RB_OPENGL
	OpenGLDriver::initializeGraphicDriver(contextWidth, contextHeight);
#endif
}


TextureInformation *GraphicDriver::loadTexture(PixMap *pixMap) {
#ifdef RB_OPENGL
	return OpenGLDriver::loadTexture(pixMap);
#endif
}
