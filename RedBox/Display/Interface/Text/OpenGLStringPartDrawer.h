
#ifndef __OPENGLSTRINGPARTDRAWER_H
#define __OPENGLSTRINGPARTDRAWER_H
#include "StringPart.h"
#include "PlatformFlager.h"

#ifdef RB_IPHONE_PLATFORM
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#endif

#include "OpenGLTextureHandleCollection.h"
namespace RedBox {
	
	class StringPart;

	class OpenGLStringPartDrawer{
	private:
		GLuint tex;
		static const GLfloat vertexCoordArray[8];
		GLfloat textCoordArray[8];
		StringPart * parentStringPart;
		int textureWidth;
		int textureHeight;
	public:
		OpenGLStringPartDrawer(StringPart * parent);
		void render();
		void setTextureInfo(float minX, float maxX, float minY, float maxY, int imageWidth, int imageHeight);
		void setBitmap(unsigned char * bitmap, const std::string& key);
	};
}
#endif