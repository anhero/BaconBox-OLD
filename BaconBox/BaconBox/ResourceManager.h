/**
 * @file
 * @ingroup Display
 * @ingroup Audio
 */
#ifndef RB_RESOURCE_MANAGER_H
#define RB_RESOURCE_MANAGER_H

#include <string>
#include <map>

#include "BaconBox/Audio/SoundParameters.h"
#include "BaconBox/Audio/MusicParameters.h"
#include "BaconBox/Display/PixMap.h"

namespace BaconBox {
	class SoundFX;
	class BackgroundMusic;
	struct SoundInfo;
	struct MusicInfo;
	struct TextureInformation;
	class Color;
#ifndef RB_ANDROID
	class Font;
#endif
	/**
	 * Class that manages resources like textures and audio.
	 * @ingroup Display
	 * @ingroup Audio
	 */
	class ResourceManager {
		friend class Engine;
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
		static TextureInformation *addTexture(const std::string &key, PixMap *aPixmap,
		                                      bool overwrite = false);

		/**
		 * Loads a texture from a file and assigns a representative key to it.
		 * @param key Key used to identify this new texture.
		 * @param filePath Path to the file containing the texture.
		 * @param colorFormat Used to select the internal colorFormat of the texture. If you choose ALPHA while loading
		 * an RGBA image, the engine will use the red channel and strip the 3 other channel.
		 * @param overwrite When set to true, it will delete any existing
		 * texture at the specified key. (False (default) will print an error if
		 * the key is occupied).
		 * @return Pointer to the loaded texture, NULL if the texture failed to
		 * load.
		 */
		static TextureInformation *loadTexture(const std::string &key,
		                                       const std::string &filePath,
		                                       ColorFormat colorFormat = ColorFormat::RGBA,
		                                       bool overwrite = false);

		/**
		 * Loads a texture from a file and assigns a representative key to it.
		 * Color format is automatically RGBA.
		 * @param key Key used to identify this new texture.
		 * @param filePath Path to the file containing the texture.
		 * @param transparentColor Color to be read as transparent.
		 * @param overwrite When set to true, it will delete any existing
		 * texture at the specified key. (False (default) will print an error if
		 * the key is occupied).
		 * @return Pointer to the loaded texture, NULL if the texture failed to
		 * load.
		 */
		static TextureInformation *loadTextureWithColorKey(const std::string &key,
		                                                   const std::string &filePath,
		                                                   const Color &transparentColor,
		                                                   bool overwrite = false);

		/**
		 * Loads a texture from a file and assigns a representative key to it.
		 * This version of the loadTexture function needs a relative path from
		 * the resource folder, you cannot use an absolute path or pass your
		 * filename through ResourcePathHandler::getResourcePathFor.
		 * @param key Key used to identify this new texture.
		 * @param relativePath Relative path (relative to the resources folder)
		 * to the file containing the texture.
		 * @param colorFormat Used to select the internal colorFormat of the
		 * texture. If you choose ALPHA while loading an RGBA image, the engine
		 * will use the red channel and strip the 3 other channel.
		 * @param overwrite When set to true, it will delete any existing
		 * texture at the specified key. (False (default) will print an error if
		 * the key is occupied).
		 * @return Pointer to the loaded texture, NULL if the texture failed to
		 * load.
		 */
		static TextureInformation *loadTextureRelativePath(const std::string &key,
		                                                   const std::string &relativePath,
		                                                   ColorFormat colorFormat = ColorFormat::RGBA,
		                                                   bool overwrite = false);

		/**
		 * Loads a texture from a file and assigns a representative key to it.
		 * This version of the loadTexture function needs a relative path from
		 * the resource folder, you cannot use an absolute path or pass your
		 * filename through ResourcePathHandler::getResourcePathFor.
		 * @param key Key used to identify this new texture.
		 * @param relativePath Relative path (relative to the resources folder)
		 * to the file containing the texture.
		 * @param transparentColor Color to be read as transparent.
		 * @param overwrite When set to true, it will delete any existing
		 * texture at the specified key. (False (default) will print an error if
		 * the key is occupied).
		 * @return Pointer to the loaded texture, NULL if the texture failed to
		 * load.
		 */
		static TextureInformation *loadTextureRelativePathWithColorKey(const std::string &key,
		                                                               const std::string &relativePath,
		                                                               const Color &transparentColor,
		                                                               bool overwrite = false);
        
        
        
        
        /**
         * Remove a texture  GraphicMemory.
         */
        static void removeTexture(const std::string &key);

		/**
		 * Gets the information about the asked texture. Uses the texture's key
		 * to find it.
		 * @param key Key used to identify and find the asked texture.
		 * @return Pointer to the texture requested, NULL if no texture is
		 * associated with the given key.
		 */
		static TextureInformation *getTexture(const std::string &key);

		/**
		 * Gets a pointer to the asked sound effect.
		 * @param key Name of the sound effect to get a pointer of.
		 * @return Pointer to the asked sound effect, NULL if it doesn't exist.
		 */
		static SoundInfo *getSound(const std::string &key);

		/**
		 * Gets a pointer to the asked background music.
		 * @param key Name of the background music to get a pointer of.
		 * @return Pointer to the asked background music, NULL if it doesn't
		 * exist.
		 */
		static MusicInfo *getMusic(const std::string &key);

		/**
		 * Loads a sound effect.
		 * @param key Name to give to the sound effect.
		 * @param filePath Path to the sound file to load.
		 * @param overwrite Flag checked to know if the loaded sound will
		 * overwrite the existing sound if the key already exists.
		 * @return Pointer to the loaded sound effect. Returns NULL if the
		 * loading failed.
		 */
		static SoundInfo *loadSound(const std::string &key,
		                            const std::string &filePath,
		                            bool overwrite = false);

