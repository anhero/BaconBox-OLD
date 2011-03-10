#include "ResourceManager.h"

#ifdef RB_OPENGL
#ifdef RB_IPHONE_PLATFORM

#endif
#endif

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#include "simple-image.h"
#include <utility>
#include "Debug.h"

using namespace RedBox;

std::map<std::string, TextureInfo*> ResourceManager::textures = std::map<std::string, TextureInfo*>();
std::map<std::string, SoundFX*> ResourceManager::sounds = std::map<std::string, SoundFX*>();
std::map<std::string, BackgroundMusic*> ResourceManager::musics = std::map<std::string, BackgroundMusic*>();
std::map<std::string, Font*> ResourceManager::fonts = std::map<std::string, Font*>();

TextureInfo* ResourceManager::addTexture(const std::string& key, unsigned char * bitmap, int width, int height){
	TextureInfo* texInfo = NULL;
	if (textures.find(key) ==  textures.end()) {
		texInfo = new TextureInfo();
#ifdef RB_OPENGL
		glGenTextures(1, &(texInfo->textureId));
		glBindTexture(GL_TEXTURE_2D, texInfo->textureId);
		
		texInfo->imageWidth = width;
		texInfo->imageHeight = height;
		
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 GL_RGBA,
					 width,
					 height,
					 0,
					 GL_RGBA,
					 GL_UNSIGNED_BYTE,
					 bitmap);
		
		textures.insert(std::pair<std::string, TextureInfo*>(key, texInfo));
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
	}
	else {
		$ECHO("Can't load texture with key: " << key << " texture is already loaded");
	}
	return texInfo;
}


TextureInfo* ResourceManager::loadTexture(const std::string& filePath,
										 const std::string& key,
										 bool overwrite) {
	TextureInfo* texInfo = NULL;
	// We check if there is already a texture with this name.
	if(textures.find(key) != textures.end()) {
		// We check if we overwrite the existing texture or not.
		if(overwrite) {
			// We free the allocated memory.
			texInfo = textures[key];
			if(texInfo) {
				delete texInfo;
			}
			// We load the new texture.
			texInfo = textures[key] = loadTexture(filePath);
			$ECHO("Overwrote the existing texture named " << key << ".");
		} else {
			$ECHO("Can't load texture with key: " << key <<
				  " texture is already loaded");
		}
	} else {
		// We load the new texture and add it to the map.
		texInfo = loadTexture(filePath);
		textures.insert(std::pair<std::string, TextureInfo*>(key, texInfo));
	}
	return texInfo;
}

TextureInfo* ResourceManager::getTexture(const std::string& key){
	return textures[key];
}

SoundFX* ResourceManager::getSoundFX(const std::string& key) {
	std::map<std::string, SoundFX*>::iterator itr = sounds.find(key);
	return (itr != sounds.end())?(itr->second):(NULL);
}

BackgroundMusic* ResourceManager::getBackgroundMusic(const std::string& key) {
	std::map<std::string, BackgroundMusic*>::iterator itr = musics.find(key);
	return (itr != musics.end())?(itr->second):(NULL);
}

SoundFX* ResourceManager::loadSoundFX(const std::string& filePath,
									 const std::string& key,
									 bool overwrite) {
	SoundFX* newSnd = NULL;
	// We make sure the sound engine is loaded and that there already isn't 
	// any sound effect with the same name.
	if(AudioEngine::getSoundEngine()) {
		if(sounds.find(key) != sounds.end()) {
			if(overwrite) {
				// We delete the existing sound effect.
				newSnd = sounds[key];
				if(newSnd) {
					delete newSnd;
				}
				// We load the sound effect and we overwrite the existing sound
				// effect.
				newSnd = sounds[key] = AudioEngine::getSoundEngine()->loadSoundFX(filePath);
				$ECHO("Overwrote the existing sound effect named " << key <<
					  ".");
			} else {
				$ECHO("Couldn't load the sound effect named " << key << 
					  " found at " << filePath <<
					  " because a sound with that name already exists.");
			}
		} else {
			// We load the sound effect.
			newSnd = AudioEngine::getSoundEngine()->loadSoundFX(filePath);
			// If it was loaded correctly.
			if(newSnd) {
				// We insert it into the map of sound effects with its
				// corresponding key.
				sounds.insert(std::pair<std::string, SoundFX*>(key, newSnd));
			}
		}
	} else {
		$ECHO("Couldn't load the sound effect named " << key << " found at " <<
			  filePath << " because the sound engine couldn't be loaded.");
	}
	return newSnd;
}

SoundFX* ResourceManager::loadSoundFX(const SoundInfo& info, bool overwrite) {
	SoundFX* newSnd = NULL;
	// We make sure the sound engine is loaded and that there already isn't 
	// any sound effect with the same name.
	if(AudioEngine::getSoundEngine()) {
		if(sounds.find(info.name) != sounds.end()) {
			if(overwrite) {
				// We delete the existing sound effect.
				newSnd = sounds[info.name];
				if(newSnd) {
					delete newSnd;
				}
				// We load the sound effect and we overwrite the existing sound
				// effect.
				newSnd = sounds[info.name] = AudioEngine::getSoundEngine()->loadSoundFX(info);
				$ECHO("Overwrote the existing sound effect named " <<
					  info.name << ".");
			} else {
				$ECHO("Couldn't load the sound effect named " << info.name << 
					  " because a sound with that name already exists.");
			}
		} else {
			// We load the sound effect.
			newSnd = AudioEngine::getSoundEngine()->loadSoundFX(info);
			// If it was loaded correctly.
			if(newSnd) {
				// We insert it into the map of sound effects with its
				// corresponding key.
				sounds.insert(std::pair<std::string, SoundFX*>(info.name,
															   newSnd));
			}
		}
	} else {
		$ECHO("Couldn't load the sound effect named " << info.name <<
			  " because the sound engine couldn't be loaded.");
	}
	return newSnd;
}

