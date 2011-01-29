#include "ResourceLoader.h"

#ifdef RB_OPENGL
#ifdef RB_IPHONE_PLATFORM

#endif
#endif

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#include "simple-image.h"

using namespace RedBox;

std::map<std::string, TextureInfo> ResourceLoader::textures = std::map<std::string, TextureInfo>();


void ResourceLoader::loadTexture(const std::string& filePath, const std::string& key) {
	
	if (textures.find(key) ==  textures.end()) {
//#ifdef RB_OPENGL
		unsigned int texID, imageWidth, imageHeight;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		siTexImagePNG(GL_TEXTURE_2D, GL_RGBA, filePath.c_str(), &imageWidth, &imageHeight);
		textures[key].textureID = texID;
		textures[key].imageWidth = imageWidth;
		textures[key].imageHeight = imageHeight;
//#endif
	}
	else {
		//$ECHO("Can't load texture with key: " << key << " texture is already loaded");
	}

}

TextureInfo ResourceLoader::getTextures(const std::string& key){
	return textures[key];
}