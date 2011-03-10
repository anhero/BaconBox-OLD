/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_OPENAL_SOUNDFX_H
#define RB_OPENAL_SOUNDFX_H

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
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
		 * Gets if the sound effect needs to survive after being played.
		 * @return True if it needs to survive, false if not.
		 */
		bool getSurvives() const;
		/**
		 * Sets if the sound effect needs to survive after being played.
		 * @param newSurvives New value, true if it needs to survive, false if
		 * not.
		 */
		void setSurvives(bool newSurvives);
		/**
		 * Get the sound effect's assigned source ID.
		 * @return Sound effect's assigned source ID.
		 */
		ALuint& getSourceId();
	private:
		/// OpenAL ID of the sound source.
		ALuint sourceId;
		/// Used to know if the engine deletes the sound effect when done.
		bool survives;
		
		/**
		 * Default constructor.
		 */
		OpenALSoundFX();
		/**
		 * Destructor.
		 */
		~OpenALSoundFX();
		/**
		 * Loads a sound effect from a file.
		 * @param filePath Path to the file to load.
		 */
		void load(ALuint bufferId, char* bufferData);
	};
}

#endif