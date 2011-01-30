/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SOUNDFX_H
#define RB_SOUNDFX_H

namespace RedBox {
	/**
	 * Abstract class for sound effects. Used by engine specific classes for
	 * sound effects.
	 * @ingroup Audio
	 */
	class SoundFX {
	public:
		/**
		 * Plays the sound effect. Will make the necessary calls itself to the
		 * engine.
		 * @param nbTimes Number of times the sound effect will be played in
		 * loop. -1 is for infinite looping.
		 */
		virtual void play(int nbTimes = 1) = 0;
	protected:
		/**
		 * Default constructor. Can only be called by the resource loader or the
		 * audio engine.
		 */
		SoundFX();
	private:
		/**
		 * Destructor. Sound effects can only be destroyed by the resource
		 * loader or the audio engine.
		 */
		virtual ~SoundFX() = 0;
	};
}

#endif // RB_SOUNDFX_H
