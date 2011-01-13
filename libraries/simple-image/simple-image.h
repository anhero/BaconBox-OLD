#ifndef simple_image_h
#define simple_image_h

#if defined(__APPLE__)
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#else

#ifdef _WIN32
//est-ce nécesaaire?
#include<windows.h>
#endif //_WIN32

#include <GL/gl.h>
#include <GL/glu.h>

#endif


#if defined(__cplusplus)
extern "C" {
#endif
	

	extern GLboolean siTexImagePNG(
								   GLenum target,
								   GLenum internalFormat,
								   const char *path, int* pixelWidth, int* pixelHeight);
	
#if defined(__cplusplus)
}
#endif

#endif
