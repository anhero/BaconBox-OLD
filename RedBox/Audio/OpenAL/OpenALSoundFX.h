/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_OPENAL_SOUNDFX_H
#define RB_OPENAL_SOUNDFX_H

#include "SoundFX.h"

namespace RedBox {
	/**
	 * Sound effect for the OpenAL sound engine.
	 * @ingroup Audio
	 */
	class OpenALSoundFX: public SoundFX {
	public:
		void play(int nbTimes = 1);
	private:
		OpenALSoundFX();
		~OpenALSoundFX();
	};
}

#endif