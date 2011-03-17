/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_BACKGROUNDMUSIC_H
#define RB_BACKGROUNDMUSIC_H

#include "Sound.h"

namespace RedBox {
	/**
	 * Abstract class for background musics. Used by engine specific classes for
	 * background music.
	 * @ingroup Audio
	 */
	class BackgroundMusic : public Sound {
		friend class AudioEngine;
	public:
		/**
		 * Destructor.
		 */
		virtual ~BackgroundMusic();
		/**
		 * Play the music with a fade in effect.
		 * @param nbTimes Number of times to play the music in loop. Negative
		 * value for infinite looping.
		 * @param fadeIn Time the fade in effect will last (in seconds).
		 */
		virtual void play(int nbTimes, double fadeIn) = 0;
		/**
		 * Stops the music with a fade out effect. Cannot be resumed and next
		 * time it will be played it will start from the beginning.
		 * @param fadeOut Time the fade out effect will last (in seconds).
		 */
		virtual void stop(double fadeOut) = 0;
		/**
		 * Pauses the music with a fade out effect. Remembers where it was
		 * paused so it can resume when calling the resume method.
		 * @param fadeOut Time the fade out effect will last (in seconds).
		 */
		virtual void pause(double fadeOut) = 0;
		/**
		 * Resumes the music with a fade in effect. Will only resume if the
		 * sound has been paused.
		 * @param fadeOut Time the fade in effect will last (in seconds).
		 */
		virtual void resume(double fadeIn) = 0;
	protected:
		/**
		 * Default constructor. Musics can only be created by the resource
		 * manager or the music engine.
		 */
		BackgroundMusic();
	};
}

#endif
