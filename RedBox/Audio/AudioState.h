/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_AUDIO_STATE_H
#define RB_AUDIO_STATE_H

namespace RedBox {
	/**
	 * Represents the state of a sound effect or a background music. When one is
	 * created and initialized, it is at INITIAL. When it is currently playing,
	 * it is at PLAYING. When paused is called on a playing sound effect or
	 * music, it set at PAUSED. When a sound is done being played, it is set at
	 * STOPPED.
	 */
	namespace AudioState {
		enum Enum {
			INITIAL,
			PLAYING,
			PAUSED,
			STOPPED
		};
	}
}

#endif