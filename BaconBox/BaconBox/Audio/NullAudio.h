/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_NULL_AUDIO_H
#define RB_NULL_AUDIO_H

#include "BackgroundMusic.h"
#include "SoundFX.h"

namespace BaconBox {
	/**
	 * Class used when audio engine implementation instead of returning NULL.
	 * It makes the game not crash and helps debugging.
	 * @ingroup Audio
	 */
	class NullAudio : public BackgroundMusic, public SoundFX {
		friend class AudioEngine;
	public:
		/**
		 * Plays the sound a given number of times.
		 * @param nbTimes Number of times the sound will be played in loop. A
		 * negative number is for infinite looping.
		 */
		void play(int nbTimes);
		/**
		 * Stops the sound. Cannot be resumed and next time it will be played
		 * it will start from the beginning.
		 */
		void stop();
		/**
		 * Pauses the sound. Remembers where it was paused so it can resume when
		 * calling the resume method.
		 */
		void pause();
		/**
		 * Resumes the sound. Will only resume if the sound has been paused.
		 */
		void resume();
		/**
		 * Checks if the sound is currently playing infinitely.
		 * @return True if the sound is currently playing infinitely.
		 */
		bool isLooping();
		/**
		 * Gets the sound's current state. Used to know if it is at its initial
		 * state, currently playing, paused, etc.
		 * @return Sound's current state.
		 * @see BaconBox::AudioState::Enum
		 */
		AudioState getCurrentState() const;
		/**
		 * Play the music with a fade in effect.
		 * @param nbTimes Number of times to play the music in loop. Negative
		 * value for infinite looping.
		 * @param fadeIn Time the fade in effect will last (in seconds).
		 */
		void play(int nbTimes, double fadeIn);
		/**
		 * Stops the music with a fade out effect. Cannot be resumed and next
		 * time it will be played it will start from the beginning.
		 * @param fadeOut Time the fade out effect will last (in seconds).
		 */
		void stop(double fadeOut);
		/**
		 * Pauses the music with a fade out effect. Remembers where it was
		 * paused so it can resume when calling the resume method.
		 * @param fadeOut Time the fade out effect will last (in seconds).
		 */
		void pause(double fadeOut);
		/**
		 * Resumes the music with a fade in effect. Will only resume if the
		 * sound has been paused.
		 * @param fadeIn Time the fade in effect will last (in seconds).
		 */
		void resume(double fadeIn);
		/**
		 * Destructor. Does not delete the sound data, only the sound source.
		 * This is done to be able to have many sounds playing the same
		 * sound without having it loaded many times in memory.
		 */
		virtual ~NullAudio();
		/**
		 * Default constructor. Can only be called by the audio engine.
		 */
		NullAudio();
	};
}

#endif
