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
#include "AudioEngine.h"

namespace RedBox {
	class SoundFX;
	class BackgroundMusic;
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
		/**
		 * Sets the audio engine to be used.
		 */
		static void startAudioEngine();
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
	private:
		/// Map associating the textures' keys and their information.
		static std::map<std::string, TextureInfo> textures;
		/// Map associating the sound effects' names and their information.
		static std::map<std::string, SoundFX*> sounds;
		/// Map associating the musics' names and their information.
		static std::map<std::string, BackgroundMusic*> musics;
		//1 Pointer to the audio engine used to play sounds.
		static AudioEngine* soundEngine;
		/// Pointer to the music engine used to play musics.
		static AudioEngine* musicEngine;
	};
}

#endif