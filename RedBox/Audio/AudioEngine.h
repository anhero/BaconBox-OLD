/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_AUDIO_ENGINE_H
#define RB_AUDIO_ENGINE_H

#include "SoundFX.h"
#include "BackgroundMusic.h"

namespace RedBox {
	class SoundFX;
	class BackgroundMusic;
	/**
	 * Abstract class used for the audio engines. Contains all the methods
	 * specific engines will require to have to be used by the resource loader.
	 * @ingroup Audio
	 */
	class AudioEngine {
	public:
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
	private:
		/**
		 * Destructor. The audio engine can only be destroyed by the resource
		 * loader.
		 */
		virtual ~AudioEngine() = 0;
	};
}

#endif