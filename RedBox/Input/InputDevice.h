/**
 * @file
 * @ingroup Input
 */
#ifndef RB_INPUT_DEVICE_H
#define RB_INPUT_DEVICE_H

namespace RedBox {
	/**
	 * Base class for all input devices.
	 * @ingroup Input
	 */
	class InputDevice {
	public:
		/**
		 * Default constructor.
		 */
		InputDevice();

		/**
		 * Destructor.
		 */
		virtual ~InputDevice();
	protected:
		/**
		 * Abstract update method. This will be called to update the device's
		 * state.
		 */
		virtual void update() = 0;
	};
}

#endif