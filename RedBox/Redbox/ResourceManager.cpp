#include "ResourceManager.h"

#include <utility>
#include "Console.h"
#include "SoundFX.h"
#include "BackgroundMusic.h"
#include "SoundInfo.h"
#include "MusicInfo.h"
#include "TextureInfo.h"
#include "AudioEngine.h"
#include "SoundEngine.h"
#include "MusicEngine.h"
#include "GraphicDriver.h"


//For LibPNG
#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#define PNG_HEADER_SIZE 8

using namespace RedBox;

std::map<std::string, TextureInfo*> ResourceManager::textures = std::map<std::string, TextureInfo*>();
std::map<std::string, SoundInfo*> ResourceManager::sounds = std::map<std::string, SoundInfo*>();
std::map<std::string, MusicInfo*> ResourceManager::musics = std::map<std::string, MusicInfo*>();
std::map<std::string, Font*> ResourceManager::fonts = std::map<std::string, Font*>();

TextureInfo* ResourceManager::addTexture(const std::string& key, PixMap* aPixmap,
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
			texInfo = textures[key] = GraphicDriver::loadTexture(aPixmap);
			Console::print("Overwrote the existing texture named " + key + ".");
		} else {
			Console::print("Can't load texture with key: " + key +
			               " texture is already loaded");
			texInfo = textures[key];
		}
	} else {
		// We load the new texture and add it to the map.
		texInfo = GraphicDriver::loadTexture(aPixmap);
		textures.insert(std::pair<std::string, TextureInfo*>(key, texInfo));
	}

	return texInfo;
}


TextureInfo* ResourceManager::loadTexture(const std::string& key,
        const std::string& filePath,
        bool overwrite) {

	PixMap* aPixMap = loadPixMap(filePath);
	TextureInfo* texInfo = addTexture(key, aPixMap, overwrite);
	delete aPixMap;
	return texInfo;
}






TextureInfo* ResourceManager::getTexture(const std::string& key) {
	return textures[key];
}

SoundInfo* ResourceManager::getSound(const std::string& key) {
	std::map<std::string, SoundInfo*>::iterator itr = sounds.find(key);
	return (itr != sounds.end()) ? (itr->second) : (NULL);
}

MusicInfo* ResourceManager::getMusic(const std::string& key) {
	std::map<std::string, MusicInfo*>::iterator itr = musics.find(key);
	return (itr != musics.end()) ? (itr->second) : (NULL);
}

SoundInfo* ResourceManager::loadSound(const std::string& key,
                                      const std::string& filePath,
                                      bool overwrite) {
	SoundInfo* newSnd = NULL;

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
				newSnd = sounds[key] = AudioEngine::getSoundEngine()->loadSound(filePath);
				Console::print("Overwrote the existing sound effect named " + key +
				               ".");
			} else {
				Console::print("Couldn't load the sound effect named " + key +
				               " found at " + filePath +
				               " because a sound with that name already exists.");
				newSnd = sounds[key];
			}
		} else {
			// We load the sound effect.
			newSnd = AudioEngine::getSoundEngine()->loadSound(filePath);

			// If it was loaded correctly.
			if(newSnd) {
				// We insert it into the map of sound effects with its
				// corresponding key.
				sounds.insert(std::pair<std::string, SoundInfo*>(key, newSnd));
			}
		}
	} else {
		Console::print("Couldn't load the sound effect named " + key + " found at " +
		               filePath + " because the sound engine couldn't be loaded.");
	}

	return newSnd;
}

SoundInfo* ResourceManager::loadSound(const SoundParameters& params,
                                      bool overwrite) {
	SoundInfo* newSnd = NULL;

	// We make sure the sound engine is loaded and that there already isn't
	// any sound effect with the same name.
	if(AudioEngine::getSoundEngine()) {
		if(sounds.find(params.name) != sounds.end()) {
			if(overwrite) {
				// We delete the existing sound effect.
				newSnd = sounds[params.name];

				if(newSnd) {
					delete newSnd;
				}

				// We load the sound effect and we overwrite the existing sound
				// effect.
				newSnd = sounds[params.name] = AudioEngine::getSoundEngine()->loadSound(params);
				Console::print("Overwrote the existing sound effect named " +
				               params.name + ".");
			} else {
				Console::print("Couldn't load the sound effect named " + params.name +
				               " because a sound with that name already exists.");
				newSnd = sounds[params.name];
			}
		} else {
			// We load the sound effect.
			newSnd = AudioEngine::getSoundEngine()->loadSound(params);

			// If it was loaded correctly.
			if(newSnd) {
				// We insert it into the map of sound effects with its
				// corresponding key.
				sounds.insert(std::pair<std::string, SoundInfo*>(params.name,
				              newSnd));
			}
		}
	} else {
		Console::print("Couldn't load the sound effect named " + params.name +
		               " because the sound engine couldn't be loaded.");
	}

	return newSnd;
}

