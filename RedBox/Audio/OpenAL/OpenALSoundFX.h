/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_OPENAL_SOUNDFX_H
#define RB_OPENAL_SOUNDFX_H

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <vector>

#include "OpenALEngine.h"
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
		 * @param nbTimes Number of times to play the sound effect. -1 for 
		 * infinite playing.
		 */
		void play(int nbTimes = 1);
	private:
		/// State of the sound source.
		ALint state;
		/// OpenAL sound buffer ID.
		ALuint bufferId;
		/// OpenAL sound source.
		ALuint sourceId;
		/// Sound data format.
		ALenum format;
		/// Frequency of the sound data.
		ALsizei freq;
		/// Sound buffer data.
		std::vector<char> bufferData;
		
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
		bool load(const std::string& filePath);
	};
}

#endif