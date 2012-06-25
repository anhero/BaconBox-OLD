/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SOUND_H
#define RB_SOUND_H

#include "AudioState.h"

namespace BaconBox {
	/**
	 * Abstract class for sounds. Sound effect and background music abstract
	 * classes derive from this class.
	 * @ingroup Audio
	 */
	class Sound {
		friend class AudioEngine;
	public:
		/// Minimum volume level.
		static const int MIN_VOLUME = 0;

		/// Maximum volume level.
		static const int MAX_VOLUME = 100;

		/**
		 * Plays the sound a given number of times.
		 * @param nbTimes Number of times the sound will be played in loop. A
		 * negative number is for infinite looping.
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
		/**
		 * Checks if the sound is currently playing infinitely.
		 * @return True if the sound is currently playing infinitely.
		 */
		virtual bool isLooping() = 0;

		/**
		 * Gets the sound's volume.
		 * @return Sound's current volume level.
		 * @see BaconBox::Sound::volume
		 */
		int getVolume() const;

		/**
		 * Sets the sound's volume level.
		 * @param newVolume New volume level. If the new volume is out of
		 * bounds, it will be set to the closest bound (minimum if it's under 0
		 * or maximum if it's over 100).
		 * @see BaconBox::Sound::volume
		 */
		virtual void setVolume(int newVolume);

		/**
		 * Gets the sound's current state. Used to know if it is at its initial
		 * state, currently playing, paused, etc.
		 * @return Sound's current state.
		 * @see BaconBox::AudioState::Enum
		 */
		virtual AudioState getCurrentState() const = 0;
		/**
		 * Destructor. Does not delete the sound data, only the sound source.
		 * This is done to be able to have many sounds playing the same
		 * sound without having it loaded many times in memory.
		 */
		virtual ~Sound();
	protected:
		/**
		 * Default constructor. Can only be called by the audio engine.
		 */
		Sound();
	private:
		/// Value between 0 and 100 for the volume level. 100 is the maximum.
		int volume;
	};
}

#endif // RB_SOUND_H
