/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_AUDIO_ENGINE_H
#define RB_AUDIO_ENGINE_H

#include <string>

namespace BaconBox {
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
		friend class Engine;
	public:
		/**
		 * Gets the sound engine.
		 * @return Pointer to the sound engine. Loads it if needed.
		 */
		static SoundEngine& getSoundEngine();
		/**
		 * Gets the music engine.
		 * @return Pointer to the music engine. Loads it if needed.
		 */
		static MusicEngine& getMusicEngine();

		/**
		 * Plays a sound effect if a sound engine is available.
		 * @param key Name of the sound resource to play.
		 * @param nbTimes Number of times to play the sound (-1 for infinite
		 * looping).
		 */
		static void playSoundFX(const std::string& key, int nbTimes = 1);

		/**
		 * Plays a background music if a music engine is available.
		 * @param key Name of the music resource to play.
		 * @param nbTimes Number of times to play the music (-1 for infinite
		 * looping).
		 * @param fadeIn Time the music takes to fade in to full volume.
		 */
		static void playBackgroundMusic(const std::string& key,
										int nbTimes = -1,
										double fadeIn = 0.0);
	protected:
		/**
		 * Default constructor.
		 */
		AudioEngine();

		/**
		 * Destructor. The audio engine can only be destroyed by the resource
		 * manager.
		 */
		virtual ~AudioEngine();

		/**
		 * Updates the necessary informations for the audio engine.
		 */
		virtual void update() = 0;
	};
}

#endif // RB_AUDIO_ENGINE_H
