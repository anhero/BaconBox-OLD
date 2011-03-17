#ifndef simple_image_h
#define simple_image_h

#if defined(__cplusplus)
extern "C" {
#endif
	

	extern GLboolean siTexImagePNG(
								   GLenum target,
								   GLenum internalFormat,
								   const char *path, unsigned int* pixelWidth, unsigned int* pixelHeight);
	
#if defined(__cplusplus)
}
#endif

#endif
