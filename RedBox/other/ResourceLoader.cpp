#include "ResourceLoader.h"

#ifdef RB_OPENGL
#ifdef RB_IPHONE_PLATFORM

#endif
#endif

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#include "simple-image.h"

using namespace RedBox;

std::map<std::string, TextureInfo*> ResourceLoader::textures = std::map<std::string, TextureInfo*>();
std::map<std::string, SoundFX*> ResourceLoader::sounds = std::map<std::string, SoundFX*>();
std::map<std::string, BackgroundMusic*> ResourceLoader::musics = std::map<std::string, BackgroundMusic*>();

TextureInfo* ResourceLoader::loadTexture(const std::string& filePath, const std::string& key) {
	TextureInfo* texInfo = NULL;
	if (textures.find(key) ==  textures.end()) {
#ifdef RB_OPENGL
		texInfo = new TextureInfo();
		glGenTextures(1, &(texInfo->textureId));
		glBindTexture(GL_TEXTURE_2D, texInfo->textureId);
		siTexImagePNG(GL_TEXTURE_2D, GL_RGBA, filePath.c_str(), &(texInfo->imageWidth), &(texInfo->imageHeight));
		textures.insert(std::pair<std::string, TextureInfo*>(key, texInfo));
#endif
	}
	else {
		//$ECHO("Can't load texture with key: " << key << " texture is already loaded");
	}
	return texInfo;
}

TextureInfo* ResourceLoader::getTexture(const std::string& key){
	return textures[key];
}

SoundFX* ResourceLoader::getSoundFX(const std::string& key) {
	std::map<std::string, SoundFX*>::iterator itr = sounds.find(key);
	return (itr != sounds.end())?(itr->second):(NULL);
}

BackgroundMusic* ResourceLoader::getBackgroundMusic(const std::string& key) {
	std::map<std::string, BackgroundMusic*>::iterator itr = musics.find(key);
	return (itr != musics.end())?(itr->second):(NULL);
}

SoundFX* ResourceLoader::loadSoundFX(const std::string& filePath,
									 const std::string& key) {
	SoundFX* newSnd = NULL;
	// We make sure the sound engine is loaded and that there already isn't 
	// any sound effect with the same name.
	if(AudioEngine::getSoundEngine() && sounds.find(key) == sounds.end()) {
		// We load the sound effect.
		newSnd = AudioEngine::getSoundEngine()->loadSoundFX(filePath);
		// If it was loaded correctly.
		if(newSnd) {
			// We insert it into the map of sound effects with its
			// corresponding key.
			sounds.insert(std::pair<std::string, SoundFX*>(key, newSnd));
		}
	}
	return newSnd;
}

SoundFX* ResourceLoader::loadSoundFX(const SoundInfo& info) {
	SoundFX* newSnd = NULL;
	// We make sure the sound engine is loaded and that there already isn't 
	// any sound effect with the same name.
	if(AudioEngine::getSoundEngine() && sounds.find(info.name) == sounds.end()) {
		// We load the sound effect.
		newSnd = AudioEngine::getSoundEngine()->loadSoundFX(info);
		// If it was loaded correctly.
		if(newSnd) {
			// We insert it into the map of sound effects with its
			// corresponding key.
			sounds.insert(std::pair<std::string, SoundFX*>(info.name, newSnd));
		}
	}
	return newSnd;
}

BackgroundMusic* ResourceLoader::loadBackgroundMusic(const std::string& filePath,
													 const std::string& key) {
	BackgroundMusic* newBgm = NULL;
	// We make sure the music engine is loaded and that there already isn't
	// any music with the same name.
	if(AudioEngine::getMusicEngine() && musics.find(key) == musics.end()) {
		// We load the music.
		newBgm = AudioEngine::getMusicEngine()->loadBackgroundMusic(filePath);
		// If it was successfully loaded.
		if(newBgm) {
			// We insert it into the map of musics with its corresponding key.
			musics.insert(std::pair<std::string, BackgroundMusic*>(key, newBgm));
		}
	}
	return newBgm;
}

BackgroundMusic* ResourceLoader::loadBackgroundMusic(const MusicInfo& info) {
	BackgroundMusic* newBgm = NULL;
	// We make sure the music engine is loaded and that there already isn't
	// any music with the same name.
	if(AudioEngine::getMusicEngine() && musics.find(info.name) == musics.end()) {
		// We load the music.
		newBgm = AudioEngine::getMusicEngine()->loadBackgroundMusic(info);
		// If it was successfully loaded.
		if(newBgm) {
			// We insert it into the map of musics with its corresponding key.
			musics.insert(std::pair<std::string, BackgroundMusic*>(info.name, newBgm));
		}
	}
	return newBgm;
}

void ResourceLoader::removeSoundFX(const std::string& name) {
	// We find the sound effect.
	std::map<std::string, SoundFX*>::iterator snd = sounds.find(name);
	// We check if the sound effect asked exists.
	if(snd != sounds.end()) {
		// We delete it.
		delete (snd->second);
		// We remove it from the map.
		sounds.erase(snd);
	}
}

void ResourceLoader::removeBackgroundMusic(const std::string& name) {
	// We find the music.
	std::map<std::string, BackgroundMusic*>::iterator music = musics.find(name);
	// We check if the music asked exists.
	if(music != musics.end()) {
		// We delete it.
		delete (music->second);
		// We remove it from the map.
		musics.erase(music);
	}
}

void ResourceLoader::unloadAll() {
	// We unload the textures.
	for(std::map<std::string, TextureInfo*>::iterator i = textures.begin();
		i != textures.end();
		i++) {
		delete i->second;
	}
	textures.clear();
	// We unload the sound effects.
	for(std::map<std::string, SoundFX*>::iterator i = sounds.begin();
		i != sounds.end();
		i++) {
		delete i->second;
	}
	sounds.clear();
	// We unload the musics.
	for(std::map<std::string, BackgroundMusic*>::iterator i = musics.begin();
		i != musics.end();
		i++) {
		delete i->second;
	}
	musics.clear();
}
