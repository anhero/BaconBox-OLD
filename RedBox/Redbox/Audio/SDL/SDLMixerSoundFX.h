/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SDL_MIXER_SOUNDFX_H
#define RB_SDL_MIXER_SOUNDFX_H

#include "PlatformFlagger.h"

#ifdef RB_SDL

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <sigly.h>

#include "SoundFX.h"

namespace RedBox {
	class SDLMixerSoundFX : public SoundFX, public sigly::HasSlots<> {
		friend class SDLMixerEngine;
		friend class sigly::Signal1<int>;
	public:
		static void channelHalted(int channel);
		/**
		 * Plays the sound a given number of times.
		 * @param nbTimes Number of times the sound will be played in loop. A
		 * negative number is for infinite looping.
		 */
		void play(int nbTimes = 1);
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
		 * Destructor.
		 */
		~SDLMixerSoundFX();
	private:
		static const int LOOPING = -1;
		static const int INVALID_CHANNEL = -1;
		/// Signal sent when a channel is done.
		static sigly::Signal1<int> haltChannel;
		/// Set to true if the sound effect is currently looping infinitely.
		bool looping;
		/// Number of the channel the sound is being played on.
		int channel;
		/// Pointer to the sound's data.
		Mix_Chunk* data;
		bool hasPlayed;

		/**
		 * Default constructor. Can only be called by the sound engine.
		 */
		SDLMixerSoundFX();

		/**
		 * Loads a sound effect from sound data.
		 * @param newData Pointer to the Mix_Chunk containing the sound data.
		 */
		void load(Mix_Chunk* newData);

		/**
		 * Gets the channel number on which the sound is currently played or
		 * on which it last played if it wasn't stopped manually.
		 * @return Channel number used by the sound effect.
		 */
		int getChannel() const;

		/**
		 * Method called when a channel is stopped.
		 * @param channelHalted Channel halted. If the halted channel is the
		 * instances's, we set the instance's channel to -1.
		 */
		void onChannelHalt(int channelHalted);
	};
}

#endif // RB_SDL

#endif
