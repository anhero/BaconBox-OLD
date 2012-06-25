/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SOUNDFX_H
#define RB_SOUNDFX_H

#include "Sound.h"

namespace BaconBox {
	/**
	 * Abstract class for sound effects. Used by engine specific classes for
	 * sound effects.
	 * @ingroup Audio
	 */
	class SoundFX : public Sound {
		friend class AudioEngine;
	public:
		/**
		 * Destructor.
		 */
		virtual ~SoundFX();
	protected:
		/**
		 * Default constructor. Can only be called by the sound engine.
		 */
		SoundFX();
	};
}

#endif // RB_SOUNDFX_H
