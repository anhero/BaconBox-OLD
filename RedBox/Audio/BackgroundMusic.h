/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_BACKGROUNDMUSIC_H
#define RB_BACKGROUNDMUSIC_H

#include "AudioEngine.h"
#include "ResourceManager.h"
#include "AudioState.h"

namespace RedBox {
	class AudioEngine;
	class ResourceManager;
	/**
	 * Abstract class for background musics. Used by engine specific classes for
	 * background music.
	 * @ingroup Audio
	 */
	class BackgroundMusic {
		friend class AudioEngine;
		friend class ResourceManager;
	public:
		/**
		 * Plays the background music. Plays the background music the number of
		 * times specified.
		 * @param nbTimes Number of times the music will be played. -1 is for
		 * infinite looping.
		 */
		virtual void play(int nbtimes = -1) = 0;
		/**
		 * Stops the music. Cannot be resumed and next time it will be played
		 * it will start from the beginning.
		 */
		virtual void stop() = 0;
		/**
		 * Pauses the music. Remembers where it was paused so it can resume when
		 * calling the resume method.
		 */
		virtual void pause() = 0;
		/**
		 * Resumes the music. Will only resume if the music has been paused.
		 */
		virtual void resume() = 0;
		/**
		 * Checks if the music is currently playing infinitely.
		 * @return True if the sound effect is currently playing.
		 */
		virtual bool isLooping() = 0;
		/**
		 * Gets the music's current state. Used to know if it is at its initial
		 * state, currently playing, paused or stopped.
		 * @see RedBox::AudioState::Enum
		 * @return Music's current state.
		 */
		virtual AudioState::Enum getCurrentState() = 0;
	protected:
		/**
		 * Default constructor. Musics can only be created by the resource
		 * loader or the audio engine.
		 */
		BackgroundMusic();
		/**
		 * Destructor. Musics can only be destroyed by the resource loader or
		 * audio engine.
		 */
		virtual ~BackgroundMusic();
	};
}

#endif
