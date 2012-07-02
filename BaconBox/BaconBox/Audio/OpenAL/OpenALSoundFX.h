/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_OPENAL_SOUNDFX_H
#define RB_OPENAL_SOUNDFX_H

#include "BaconBox/PlatformFlagger.h"

#include <vector>

#include "BaconBox/Audio/OpenAL/RBOpenAL.h"
#include "BaconBox/Audio/SoundFX.h"

namespace BaconBox {
	/**
	 * Sound effect for the OpenAL sound engine.
	 * @ingroup Audio
	 */
	class OpenALSoundFX: public SoundFX {
		friend class OpenALEngine;
	public:
		/**
		 * Destructor.
		 */
		~OpenALSoundFX();
		
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
		 * Sets the sound effect's volume level.
		 * @param newVolume New volume level. If the new volume is out of
		 * bounds, it will be set to the closest bound (minimum if it's under 0
		 * or maximum if it's over 100).
		 * @see BaconBox::Sound::volume
		 */
		void setVolume(int newVolume);

		/**
		 * Gets the sound effect's current state. Queries OpenAL for the sound's
		 * current state.
		 * @return Sound effect's current state.
		 */
		AudioState getCurrentState() const;

        /**
         * Gets the sound effect's source ID.
         * @return Sound effect's source ID.
         * @see BaconBox::OpenALSoundFX::sourceId
         */
        ALuint& getSourceId();
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
