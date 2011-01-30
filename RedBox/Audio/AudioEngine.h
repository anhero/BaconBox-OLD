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
	class ResourceLoader;
	/**
	 * Abstract class used for the audio engines. Contains all the methods
	 * specific engines will require to have to be used by the resource loader.
	 * @ingroup Audio
	 */
	class AudioEngine {
		friend class ResourceLoader;
	protected:
		/**
		 * Default constructor. Can only be called by the resource loader.
		 */
		AudioEngine();
		/**
		 * Initializes the audio engine.
		 */
		virtual void init() = 0;
		/**
		 * Updates the necessary informations for the audio engine.
		 */
		virtual void update() = 0;
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
	private:
		/**
		 * Destructor. The audio engine can only be destroyed by the resource
		 * loader.
		 */
		virtual ~AudioEngine() = 0;
	};
}

#endif