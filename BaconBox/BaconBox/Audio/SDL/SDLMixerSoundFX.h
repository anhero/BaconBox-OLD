/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SDL_MIXER_SOUNDFX_H
#define RB_SDL_MIXER_SOUNDFX_H

#include "BaconBox/PlatformFlagger.h"

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <sigly.h>

#include "BaconBox/Audio/SoundFX.h"

namespace BaconBox {
	/**
	 * SDL_mixer implementation for sound effects. A sound effect is
	 * associated with a Mix_Chunk pointer. When playing, it gets associated
	 * with a sound channel until the sound is done playing.
	 * @ingroup Audio
	 */
	class SDLMixerSoundFX : public SoundFX, public sigly::HasSlots<> {
		friend class SDLMixerEngine;
		friend class sigly::Signal1<int>;
		friend class sigly::Signal0<>;
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
		 * Sets the sound effect's volume level.
		 * @param newVolume New volume level. If the new volume is out of
		 * bounds, it will be set to the closest bound (minimum if it's under 0
		 * or maximum if it's over 100).
		 * @see BaconBox::Sound::volume
		 */
		void setVolume(int newVolume);

		/**
		 * Gets the sound's current state. Used to know if it is at its initial
		 * state, currently playing, paused, etc.
		 * @return Sound's current state.
		 * @see BaconBox::AudioState
		 */
		AudioState getCurrentState() const;
		/**
		 * Destructor.
		 */
		~SDLMixerSoundFX();
	private:
		/// Constant used to signify infinite looping.
		static const int LOOPING = -1;

		/// Contant used to signify an invalid or automatic sound channel.
		static const int INVALID_CHANNEL = -1;

		/// Signal sent when a channel is done.
		static sigly::Signal1<int> haltChannel;

		/// Set to true if the sound effect is currently looping infinitely.
		bool looping;

		/// Number of the channel the sound is being played on.
		int channel;

		/// Pointer to the sound's data.
		Mix_Chunk* data;

		/// Set to false until the sound has played at least once.
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

		/**
		 * Called when the global sound volume is changed.
		 */
		void soundVolumeChanged();

		/**
		 * Refreshes the volume on the sound effect's channel.
		 */
		void refreshVolume(int newVolume);
	};
}

#endif