BackgroundMusic* ResourceManager::loadBackgroundMusic(const std::string& filePath,
													 const std::string& key,
													 bool overwrite) {
	BackgroundMusic* newBgm = NULL;
	// We make sure the sound engine is loaded and that there already isn't 
	// any music with the same name.
	if(AudioEngine::getMusicEngine()) {
		if(musics.find(key) != musics.end()) {
			if(overwrite) {
				// We delete the existing music.
				newBgm = musics[key];
				if(newBgm) {
					delete newBgm;
				}
				// We load the music and we overwrite the existing music.
				newBgm = musics[key] = AudioEngine::getMusicEngine()->loadBackgroundMusic(filePath);
				$ECHO("Overwrote the existing music named " << key <<
					  ".");
			} else {
				$ECHO("Couldn't load the music named " << key << 
					  " found at " << filePath <<
					  " because a music with that name already exists.");
			}
		} else {
			// We load the music.
			newBgm = AudioEngine::getMusicEngine()->loadBackgroundMusic(filePath);
			// If it was loaded correctly.
			if(newBgm) {
				// We insert it into the map of musics with its corresponding
				// key.
				musics.insert(std::pair<std::string, BackgroundMusic*>(key, newBgm));
			}
		}
	} else {
		$ECHO("Couldn't load the music named " << key << " found at " <<
			  filePath << " because the sound engine couldn't be loaded.");
	}
	return newBgm;
}

BackgroundMusic* ResourceManager::loadBackgroundMusic(const MusicInfo& info,
													 bool overwrite) {
	BackgroundMusic* newBgm = NULL;
	// We make sure the sound engine is loaded and that there already isn't 
	// any music with the same name.
	if(AudioEngine::getMusicEngine()) {
		if(musics.find(info.name) != musics.end()) {
			if(overwrite) {
				// We delete the existing music.
				newBgm = musics[info.name];
				if(newBgm) {
					delete newBgm;
				}
				// We load the music and we overwrite the existing music.
				newBgm = musics[info.name] =
				AudioEngine::getMusicEngine()->loadBackgroundMusic(info);
				$ECHO("Overwrote the existing music named " << info.name <<
					  ".");
			} else {
				$ECHO("Couldn't load the music named " << info.name << 
					  " because a music with that name already exists.");
			}
		} else {
			// We load the music.
			newBgm = AudioEngine::getMusicEngine()->loadBackgroundMusic(info);
			// If it was loaded correctly.
			if(newBgm) {
				// We insert it into the map of musics with its corresponding
				// key.
				musics.insert(std::pair<std::string, BackgroundMusic*>(info.name, newBgm));
			}
		}
	} else {
		$ECHO("Couldn't load the music named " << info.name <<
			  " because the sound engine couldn't be loaded.");
	}
	return newBgm;
}

void ResourceManager::removeSoundFX(const std::string& name) {
	// We find the sound effect.
	std::map<std::string, SoundFX*>::iterator snd = sounds.find(name);
	// We check if the sound effect asked exists.
	if(snd != sounds.end()) {
		// We delete it.
		delete (snd->second);
		// We remove it from the map.
		sounds.erase(snd);
	} else {
		$ECHO("The sound effect named " << name << " could not be removed because it doesn't exist.");
	}
}

void ResourceManager::removeBackgroundMusic(const std::string& name) {
	// We find the music.
	std::map<std::string, BackgroundMusic*>::iterator music = musics.find(name);
	// We check if the music asked exists.
	if(music != musics.end()) {
		// We delete it.
		delete (music->second);
		// We remove it from the map.
		musics.erase(music);
	} else {
		$ECHO("The music named " << name << " could not be removed because it doesn't exist.");
	}
}

Font* ResourceManager::loadFont(std::string & name, std::string & path){
	
	Font * aFont = new Font(name,path);
	// If there is already a font with the specified name in the map,
	// we delete it before we insert the new one 
	std::map<std::string, Font*>::iterator i = fonts.find(name);
	if (i != fonts.end()){
		delete (*i).second;
		(*i).second = aFont;
	}
	else{
		fonts.insert(std::pair<std::string, Font*>(name, aFont));
	}
	return aFont;
}

Font* ResourceManager::getFont(std::string & name){
	std::map<std::string, Font*>::iterator i = fonts.find(name);
	if (i != fonts.end()){
		return (*i).second;
	}
	else {
		return NULL;
	}
}

void ResourceManager::removeFont(std::string & name){
	std::map<std::string, Font*>::iterator i = fonts.find(name);
	if (i != fonts.end()){
		delete (*i).second;
	}
	fonts.erase(i);
}

void ResourceManager::unloadAll() {
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
	
	// We unload the fonts.
	for(std::map<std::string, Font*>::iterator i = fonts.begin();
		i != fonts.end();
		i++) {
		delete i->second;
	}
	fonts.clear();
}

TextureInfo* ResourceManager::loadTexture(const std::string& filePath) {
	TextureInfo* texInfo = NULL;
#ifdef RB_OPENGL
	texInfo = new TextureInfo();
	glGenTextures(1, &(texInfo->textureId));
	glBindTexture(GL_TEXTURE_2D, texInfo->textureId);
	siTexImagePNG(GL_TEXTURE_2D, GL_RGBA, filePath.c_str(), &(texInfo->imageWidth), &(texInfo->imageHeight));
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
	return texInfo;
}

