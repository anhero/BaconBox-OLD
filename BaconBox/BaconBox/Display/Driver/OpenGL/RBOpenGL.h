#ifndef RB_OPENGL_H
#define RB_OPENGL_H

#include "BaconBox/PlatformFlagger.h"

#if defined (RB_OPENGL) || defined (RB_OPENGLES)

#if defined(RB_MAC_PLATFORM) && defined(RB_SDL)
#include <OpenGL/OpenGL.h>
#endif

#if defined(RB_IPHONE_PLATFORM)
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#elif defined(RB_QT)
#include <QtOpenGL>
#elif defined(RB_MAC_PLATFORM)
#include <OpenGL/gl.h>
#elif defined(RB_ANDROID)
#include <GLES/gl.h>
#include <GLES/glext.h>
#else
#define GLEW_STATIC
#include "glew.h"
#define RB_GLEW
#endif

#endif

#endif
