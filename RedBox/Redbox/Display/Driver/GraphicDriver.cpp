#include "GraphicDriver.h"

#include "PlatformFlagger.h"

#include "RenderInfo.h"

#ifdef RB_OPENGL
#include "OpenGLDriver.h"
#else
#include "NullGraphicsDriver.h"
#endif

using namespace RedBox;

void GraphicDriver::drawShapeWithTextureAndColor(std::vector<Vector2>& vertices,
        RenderInfo& renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawShapeWithTextureAndColor(reinterpret_cast<GLfloat*>(&(*(vertices.begin()))),
	        renderingInfo, vertices.size());
#endif
}

void GraphicDriver::drawShapeWithTexture(std::vector<Vector2>& vertices,
        RenderInfo& renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawShapeWithTexture(reinterpret_cast<GLfloat*>(&(*(vertices.begin()))),
	                                   renderingInfo,
	                                   vertices.size());
#endif
}

void GraphicDriver::drawShapeWithColor(std::vector<Vector2>& vertices,
                                       RedBox::RenderInfo& renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawShapeWithColor(reinterpret_cast<GLfloat*>(&(*(vertices.begin()))),
	                                 renderingInfo, vertices.size());
#endif
}


void GraphicDriver::drawMaskShapeWithTexture(std::vector<Vector2>& vertices,
        RedBox::RenderInfo& renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawMaskShapeWithTexture(reinterpret_cast<GLfloat*>(&(*(vertices.begin()))),
	                                       renderingInfo, vertices.size());
#endif
}

void GraphicDriver::unmask(std::vector<Vector2>& vertices,
                           RedBox::RenderInfo& renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::unmask(reinterpret_cast<GLfloat*>(&(*(vertices.begin()))),
	                     renderingInfo, vertices.size());
#endif
}

void GraphicDriver::drawMaskShapeWithTextureAndColor(std::vector<Vector2>& vertices,
        RedBox::RenderInfo& renderingInfo) {
#ifdef RB_OPENGL
	OpenGLDriver::drawMaskShapeWithTextureAndColor(reinterpret_cast<GLfloat*>(&(*(vertices.begin()))),
	        renderingInfo, vertices.size());
#endif
}


void GraphicDriver::drawMaskedShapeWithTextureAndColor(std::vector<Vector2>& vertices,
        RenderInfo& renderingInfo,
        bool inversedMask) {
#ifdef RB_OPENGL
	OpenGLDriver::drawMaskedShapeWithTextureAndColor(reinterpret_cast<GLfloat*>(&(*(vertices.begin()))),
	        renderingInfo, vertices.size(), inversedMask);
#endif
}

void GraphicDriver::prepareScene(const Vector2& position, float angle, float zoom,
                                 const Color& backgroundColor,
                                 const Vector2& rotationCenterOffset) {

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

void GraphicDriver::translate(const Vector2& translation) {
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


TextureInfo* GraphicDriver::loadTexture(PixMap* pixMap) {
#ifdef RB_OPENGL
	return OpenGLDriver::loadTexture(pixMap);
#endif
}
