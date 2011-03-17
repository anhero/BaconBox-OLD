/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_AUDIO_ENGINE_H
#define RB_AUDIO_ENGINE_H

namespace RedBox {
	class SoundFX;
	class BackgroundMusic;
	class SoundEngine;
	class MusicEngine;
	/**
	 * Abstract class used for the audio engines. Contains all the methods
	 * specific engines will require to have to be used by the resource loader.
	 * @ingroup Audio
	 */
	class AudioEngine {
		friend class ResourceManager;
		friend class RedBoxEngine;
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
		static SoundEngine* getSoundEngine();
		/**
		 * Gets the music engine.
		 * @return Pointer to the music engine. Loads it if needed.
		 */
		static MusicEngine* getMusicEngine();
		/**
		 * Unloads the audio engines. Must be called after the resource manager
		 * has unloaded everything related to the audio engine.
		 */
		static void unloadAudioEngines();
	protected:
		/**
		 * Default constructor. Only called by its children's constructors.
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
		 * Destructor. The audio engine can only be destroyed by the resource
		 * loader.
		 */
		virtual ~AudioEngine();
	private:
		static SoundEngine* soundEngine;
		static MusicEngine* musicEngine;
	};
}

#endif // RB_AUDIO_ENGINE_H
