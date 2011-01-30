/**
 * @file
 * @ingroup Display
 */
#ifndef RB_TEXTURE_INFO_H
#define RB_TEXTURE_INFO_H

namespace RedBox {
	/**
	 * Struct containing information about a texture. Will contain different
	 * informations depending on the platform.
	 * @ingroup Display
	 */
	struct TextureInfo {
		/**
		 * Default constructor.
		 */
		TextureInfo();
#ifdef RB_OPENGL
		/**
		 * Parametrized constructor for the OpenGL implementation of 
		 * TextureInfo.
		 * @param newTextureId Texture ID to be used.
		 * @param newImageWidth Image width in pixels to be used.
		 * @param newImageHeight Image height in pixels to be used.
		 */
		TextureInfo(unsigned int newTextureId,
					unsigned int newImageWidth,
					unsigned int newImageHeight);
		/// OpenGL's texture's ID.
		unsigned int textureId;
#endif
		/// Texture's image width.
		unsigned int imageWidth;
		/// Texture's image height.
		unsigned int imageHeight;
	};
}
#endif