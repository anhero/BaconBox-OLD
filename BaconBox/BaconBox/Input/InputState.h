/**
 * @file
 * @ingroup Input
 */
#ifndef RB_INPUT_STATE_H
#define RB_INPUT_STATE_H

namespace BaconBox {
	/**
	 * Base class for all input devices' state information. Which are also used
	 * as signal data for its concerned device.
	 * @ingroup Input
	 */
	class InputState {
	public:
		/**
		 * Default constructor.
		 */
		InputState();
		/**
		 * Destructor.
		 */
		virtual ~InputState();
	};
}

#endif
