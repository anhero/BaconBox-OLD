#ifndef RB_SDL_MIXER_BACKGROUND_MUSIC_H
#define RB_SDL_MIXER_BACKGROUND_MUSIC_H

#include "PlatformFlagger.h"

#ifdef RB_SDL

#include <stdint.h>

#include <SDL/SDL_mixer.h>

#include <sigly.h>

#include "BackgroundMusic.h"

namespace RedBox {
	class SDLMixerBackgroundMusic : public BackgroundMusic,
	public sigly::HasSlots<> {
		friend class SDLMixerEngine;
		friend class sigly::Signal1<unsigned int>;
	public:
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
		static SDLMixerBackgroundMusic* currentMusic;
		static bool isBeingPaused;
		static const bool FADE_OUT = true;
		static const bool FADE_IN = false;
		Mix_Music* music;
		bool looping;
		bool neverPlayed;
		
		bool pauseResumeFading;
		bool fadeType;
		unsigned int fadeTime;
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
		 * Slot called when a pause/resume fading is to be updated.
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