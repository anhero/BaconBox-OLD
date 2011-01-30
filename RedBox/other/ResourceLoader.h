/**
 * @file
 * @ingroup Display
 */

#ifndef __RESOURCELOADER_H
#define __RESOURCELOADER_H

#include <string>
#include <map>

#include "Debug.h"
#include "TextureInfo.h"

namespace RedBox {
	/**
	 * Class that loads resources like textures and audio.
	 * @ingroup Display
	 */
	class ResourceLoader {
	public:
		/**
		 * Loads a texture from a file and assigns a representative key to it.
		 * @param filePath Path to the file containing the texture.
		 * @param key Key used to identify this new texture.
		 */
		static void loadTexture(const std::string& filePath, const std::string& key);
		/**
		 * Gets the information about the asked texture. Uses the texture's key
		 * to find it.
		 * @param key Key used to identify and find the asked texture.
		 */
		static TextureInfo getTextures(const std::string& key);
	private:
		/// Map associating the textures' keys and their information.
		static std::map<std::string, TextureInfo> textures;
	};
}

#endif