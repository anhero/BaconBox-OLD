/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_BACKGROUNDMUSIC_H
#define RB_BACKGROUNDMUSIC_H

namespace RedBox {
	/**
	 * Abstract class for background musics. Used by engine specific classes for
	 * background music.
	 * @ingroup Audio
	 */
	class BackgroundMusic {
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
	protected:
		/**
		 * Default constructor. Musics can only be created by the resource
		 * loader or the audio engine.
		 */
		BackgroundMusic();
	private:
		/**
		 * Destructor. Musics can only be destroyed by the resource loader or
		 * audio engine.
		 */
		virtual ~BackgroundMusic() = 0;
	};
}

#endif
