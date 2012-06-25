/**
 * @file
 * @ingroup Display
 */
#ifndef RB_TEXTURE_INFORMATION_H
#define RB_TEXTURE_INFORMATION_H

#include <iostream>

#include "PlatformFlagger.h"

#include "RBOpenGL.h"
#include "ColorFormat.h"

namespace BaconBox {
	/**
	 * Struct containing information about a texture. Will contain different
	 * informations depending on the platform.
	 * @ingroup Display
	 */
	struct TextureInformation {
		/**
		 * Outputs the Texture's content.
		 * @param output The ostream in which Texture is output.
		 * @param t Texture to output in the ostream.
		 * @return Resulting ostream.
		 */
		friend std::ostream &operator<<(std::ostream &output,
		                                const TextureInformation &t);

		/**
		 * Default constructor.
		 */
		TextureInformation();
#if defined (RB_OPENGL) || defined (RB_OPENGLES)
		/**
		 * Parametrized constructor for the OpenGL implementation of
		 * Texture.
		 * @param newTextureId Texture ID to be used.
		 * @param newImageWidth Image width in pixels to be used.
		 * @param newImageHeight Image height in pixels to be used.
		 */
		TextureInformation(unsigned int newTextureId,
		                   unsigned int newImageWidth,
		                   unsigned int newImageHeight);

		/// OpenGL's texture's ID.
		unsigned int textureId;
#else
		TextureInformation(unsigned int newImageWidth,
		                   unsigned int newImageHeight);
#endif

		/// Color format of the texture
		ColorFormat colorFormat;

		/// Texture width powered to 2
		unsigned int poweredWidth;

		/// Texture height powered to 2
		unsigned int poweredHeight;

		/// Texture's image width.
		unsigned int imageWidth;

		/// Texture's image height.
		unsigned int imageHeight;
	};
}
#endif
