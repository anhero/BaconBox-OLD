/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_OPENAL_SOUNDFX_H
#define RB_OPENAL_SOUNDFX_H

#include "PlatformFlagger.h"

#ifdef RB_WIN32
#include <al.h>
#include <alc.h>
#else
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif
#include <vector>

#include "SoundFX.h"

namespace RedBox {
	/**
	 * Sound effect for the OpenAL sound engine.
	 * @ingroup Audio
	 */
	class OpenALSoundFX: public SoundFX {
		friend class OpenALEngine;
	public:
		/**
		 * Plays the sound effect a given number of times.
		 * @param nbTimes Number of times to play the sound effect. Negative
		 * number for infinite playing.
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
		 * Checks if the sound effect is currently looping.
		 * @return Sound source's looping property (true if looping, false if
		 * not).
		 */
		bool isLooping();
		/**
		 * Gets the sound effect's current state. Queries OpenAL for the sound's
		 * current state.
		 * @return Sound effect's current state.
		 */
		AudioState::Enum getCurrentState();
		/**
		 * Destructor.
		 */
		~OpenALSoundFX();
	private:
		/// OpenAL ID of the sound source.
		ALuint sourceId;
		/// Used to know if the engine deletes the sound effect when done.
		bool survives;
		/**
		 * Number of times left to play. It's used for counting the number of
		 * loops.
		 */
		int nbTimesLeft;
		
		/**
		 * Default constructor.
		 */
		OpenALSoundFX();
		/**
		 * Loads a sound effect from a buffer.
		 * @param bufferId ID of the buffer to play.
		 */
		void load(ALuint bufferId);
	};
}

#endif