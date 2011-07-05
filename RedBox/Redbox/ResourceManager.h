/**
 * @file
 * @ingroup Display
 * @ingroup Audio
 */
#ifndef RB_RESOURCE_MANAGER_H
#define RB_RESOURCE_MANAGER_H

#include <string>
#include <map>

#include "SoundParameters.h"
#include "MusicParameters.h"
#ifndef RB_ANDROID
	#include "Font.h"
#endif
#include "PixMap.h"

namespace RedBox {
	class SoundFX;
	class BackgroundMusic;
	class SoundInfo;
	class MusicInfo;
	class TextureInfo;
	/**
	 * Class that manages resources like textures and audio.
	 * @ingroup Display
	 * @ingroup Audio
	 */
	class ResourceManager {
	public:
		/**
		 * Add a texture already loaded as a pixmap into the graphic memory and
		 * resource manager.
		 * @param key Key used to identify this new texture.
		 * @param aPixmap The pixel map you want to use as a texture
		 * @param overwrite When set to true, it will delete any existing
		 * texture at the specified key. (False (default) will print an error if
		 * the key is occupied).
		 * @return Pointer to the added texture information. Returns NULL if the
		 * texture failed to be added.
		 */
		static TextureInfo* addTexture(const std::string& key, PixMap* aPixmap,
		                               bool overwrite = false);

		/**
		 * Loads a texture from a file and assigns a representative key to it.
		 * @param key Key used to identify this new texture.
		 * @param filePath Path to the file containing the texture.
		 * @param overwrite When set to true, it will delete any existing
		 * texture at the specified key. (False (default) will print an error if
		 * the key is occupied).
		 * @return Pointer to the loaded texture, NULL if the texture failed to
		 * load.
		 */
		static TextureInfo* loadTexture(const std::string& key,
		                                const std::string& filePath,
		                                bool overwrite = false);

		/**
		 * Gets the information about the asked texture. Uses the texture's key
		 * to find it.
		 * @param key Key used to identify and find the asked texture.
		 * @return Pointer to the texture requested, NULL if no texture is
		 * associated with the given key.
		 */
		static TextureInfo* getTexture(const std::string& key);

		/**
		 * Gets a pointer to the asked sound effect.
		 * @param key Name of the sound effect to get a pointer of.
		 * @return Pointer to the asked sound effect, NULL if it doesn't exist.
		 */
		static SoundInfo* getSound(const std::string& key);

		/**
		 * Gets a pointer to the asked background music.
		 * @param key Name of the background music to get a pointer of.
		 * @return Pointer to the asked background music, NULL if it doesn't
		 * exist.
		 */
		static MusicInfo* getMusic(const std::string& key);

		/**
		 * Loads a sound effect.
		 * @param key Name to give to the sound effect.
		 * @param filePath Path to the sound file to load.
		 * @param overwrite Flag checked to know if the loaded sound will
		 * overwrite the existing sound if the key already exists.
		 * @return Pointer to the loaded sound effect. Returns NULL if the
		 * loading failed.
		 */
		static SoundInfo* loadSound(const std::string& key,
		                            const std::string& filePath,
		                            bool overwrite = false);

		/**
		 * Loads a sound effect.
		 * @param info Information in a struct about the sound effect to load.
		 * Let's the developer specify more precise parameters for specific
		 * engines.
		 * @param overwrite Flag checked to know if the loaded sound will
		 * overwrite the existing sound if the key already exists.
		 * @return Pointer to the loaded sound effect, NULL if the loading
		 * failed.
		 */
		static SoundInfo* loadSound(const SoundParameters& info,
		                            bool overwrite = false);

		/**
		 * Loads a background music.
		 * @param key Name to give to the background music.
		 * @param filePath Path to the music file to load.
		 * @param overwrite Flag checked to know if the loaded music will
		 * oerwrite the existing music if the key already exists.
		 * @return Pointer to the loaded music, NULL if the loading failed.
		 */
		static MusicInfo* loadMusic(const std::string& key,
		                            const std::string& filePath,
		                            bool overwrite = false);

		/**
		 * Loads a background music.
		 * @param info Information in a struct about the sound effect to load.
		 * Let's the developer specify more precise parameters for specific
		 * engines.
		 * @param overwrite Flag checked to know if the loaded sound will
		 * overwrite the existing sound if the key already exists.
		 * @return Pointer to the loaded music, NULL if the loading failed.
		 */
		static MusicInfo* loadMusic(const MusicParameters& info,
		                            bool overwrite = true);

		/**
		 * Removes and unloads a sound effect. Does nothing if no sound effect
		 * is associated with the given key.
		 * @param key Name of the sound effect to unload.
		 */
		static void removeSound(const std::string& key);

		/**
		 * Removes and unloads a background music. Does nothing if no background
		 * music is associated with the given key.
		 * @param key Name of the background music to unload.
		 */
		static void removeMusic(const std::string& key);

#ifndef RB_ANDROID
		/**
		 * Load the font at the specified path and put it in the fonts' map.
		 * @param key Name of the font, it will be the key of the fonts' map.
		 * @param path Path of the font.
		 * @param overwrite Flag checked to know if the loaded font will
		 * overwrite the existing font if the key already exists.
		 * @return Pointer to the loaded font, NULL if the font failed to load.
		 */
		static Font* loadFont(const std::string& key,
		                      const std::string& path, bool overwrite = false);

		/**
		 * Return a pointer to the font specified by the given name.
		 * @param key Key of the font to get.
		 * @return Pointer to the specified font, NULL if no font is found.
		 */
		static Font* getFont(const std::string& key);

		/**
		 * Remove the specified font from the fonts' map.
		 * @param key Key of the font to remove.
		 */
		static void removeFont(const std::string& key);
#endif
		/**
		 * Unloads everything in the ResourceManager.
		 */
		static void unloadAll();
	private:
		///Create a PixMap from an image file at the given path.
		static PixMap* loadPixMap(const std::string& filePath);

		///Create a PixMap from a PNG file at the given path.
		static PixMap* loadPixMapFromPNG(const std::string& filePath);

		/// Map associating the textures' keys and their information.
		static std::map<std::string, TextureInfo*> textures;

		/// Map associating the sound effects' names and their information.
		static std::map<std::string, SoundInfo*> sounds;

		/// Map associating the musics' names and their information.
		static std::map<std::string, MusicInfo*> musics;
#ifndef RB_ANDROID
		/// Map  associating the fonts' names and their information.
		static std::map<std::string, Font*> fonts;
#endif
	};
}

#endif
