/**
 * @file
 * @ingroup Input
 */
#ifndef RB_ACCELEROMETER_STATE_H
#define RB_ACCELEROMETER_STATE_H

#include "BaconBox/Input/InputState.h"

namespace BaconBox {
	/**
	 * Contains the information about the accelerometer.
	 * @ingroup Input
	 */
	class AccelerometerState : public InputState {
		friend class Accelerometer;
	public:
		/**
		 * Default constructor.
		 */
		AccelerometerState();
		
		/**
		 * Destructor.
		 */
		~AccelerometerState();
		
		/**
		 * Gets the x acceleration.
		 * @return X acceleration.
		 */
		float getXAcceleration() const;
		
		/**
		 * Gets the y acceleration.
		 * @return Y acceleration.
		 */
		float getYAcceleration() const;
		
		/**
		 * Gets the z acceleration.
		 * @return Z acceleration.
		 */
		float getZAcceleration() const;
	private:
		/// Initial acceleration values.
		static const float STARTING_ACCELERATION;
		
		/// Accelerometer's x acceleration.
		float xAcceleration;
		
		/// Accelerometer's y acceleration.
		float yAcceleration;
		
		/// Accelerometer's z acceleration.
		float zAcceleration;
	};
}

#endif
