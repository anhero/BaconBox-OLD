/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_AUDIO_STATE_H
#define RB_AUDIO_STATE_H

#include "SafeEnum.h"

namespace RedBox {
	/**
	 * Represents the state of a sound effect or a background music. When one is
	 * created and initialized, it is at INITIAL. When it is currently playing,
	 * it is at PLAYING. When paused is called on a playing sound effect or
	 * music, it set at PAUSED. When a sound is done being played, it is set at
	 * STOPPED.
	 */
	struct AudioStateDef {
		enum type {
			INITIAL,
			PLAYING,
			PAUSED,
			STOPPED,
			FADING_IN,
			FADING_OUT
		};
	};
	typedef SafeEnum<AudioStateDef> AudioState;
}

#endif
