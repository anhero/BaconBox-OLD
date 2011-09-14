/**
 * @file
 * @ingroup Display
 */
#ifndef RB_TEXTURE_INFO_H
#define RB_TEXTURE_INFO_H

#include <iostream>

#include "PlatformFlagger.h"

#include "RBOpenGL.h"
#include "ColorFormat.h"

namespace RedBox {
	/**
	 * Struct containing information about a texture. Will contain different
	 * informations depending on the platform.
	 * @ingroup Display
	 */
	struct TextureInfo {
		/**
		 * Outputs the TextureInfo's content.
		 * @param output The ostream in which TextureInfo is output.
		 * @param t TextureInfo to output in the ostream.
		 * @return Resulting ostream.
		 */
		friend std::ostream &operator<<(std::ostream &output,
		                                const TextureInfo &t);

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
#else
		TextureInfo(unsigned int newImageWidth,
		            unsigned int newImageHeight);
#endif

		/// Color format of the texture
		ColorFormat colorFormat;

		/// Texture width powered to 2
		unsigned int poweredWidth;

		/// Texure height powered to 2
		unsigned int poweredHeight;

		/// Texture's image width.
		unsigned int imageWidth;

		/// Texture's image height.
		unsigned int imageHeight;
	};
}
#endif
