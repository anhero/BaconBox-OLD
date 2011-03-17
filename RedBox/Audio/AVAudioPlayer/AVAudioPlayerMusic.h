/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_AV_AUDIO_PLAYER_MUSIC_H
#define RB_AV_AUDIO_PLAYER_MUSIC_H

#include <string>

#include "BackgroundMusic.h"

namespace RedBox {
	/**
	 * Represents a music that can be manipulated. Implementation of 
	 * BackgroundMusic for iOS.
	 * @ingroup Audio
	 */
	class AVAudioPlayerMusic : public BackgroundMusic {
		friend class AVAudioPlayerEngine;
	public:
		/**
		 * Plays the music a given number of times.
		 * @param nbTimes Number of times the sound will be played in loop. A
		 * negative number is for infinite looping.
		 */
		void play(int nbTimes = -1);
		/**
		 * Stops the music. Cannot be resumed and next time it will be played
		 * it will start from the beginning.
		 */
		void stop();
		/**
		 * Pauses the music. Remembers where it was paused so it can resume when
		 * calling the resume method.
		 */
		void pause();
		/**
		 * Resumes the music. Will only resume if the music has been paused.
		 */
		void resume();
		/**
		 * Checks if the music is currently playing infinitely.
		 * @return True if the music is currently looping infinitely.
		 */
		bool isLooping();
		/**
		 * Gets the music's current state. Used to know if it is at its initial
		 * state, currently playing, paused or stopped.
		 * @return Sound effect's current state.
		 * @see RedBox::AudioState::Enum
		 */
		AudioState::Enum getCurrentState();
		/**
		 * Destructor. Does not delete the music data, only the music source.
		 * This is done to be able to have many musics playing the same
		 * music without having it loaded many times in memory.
		 */
		~AVAudioPlayerMusic();
	private:
		/**
		 * Default constructor. Can only be called by the audio engine.
		 */
		AVAudioPlayerMusic();
		/**
		 * Loads a background music.
		 * @param filePath Path to the music file to load.
		 */
		void load(const std::string& filePath);
	};
}

#endif