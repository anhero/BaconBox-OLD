#include <stdarg.h>
#include <stdio.h>

#include "simple-image.h"
#include "simple-image-debug.h"

static GLboolean siDebugEnabled =
#if defined(NDEBUG)
    GL_FALSE;
#else
    GL_TRUE;
#endif

void siEnableDebug(GLboolean enable)
{
    siDebugEnabled = enable;
}

PRINTF_FORMAT void siDebug(
    const char *format, ...)
{
    if (siDebugEnabled)
    {
        va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
    }
}
