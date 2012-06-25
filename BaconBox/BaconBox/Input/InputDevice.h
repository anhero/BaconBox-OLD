/**
 * @file
 * @ingroup Input
 */
#ifndef RB_INPUT_DEVICE_H
#define RB_INPUT_DEVICE_H

namespace BaconBox {
	/**
	 * Base class for all input devices.
	 * @ingroup Input
	 */
	class InputDevice {
		friend class InputManager;
	protected:
		/**
		 * Default constructor.
		 */
		InputDevice();
		
		/**
		 * Destructor.
		 */
		virtual ~InputDevice();
		/**
		 * Abstract update method. This will be called to update the device's
		 * state.
		 */
		virtual void updateDevice();
	};
}

#endif
