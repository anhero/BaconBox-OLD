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
	class ResourceLoader {
	public:
		static void loadTexture(const std::string& filePath, const std::string& key);
		static TextureInfo getTextures(const std::string& key);
	private:
		static std::map<std::string, TextureInfo> textures;
	};
}

#endif