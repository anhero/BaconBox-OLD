#ifndef __RESOURCELOADER_H
#define __RESOURCELOADER_H

#include "Debug.h"

#ifdef RB_IPHONE_PLATFORM
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#endif

#ifdef RB_OPENGL
	#include "simple-image.h"
#endif

using namespace std;

namespace RedBox{
	
	class ResourceLoader {
	private:
#ifdef RB_OPENGL
		static std::map<std::string, unsigned int> textureHandles;
#endif
	public:
		//Graphic resources
		static void loadTexture(string & filePath, string & key);
#ifdef RB_OPENGL
		static unsigned int getTextureHandle(string & key);
#endif

#ifdef RB_DIRECT3D
		//DIRECT3D FUNCTION HERE
#endif
		

		
	};
}

#endif