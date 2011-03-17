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
	 * Abstract class used for the audio engines. Sound engines and music
	 * engines derive from this class.
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
		 * Loads the sound engine. Calls its init() method after being created.
		 * Does nothing if the sound engine has already been loaded.
		 */
		static void loadSoundEngine();
		/**
		 * Loads the music engine. Calls its init() method after being created.
		 * Does nothing if the music engine has already been loaded.
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
		 * Default constructor.
		 */
		AudioEngine();
		/**
		 * Initializes the audio engine. Called by the static functions that
		 * load the audio engines.
		 */
		virtual void init() = 0;
		/**
		 * Updates the necessary informations for the audio engine.
		 */
		virtual void update() = 0;
		/**
		 * Destructor. The audio engine can only be destroyed by the resource
		 * manager.
		 */
		virtual ~AudioEngine();
	private:
		/// Pointer to the sound engine singleton.
		static SoundEngine* soundEngine;
		/// Pointer to the music engine singleton.
		static MusicEngine* musicEngine;
	};
}

#endif // RB_AUDIO_ENGINE_H
