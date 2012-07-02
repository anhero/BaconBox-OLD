/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_AV_AUDIO_PLAYER_MUSIC_H
#define RB_AV_AUDIO_PLAYER_MUSIC_H

#include "BaconBox/PlatformFlagger.h"

#include <string>

#include "BaconBox/Audio/ios/RBAudioPlayerMusicDelegate.h"
#include <Foundation/Foundation.h>

#include "BaconBox/Audio/AudioState.h"
#include "BaconBox/Audio/BackgroundMusic.h"

namespace BaconBox {
	/**
	 * Represents a music that can be manipulated. Implementation of 
	 * BackgroundMusic for iOS.
	 * @ingroup Audio
	 */
	class RBAudioPlayerMusic : public BackgroundMusic {
		friend class RBAudioPlayerEngine;
	public:
		/**
		 * Plays the music a given number of times.
		 * @param nbTimes Number of times the music will be played in loop. A
		 * negative number is for infinite looping.
		 */
		void play(int nbTimes = -1);
		/**
		 * Same as the usual play method, but with a fade in effect.
		 * @param nbTimes Number of times the music will be played in loop. A
		 * negative number is for infinite looping.
		 * @param fadeIn Time the fade in effect will last (in seconds).
		 */
		void play(int nbTimes, double fadeIn = 0.0);
		/**
		 * Stops the music. Cannot be resumed and next time it will be played
		 * it will start from the beginning.
		 */
		void stop();
		/**
		 * Same as the usual stop method, but with a fade out effect.
		 * @param fadeOut Time the fade out effect will last (in seconds).
		 */
		void stop(double fadeOut);
		/**
		 * Pauses the music. Remembers where it was paused so it can resume when
		 * calling the resume method.
		 */
		void pause();
		/**
		 * Same as the usual pause method, but with a fade out effect.
		 * @param fadeOut Time the fade out effect will last (in seconds).
		 */
		void pause(double fadeOut);
		/**
		 * Resumes the music. Will only resume if the music has been paused.
		 */
		void resume();
		/**
		 * Same as the usual resume method, but with a fade in effect.
		 * @param fadeIn Time the fade in effect will last (in seconds).
		 */
		void resume(double fadeIn);
		/**
		 * Checks if the music is currently playing infinitely.
		 * @return True if the music is currently looping infinitely.
		 */
		bool isLooping();
		
		/**
		 * Sets the music's volume level.
		 * @param newVolume New volume level. If the new volume is out of
		 * bounds, it will be set to the closest bound (minimum if it's under 0
		 * or maximum if it's over 100).
		 * @see BaconBox::Sound::volume
		 */
		void setVolume(int newVolume);
		
		/**
		 * Gets the music's current state. Used to know if it is at its initial
		 * state, currently playing, paused or stopped.
		 * @return Sound effect's current state.
		 * @see BaconBox::AudioState
		 */
		AudioState getCurrentState() const;
		/**
		 * Destructor. Does not delete the music data, only the music source.
		 * This is done to be able to have many musics playing the same
		 * music without having it loaded many times in memory.
		 */
		~RBAudioPlayerMusic();
	private:
		/// Pointer to the music being currently played.
		static RBAudioPlayerMusic* currentMusic;
		/// Pointer to the objective-C background music.
		RBAudioPlayerMusicDelegate* bgm;
		/// Used to keep track if the music is at the INITIAL state.
		bool playedOnce;
		
		/**
		 * Refreshes the volume taking into account the global music volume.
		 */
		static void refreshVolume();
		/**
		 * Default constructor. Can only be called by the audio engine.
		 */
		RBAudioPlayerMusic();
		/**
		 * Loads a background music.
		 * @param filePath Path to the music file to load.
		 */
		void load(const std::string& filePath);
	};
}
#endif
