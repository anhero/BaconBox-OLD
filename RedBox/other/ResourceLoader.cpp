#include "ResourceLoader.h"

std::map<std::string, unsigned int> ResourceLoader::textureHandles = std::map<std::string, unsigned int>();


void ResourceLoader::loadTexture(string & filePath, string & key){
	
	if (textureHandles.find(key) ==  textureHandles.end()) {
#ifdef RB_OPENGL
		unsigned int texID;
		glGenTextures(1, texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		siTexImagePNG(GL_TEXTURE_2D, GL_RGBA, filePath.c_str(), &imageWidth, &imageHeight);
		textureHandles[key] = texID;

#endif
	}
	else {
		$ECHO("Can't load texture with key: " << key << " texture is already loaded");
	}

}

#ifdef RB_OPENGL
unsigned int ResourceLoader::getTextureHandle(string & key){
	return textureHandles[key];
}
#endif