MusicInfo* ResourceManager::loadMusic(const std::string& key,
                                      const std::string& filePath,
                                      bool overwrite) {
	MusicInfo* newBgm = NULL;

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
				newBgm = musics[key] = AudioEngine::getMusicEngine()->loadMusic(filePath);
				Console::print("Overwrote the existing music named " + key +
				               ".");
			} else {
				Console::print("Couldn't load the music named " + key +
				               " found at " + filePath +
				               " because a music with that name already exists.");
				newBgm = musics[key];
			}
		} else {
			// We load the music.
			newBgm = AudioEngine::getMusicEngine()->loadMusic(filePath);

			// If it was loaded correctly.
			if(newBgm) {
				// We insert it into the map of musics with its corresponding
				// key.
				musics.insert(std::pair<std::string, MusicInfo*>(key, newBgm));
			}
		}
	} else {
		Console::print("Couldn't load the music named " + key + " found at " +
		               filePath + " because the sound engine couldn't be loaded.");
	}

	return newBgm;
}

MusicInfo* ResourceManager::loadMusic(const MusicParameters& params,
                                      bool overwrite) {
	MusicInfo* newBgm = NULL;

	// We make sure the sound engine is loaded and that there already isn't
	// any music with the same name.
	if(AudioEngine::getMusicEngine()) {
		if(musics.find(params.name) != musics.end()) {
			if(overwrite) {
				// We delete the existing music.
				newBgm = musics[params.name];

				if(newBgm) {
					delete newBgm;
				}

				// We load the music and we overwrite the existing music.
				newBgm = musics[params.name] = AudioEngine::getMusicEngine()->loadMusic(params);
				Console::print("Overwrote the existing music named " + params.name + ".");
			} else {
				Console::print("Couldn't load the music named " + params.name +
				               " because a music with that name already exists.");
				newBgm = musics[params.name];
			}
		} else {
			// We load the music.
			newBgm = AudioEngine::getMusicEngine()->loadMusic(params);

			// If it was loaded correctly.
			if(newBgm) {
				// We insert it into the map of musics with its corresponding
				// key.
				musics.insert(std::pair<std::string, MusicInfo*>(params.name, newBgm));
			}
		}
	} else {
		Console::print("Couldn't load the music named " + params.name +
		               " because the sound engine couldn't be loaded.");
	}

	return newBgm;
}

void ResourceManager::removeSound(const std::string& key) {
	// We find the sound effect.
	std::map<std::string, SoundInfo*>::iterator snd = sounds.find(key);

	// We check if the sound effect asked exists and we ask the sound engine to
	// unload the data.
	if(snd != sounds.end()) {
		if(AudioEngine::getSoundEngine()->unloadSound(snd->second)) {
			// We delete it.
			delete(snd->second);
			// We remove it from the map.
			sounds.erase(snd);
		} else {
			Console::print("The sound effect named " + key + " could not be removed because the audio engine failed to unload it.");
		}
	} else {
		Console::print("The sound effect named " + key + " could not be removed because it doesn't exist.");
	}
}

void ResourceManager::removeMusic(const std::string& key) {
	// We find the music.
	std::map<std::string, MusicInfo*>::iterator music = musics.find(key);

	// We check if the music asked exists and we ask the music engine to
	// unload the data.
	if(music != musics.end()) {
		if(AudioEngine::getMusicEngine()->unloadMusic(music->second)) {
			// We delete it.
			delete(music->second);
			// We remove it from the map.
			musics.erase(music);
		} else {
			Console::print("The music named " + key + " could not be removed because the audio engine failed to unload it.");
		}
	} else {
		Console::print("The music named " + key + " could not be removed because it doesn't exist.");
	}
}

Font* ResourceManager::loadFont(const std::string& key, const std::string& path, bool overwrite) {
	Font* aFont = NULL;

	// We check if there is already a font with this name.
	if(fonts.find(key) != fonts.end()) {
		// We check if we overwrite the existing font or not.
		if(overwrite) {
			// We free the allocated memory.
			aFont = fonts[key];

			if(aFont) {
				delete aFont;
			}

			// We load the new font.
			aFont = fonts[key] = new Font(key, path);
			Console::print("Overwrote the existing font named " + key + ".");
		} else {
			Console::print("Can't load font with key: " + key +
			               " font is already loaded");
			aFont = fonts[key];
		}
	} else {
		// We load the new texture and add it to the map.
		aFont = new Font(key, path);
		fonts.insert(std::pair<std::string, Font*>(key, aFont));
	}

	return aFont;
}