		/**
		 * Loads a sound effect. This version of the loadSound function needs
		 * a relative path from the resource folder, you cannot use an absolute
		 * path or pass your filename through
		 * ResourcePathHandler::getResourcePathFor.
		 * @param key Name to give to the sound effect.
		 * @param relativePath Relative path (relative to the resources folder)
		 * to the sound file to load.
		 * @param overwrite Flag checked to know if the loaded sound will
		 * overwrite the existing sound if the key already exists.
		 * @return Pointer to the loaded sound effect. Returns NULL if the
		 * loading failed.
		 */
		static SoundInfo *loadSoundRelativePath(const std::string &key,
		                                        const std::string &relativePath,
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
		static SoundInfo *loadSound(const SoundParameters &info,
		                            bool overwrite = false);

		/**
		 * Loads a background music.
		 * @param key Name to give to the background music.
		 * @param filePath Path to the music file to load.
		 * @param overwrite Flag checked to know if the loaded music will
		 * oerwrite the existing music if the key already exists.
		 * @return Pointer to the loaded music, NULL if the loading failed.
		 */
		static MusicInfo *loadMusic(const std::string &key,
		                            const std::string &filePath,
		                            bool overwrite = false);

		/**
		 * Loads a background music. This version of the loadMusic function
		 * needs a relative path from the resources folder, you cannot use an
		 * absolute path or pass your filename through
		 * ResourcePathHandler::getResourcePathFor.
		 * @param key Name to give to the background music.
		 * @param relativePath Relative path (relative to the resources folder)
		 * to the music file to load.
		 * @param overwrite Flag checked to know if the loaded music will
		 * oerwrite the existing music if the key already exists.
		 * @return Pointer to the loaded music, NULL if the loading failed.
		 */
		static MusicInfo *loadMusicRelativePath(const std::string &key,
		                                        const std::string &relativePath,
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
		static MusicInfo *loadMusic(const MusicParameters &info,
		                            bool overwrite = true);

		/**
		 * Removes and unloads a sound effect. Does nothing if no sound effect
		 * is associated with the given key.
		 * @param key Name of the sound effect to unload.
		 */
		static void removeSound(const std::string &key);

		/**
		 * Removes and unloads a background music. Does nothing if no background
		 * music is associated with the given key.
		 * @param key Name of the background music to unload.
		 */
		static void removeMusic(const std::string &key);

#ifndef RB_ANDROID
		/**
		 * Loads the font at the specified path and put it in the fonts' map.
		 * @param key Name of the font, it will be the key of the fonts' map.
		 * @param path Path of the font.
		 * @param overwrite Flag checked to know if the loaded font will
		 * overwrite the existing font if the key already exists.
		 * @return Pointer to the loaded font, NULL if the font failed to load.
		 */
		static Font *loadFont(const std::string &key,
		                      const std::string &path, bool overwrite = false);

		/**
		 * Loads the font at the specified path and put it in the fonts' map.
		 * This version of the loadMusic function needs a relative path from the
		 * resources folder, you cannot use an absolute path or pass your
		 * filename through ResourcePathHandler::getResourcePathFor.
		 * @param key Name of the font, it will be the key of the fonts' map.
		 * @param relativePath Relative path (relative to the resources folder)
		 * to the font file to load.
		 * @param overwrite Flag checked to know if the loaded font will
		 * overwrite the existing font if the key already exists.
		 * @return Pointer to the loaded font, NULL if the font failed to load.
		 */
		static Font *loadFontRelativePath(const std::string &key,
		                                  const std::string &relativePath,
		                                  bool overwrite = false);

		/**
		 * Return a pointer to the font specified by the given name.
		 * @param key Key of the font to get.
		 * @return Pointer to the specified font, NULL if no font is found.
		 */
		static Font *getFont(const std::string &key);

		/**
		 * Remove the specified font from the fonts' map.
		 * @param key Key of the font to remove.
		 */
		static void removeFont(const std::string &key);
#endif
		
		/// Create a PixMap from an image file at the given path.
		static PixMap *loadPixMap(const std::string &filePath, ColorFormat colorFormat);
		
		/**
		 * Loads a pixmap from a file and sets a specific color as transparent.
		 * @param filePath Path to the file to read.
		 * @param transparentColor Color to be made transparent.
		 */
		static PixMap *loadPixMap(const std::string &filePath,
		                          const Color &transparentColor);
		
		/**
		 * Saves a PixMap to a file at the given path.
		 * @param pixMap PixMap to save to a file.
		 * @param filePath Path to the file to write.
		 */
		static void savePixMap(const PixMap &pixMap,
							   const std::string &filePath);
	private:
		/**
		 * Unloads everything in the ResourceManager.
		 */
		static void unloadAll();

		///Create a PixMap from a PNG file at the given path.
		static PixMap *loadPixMapFromPNG(const std::string &filePath);
		
		/**
		 * Saves a PixMap to a PNG file.
		 * @param pixMap PixMap to save to a PNG file.
		 * @param filePath Path to the PNG file to write.
		 */
		static void savePixMapToPNG(const PixMap &pixMap, const std::string &filePath);

		/// Map associating the textures' keys and their information.
		static std::map<std::string, TextureInformation *> textures;

		/// Map associating the sound effects' names and their information.
		static std::map<std::string, SoundInfo *> sounds;

		/// Map associating the musics' names and their information.
		static std::map<std::string, MusicInfo *> musics;
#ifndef RB_ANDROID
		/// Map  associating the fonts' names and their information.
		static std::map<std::string, Font *> fonts;
#endif
	};
}

#endif
