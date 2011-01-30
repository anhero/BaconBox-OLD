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
std::map<std::string, SoundFX*> ResourceLoader::sounds = std::map<std::string, SoundFX*>();
std::map<std::string, BackgroundMusic*> ResourceLoader::musics = std::map<std::string, BackgroundMusic*>();
AudioEngine* ResourceLoader::soundEngine = NULL;
AudioEngine* ResourceLoader::musicEngine = NULL;

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

void ResourceLoader::startAudioEngine() {
	//TODO: Audio engine specific loading.
}

void ResourceLoader::removeSoundFX(const std::string& name) {
	// We check if the sound engine is loaded.
	if(soundEngine) {
		// We find the sound effect.
		std::map<std::string, SoundFX*>::iterator snd = sounds.find(name);
		// We check if the sound effect asked exists.
		if(snd) {
			// We delete it.
			delete (*snd);
			// We remove it from the map.
			sounds.erase(snd);
		}
	}
}

void ResourceLoader::removeBackgroundMusic(const std::string& name) {
	// We check if the music engine is loaded.
	if(musicEngine) {
		// We find the music.
		std::map<std::string, BackgroundMusic*>::iterator music = musics.find(name);
		// We check if the music asked exists.
		if(music) {
			// We delete it.
			delete (*music);
			// We remove it from the map.
			musics.erase(music);
		}
	}
}