Font* ResourceManager::getFont(const std::string& key) {
	std::map<std::string, Font*>::iterator i = fonts.find(key);

	if(i != fonts.end()) {
		return (*i).second;
	} else {
		return NULL;
	}
}

void ResourceManager::removeFont(const std::string& key) {
	std::map<std::string, Font*>::iterator i = fonts.find(key);

	if(i != fonts.end()) {
		delete(*i).second;
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
	for(std::map<std::string, SoundInfo*>::iterator i = sounds.begin();
	        i != sounds.end();
	        i++) {
		AudioEngine::getSoundEngine()->unloadSound(i->second);
		delete i->second;
	}

	sounds.clear();

	// We unload the musics.
	for(std::map<std::string, MusicInfo*>::iterator i = musics.begin();
	        i != musics.end();
	        i++) {
		AudioEngine::getMusicEngine()->unloadMusic(i->second);
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

PixMap* ResourceManager::loadPixMap(const std::string& filePath) {
	return loadPixMapFromPNG(filePath);
}

PixMap* ResourceManager::loadPixMapFromPNG(const std::string& filePath) {


	FILE* PNG_file = fopen(filePath.c_str(), "rb");

	if(PNG_file == NULL) {
		Console::print("Unable to open this png file : " + filePath);
		return false;
	}

	uint8_t PNG_header[PNG_HEADER_SIZE];

	fread(PNG_header, 1, PNG_HEADER_SIZE, PNG_file);

	if(png_sig_cmp(PNG_header, 0, PNG_HEADER_SIZE) != 0) {
		Console::print("Trying to load a non png file as a png file. Path to file :" + filePath);
	}

	png_structp PNG_reader
	= png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if(PNG_reader == NULL) {
		Console::print("Cannot read this png file " + filePath);
	}

	png_infop PNG_info = png_create_info_struct(PNG_reader);

	if(PNG_info == NULL) {
		Console::print("Cannot extract info from this png file : " + filePath);
		png_destroy_read_struct(&PNG_reader, NULL, NULL);
	}

	png_infop PNG_end_info = png_create_info_struct(PNG_reader);

	if(PNG_end_info == NULL) {
		Console::print("Cannot extract end info from this png file : " + filePath);
		png_destroy_read_struct(&PNG_reader, &PNG_info, NULL);
	}

	if(setjmp(png_jmpbuf(PNG_reader))) {
		Console::print("Cannot load this png file " + filePath);
		png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);
	}

	png_init_io(PNG_reader, PNG_file);
	png_set_sig_bytes(PNG_reader, PNG_HEADER_SIZE);

	png_read_info(PNG_reader, PNG_info);

	png_uint_32 width, height;
	width = png_get_image_width(PNG_reader, PNG_info);
	height = png_get_image_height(PNG_reader, PNG_info);

	png_uint_32 bit_depth, color_type;
	bit_depth = png_get_bit_depth(PNG_reader, PNG_info);
	color_type = png_get_color_type(PNG_reader, PNG_info);

	if(color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(PNG_reader);
	}

	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
		png_set_expand_gray_1_2_4_to_8(PNG_reader);
	}

	if(color_type == PNG_COLOR_TYPE_GRAY ||
	        color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(PNG_reader);
	}

	if(png_get_valid(PNG_reader, PNG_info, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(PNG_reader);
	} else {
		png_set_filler(PNG_reader, 0xff, PNG_FILLER_AFTER);
	}

	if(bit_depth == 16) {
		png_set_strip_16(PNG_reader);
	}

	png_read_update_info(PNG_reader, PNG_info);

	png_byte* PNG_image_buffer = (png_byte*)malloc(4 * width * height);
	png_byte** PNG_rows = (png_byte**)malloc(height * sizeof(png_byte*));

	unsigned int row;

	for(row = 0; row < height; ++row) {
		PNG_rows[row] = PNG_image_buffer + (row * 4 * width);
	}

	png_read_image(PNG_reader, PNG_rows);

	free(PNG_rows);

	png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);
	fclose(PNG_file);

	PixMap* aPixMap = new PixMap(PNG_image_buffer, width, height);


	return aPixMap;
}

