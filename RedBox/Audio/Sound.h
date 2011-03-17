/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SOUND_H
#define RB_SOUND_H

#include "AudioState.h"

namespace RedBox {
	/**
	 * Abstract class for sounds. Sound effect and background music abstract
	 * classes inherit from this class.
	 * @ingroup Audio
	 */
	class Sound {
		friend class AudioEngine;
		friend class ResourceManager;
	public:
		/**
		 * Plays the sound.
		 * @param nbTimes Number of times the sound will be played in loop. A
		 * negative number is for infinite looping.
		 */
		virtual void play(int nbTimes) = 0;
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
		/**
		 * Checks if the sound effect is currently playing infinitely.
		 * @return True if the sound effect is currently playing.
		 */
		virtual bool isLooping() = 0;
		/**
		 * Gets the sound's current state. Used to know if it is at its initial
		 * state, currently playing, paused or stopped.
		 * @return Sound effect's current state.
		 * @see RedBox::AudioState::Enum
		 */
		virtual AudioState::Enum getCurrentState() = 0;
	protected:
		/**
		 * Default constructor. Can only be called by the resource manager or
		 * the audio engine.
		 */
		Sound();
		/**
		 * Destructor. Sound effects can only be destroyed by the resource
		 * loader or the audio engine.
		 */
		virtual ~Sound();
	};
}

#endif // RB_SOUND_H