#ifndef simple_image_debug_h
#define simple_image_debug_h

#if defined(__GNUC__)
#define PRINTF_FORMAT __attribute__((format (printf, 1, 2)))
#else
#define PRINTF_FORMAT
#endif

extern PRINTF_FORMAT void siDebug(
    const char *format, ...);

#endif
