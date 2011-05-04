#ifndef RB_OPENGL_H
#define RB_OPENGL_H

#include "PlatformFlagger.h"

#ifdef RB_OPENGL

#if defined(RB_MAC_PLATFORM) && defined(RB_SDL)
#include <OpenGl/OpenGL.h>
#endif

#if defined(RB_IPHONE_PLATFORM)
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#elif defined(RB_QT)
#include <QtOpenGL>
#elif defined(RB_MAC_PLATFORM)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#endif

#endif
