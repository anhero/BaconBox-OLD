/**
 * @file
 * @ingroup Display
 */

#ifndef RB_RESOURCE_MANAGER_H
#define RB_RESOURCE_MANAGER_H

#include <string>
#include <map>

#include "Debug.h"
#include "TextureInfo.h"
#include "AudioEngine.h"
#include "Font.h"

namespace RedBox {
	class SoundFX;
	class BackgroundMusic;
	/**
	 * Class that manages resources like textures and audio.
	 * @ingroup Display
	 */
	class ResourceManager {
	public:
		
		static TextureInfo* addTexture(const std::string& key, unsigned char * bitmap, int width, int height);
		/**
		 * Loads a texture from a file and assigns a representative key to it.
		 * @param filePath Path to the file containing the texture.
		 * @param key Key used to identify this new texture.
		 */
		static TextureInfo* loadTexture(const std::string& filePath,
										const std::string& key,
										bool overwrite = false);
		/**
		 * Gets the information about the asked texture. Uses the texture's key
		 * to find it.
		 * @param key Key used to identify and find the asked texture.
		 */
		static TextureInfo* getTexture(const std::string& key);
		/**
		 * Gets a pointer to the asked sound effect.
		 * @param key Name of the sound effect to get a pointer of.
		 * @return Pointer to the asked sound effect, NULL if it doesn't exist.
		 */
		static SoundFX* getSoundFX(const std::string& key);
		/**
		 * Gets a pointer to the asked background music.
		 * @param key Name of the background music to get a pointer of.
		 * @return Pointer to the asked background music, NULL if it doesn't
		 * exist.
		 */
		static BackgroundMusic* getBackgroundMusic(const std::string& key);
		/**
		 * Loads a sound effect.
		 * @param name Name to give to the sound effect.
		 * @param info Information needed to load the sound effect. Audio engine
		 * dependant.
		 * @return Pointer to the loaded sound effect. Returns NULL if the
		 * loading failed.
		 */
		static SoundFX* loadSoundFX(const std::string& filePath,
									const std::string& key,
									bool overwrite = false);
		/**
		 * Loads a sound effect.
		 * @param info Information in a struct about the sound effect to load.
		 * Let's the developer specify more precise parameters for specific
		 * engines.
		 * @return Pointer to the loaded sound effect. Returns NULL if the
		 * loading failed.
		 */
		static SoundFX* loadSoundFX(const SoundInfo& info,
									bool overwrite = false);
		/**
		 * Loads a background music.
		 * @param name Name to give to the background music.
		 * @param info Information needed to load the background music. Audio
		 * Engine dependant.
		 * @return Pointer to the loaded background music. Returns NULL if the
		 * loading failed.
		 */
		static BackgroundMusic* loadBackgroundMusic(const std::string& filePath,
													const std::string& key,
													bool overwrite = false);
		/**
		 * Loads a background music.
		 * @param info Information in a struct about the sound effect to load.
		 * Let's the developer specify more precise parameters for specific
		 * engines.
		 * @return Pointer to the loaded sound effect. Returns NULL if the
		 * loading failed.
		 */
		static BackgroundMusic* loadBackgroundMusic(const MusicInfo& info,
													bool overwrite = true);
		/**
		 * Removes and unloads a sound effect.
		 * @param name Name of the sound effect to unload.
		 */
		static void removeSoundFX(const std::string& name);
		/**
		 * Removes and unloads a background music.
		 * @param name Name of the background music to unload.
		 */
		static void removeBackgroundMusic(const std::string& name);
		
		/**
		 * Load the fond at the specified path and put it in the fonts' map.
		 * @param name Name of the font, it will be the key of the fonts' map.
		 * @param path Path of the font.
		 */
		static Font* loadFont(std::string & name, std::string & path);
		
		/**
		 * Return a pointer to the font specified by the given name. 
		 * @param name Name of the font.
		 * @return Return a pointer to the specified font or NULL if no font is found.
		 */
		static Font* getFont(std::string & name);
		
		
		/**
		 * Remove the specified font from the fonts' map.
		 */
		static void removeFont(std::string & name);
		
		/**
		 * Unloads everything in the ResourceManager.
		 */
		static void unloadAll();
	private:
		static TextureInfo* loadTexture(const std::string& filePath);
		/// Map associating the textures' keys and their information.
		static std::map<std::string, TextureInfo*> textures;
		/// Map associating the sound effects' names and their information.
		static std::map<std::string, SoundFX*> sounds;
		/// Map associating the musics' names and their information.
		static std::map<std::string, BackgroundMusic*> musics;
		/// Map  associating the fonts' names and their information.
		static std::map<std::string, Font*> fonts;
	};
}

#endif