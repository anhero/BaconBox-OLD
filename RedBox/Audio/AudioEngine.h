/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_AUDIO_ENGINE_H
#define RB_AUDIO_ENGINE_H

#include "SoundInfo.h"
#include "MusicInfo.h"
#include "SoundFX.h"
#include "BackgroundMusic.h"
#include "ResourceLoader.h"

namespace RedBox {
	class SoundFX;
	class BackgroundMusic;
	/**
	 * Abstract class used for the audio engines. Contains all the methods
	 * specific engines will require to have to be used by the resource loader.
	 * @ingroup Audio
	 */
	class AudioEngine {
		friend class ResourceLoader;
	public:
		/**
		 * Loads the sound and the music engine.
		 */
		static void loadAudioEngine();
		/**
		 * Loads the sound engine.
		 */
		static void loadSoundEngine();
		/**
		 * Loads the music engine.
		 */
		static void loadMusicEngine();
		/**
		 * Gets the sound engine.
		 * @return Pointer to the sound engine. Loads it if needed.
		 */
		static AudioEngine* getSoundEngine();
		/**
		 * Gets the music engine.
		 * @return Pointer to the music engine. Loads it if needed.
		 */
		static AudioEngine* getMusicEngine();
		/**
		 * Initializes the audio engine.
		 */
		virtual void init() = 0;
		/**
		 * Updates the necessary informations for the audio engine.
		 */
		virtual void update() = 0;
	protected:
		/**
		 * Default constructor. Can only be called by the resource loader.
		 */
		AudioEngine();
		/**
		 * Loads a sound effect using a file path.
		 * @param filePath Path to the file to load.
		 * @return Pointer to the loaded sound effect.
		 */
		virtual SoundFX* loadSoundFX(const std::string& filePath) = 0;
		/**
		 * Loads a sound effect using specific parameters.
		 * @param info Struct containing platform dependant information about
		 * the sound effect to load.
		 * @return Pointer to the loaded sound effect.
		 */
		virtual SoundFX* loadSoundFX(const SoundInfo& info) = 0;
		/**
		 * Loads a music using a file path.
		 * @param filePath Path to the music file to load.
		 * @return Pointer to the loaded music.
		 */
		virtual BackgroundMusic* loadBackgroundMusic(const std::string& filePath) = 0;
		/**
		 * Loads a music using specific parameters.
		 * @param info Struct containing platform dependant information about
		 * the music to load.
		 * @return Pointer to the loaded music.
		 */
		virtual BackgroundMusic* loadBackgroundMusic(const MusicInfo& info) = 0;
		/**
		 * Destructor. The audio engine can only be destroyed by the resource
		 * loader.
		 */
		virtual ~AudioEngine() = 0;
	private:
		static AudioEngine* soundEngine;
		static AudioEngine* musicEngine;
	};
}

#endif