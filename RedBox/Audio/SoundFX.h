/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SOUNDFX_H
#define RB_SOUNDFX_H

#include "AudioEngine.h"
#include "ResourceManager.h"

namespace RedBox {
	class AudioEngine;
	class ResourceManager;
	/**
	 * Abstract class for sound effects. Used by engine specific classes for
	 * sound effects.
	 * @ingroup Audio
	 */
	class SoundFX {
		friend class AudioEngine;
		friend class ResourceManager;
	public:
		/**
		 * Plays the sound effect. Will make the necessary calls itself to the
		 * engine.
		 * @param nbTimes Number of times the sound effect will be played in
		 * loop. A negative number is for infinite looping.
		 */
		virtual void play(int nbTimes = 1) = 0;
		/**
		 * Stops the sound. Cannot be resumed and next time it will be played
		 * it will start from the beginning.
		 */
		virtual void stop() = 0;
		/**
		 * Pauses the sound. Remembers where it was paused so it can resume when
		 * calling the resume method.
		 */
		virtual void pause() = 0;
		/**
		 * Resumes the sound. Will only resume if the sound has been paused.
		 */
		virtual void resume() = 0;
	protected:
		/**
		 * Default constructor. Can only be called by the resource loader or the
		 * audio engine.
		 */
		SoundFX();
		/**
		 * Destructor. Sound effects can only be destroyed by the resource
		 * loader or the audio engine.
		 */
		virtual ~SoundFX();
	};
}

#endif // RB_SOUNDFX_H
