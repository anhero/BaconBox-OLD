/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SDL_MIXER_BACKGROUND_MUSIC_H
#define RB_SDL_MIXER_BACKGROUND_MUSIC_H

#include "PlatformFlagger.h"

#ifdef RB_SDL

#include <stdint.h>

#include <SDL/SDL_mixer.h>

#include <sigly.h>

#include "BackgroundMusic.h"

namespace RedBox {
	/**
	 * SDL_mixer implementation for background musics.
	 * @ingroup Audio
	 */
	class SDLMixerBackgroundMusic : public BackgroundMusic,
		public sigly::HasSlots<> {
		friend class SDLMixerEngine;
		friend class sigly::Signal1<unsigned int>;
	public:
		/**
		 * Callback function given to SDL_mixer that gets called when a music
		 * is halted or is done playing.
		 */
		static void stoppedCurrentMusic();
		/**
		 * Destructor.
		 */
		~SDLMixerBackgroundMusic();
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
		 * @see RedBox::AudioState::Enum
		 */
		AudioState::Enum getCurrentState();
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
		 * @param fadeOut Time the fade in effect will last (in seconds).
		 */
		void resume(double fadeIn);
	private:
		/**
		 * Used by the fadeType boolean to mean the music is fading out on
		 * pause.
		 */
		static const bool FADE_OUT = true;
		/**
		 * Used by the fadeType boolean to mean the music is fading in on
		 * pause.
		 */
		static const bool FADE_IN = false;
		/// Pointer to the current music being played.
		static SDLMixerBackgroundMusic* currentMusic;
		/// Set to true if the current music is on pause.
		static bool isBeingPaused;
		/// Pointer to the music to play.
		Mix_Music* music;
		/// Set to true if the music is infinitely looping.
		bool looping;
		/**
		 * Set to true if the music has not been played at least once. So it
		 * means that it is in its initial state.
		 */
		bool neverPlayed;

		/// Set to true if the music is currently fading in our out of pause.
		bool pauseResumeFading;
		/**
		 * Set to true if it is fading out into pause, or false if it is
		 * fading in to resume.
		 */
		bool fadeType;
		/// Time the pause/resume fading has to take.
		unsigned int fadeTime;
		/// Time at which the pause/resume fading started.
		unsigned int fadeStart;

		/**
		 * Default constructor. Musics can only be created by the resource
		 * manager or the music engine.
		 */
		SDLMixerBackgroundMusic();

		/**
		 * Sets the music.
		 * @param newMusic Pointer to the music to set.
		 */
		void load(Mix_Music* newMusic);

		/**
		 * Slot called when a pause/resume fading is to be updated. SDL_mixer
		 * doesn't support fading to pause or resume a music. So we simulate
		 * it manually. Every 100 ms, the audio engine will call this method
		 * when the music is fading in or out to pause or resume. When the
		 * fading is done, we ask the engine to not be called anymore on
		 * fade updates.
		 */
		void fadeUpdate(unsigned int ticks);

		/**
		 * Resets the pause and resume fading.
		 */
		void resetPauseResumeFade();
	};
}

#endif

#endif
