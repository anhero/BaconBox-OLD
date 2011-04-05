/**
 * @file
 * @ingroup Input
 */
#ifndef RB_ACCELEROMETER_SIGNAL_DATA_H
#define RB_ACCELEROMETER_SIGNAL_DATA_H

#include "InputSignalData.h"
#include "AccelerometerState.h"

namespace RedBox {
	/**
	 * Contains the data needed by slots that listen to the accelerometer(s)'s
	 * signals.
	 * @ingroup Input
	 */
	class AccelerometerSignalData : public InputSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newAccelerometerState State of the accelerometer device that
		 * is sending the signal.
		 */
		AccelerometerSignalData(const AccelerometerState& newAccelerometerState);
		
		/**
		 * Destructor.
		 */
		~AccelerometerSignalData();
		
		/// State of the accelerometer device that sent the signal.
		const AccelerometerState& accelerometerState;
	};
}

#endif