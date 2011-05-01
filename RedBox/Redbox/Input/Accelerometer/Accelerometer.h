/**
 * @file
 * @ingroup Input
 */
#ifndef RB_ACCELEROMETER_H
#define RB_ACCELEROMETER_H

#include <sigly.h>

#include "InputDevice.h"
#include "AccelerometerSignalData.h"
#include "AccelerometerState.h"

namespace RedBox {
	/**
	 * Represents an accelerometer device. Can be activated or deactivated at
	 * will because it can use up a lot of battery on some platforms.
	 * @ingroup Input
	 */
	class Accelerometer : public InputDevice {
		friend class InputManager;
	public:
		/**
		 * Signal sent when the accelerometer's values change, which happens
		 * very frequently (pretty close to every update).
		 */
		sigly::Signal1<AccelerometerSignalData> change;
		
		/**
		 * Gets a pointer to the default accelerometer device.
		 * @return Pointer to the default accelerometer device. Null if none are
		 * available.
		 */
		static Accelerometer* getDefault();

		/**
		 * Activates the signal sending when the accelerometer's value are
		 * updated.
		 */
		void activateSignals();
		
		/**
		 * Deactivates the signal sending when the accelerometer's value are
		 * updated.
		 */
		void deactivateSignals();
		
		/**
		 * Checks if the signal emitting is active or not.
		 * @return True if the accelerometer is emitting signals, false if not.
		 */
		bool areSignalsActive() const;
		
		/**
		 * Activates the updating of the accelerometer. When activated, the
		 * accelerometer fetches data about it at every update.
		 */
		void activate();
		
		/**
		 * Deactivates the updating of the accelerometer. When deactivated, the
		 * acceleration values of the accelerometer's state are never updated.
		 */
		void deactivate();
		
		/**
		 * Checks if the accelerometer is active.
		 * @return True if the accelerometer is updating its acceleration
		 * values, false if not.
		 */
		bool isActive() const;
		
		/**
		 * Gets the accelerometer's state.
		 * @return Accelerometer's state containing its acceleration values.
		 */
		const AccelerometerState& getState() const;
	protected:
		
		/// Accelerometer's state containing its acceleration values (x, y z).
		AccelerometerState state;
		
		/**
		 * Default constructor.
		 */
		Accelerometer();
		
		/**
		 * Destructor.
		 */
		virtual ~Accelerometer();
		
	private:
		
		/**
		 * Is set at true if the accelerometer is actively updating its
		 * acceleration values.
		 */
		bool active;
		
		/**
		 * Is set to true if the accelerometer is sending signals each time it
		 * updates its acceleration values.
		 */
		bool signalsActive;
	};
}

#endif
