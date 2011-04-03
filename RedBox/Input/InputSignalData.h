/**
 * @file
 * @ingroup Input
 */
#ifndef RB_INPUT_SIGNAL_DATA_H
#define RB_INPUT_SIGNAL_DATA_H

#include "SignalData.h"

namespace RedBox {
	/**
	 * Contains data for signals sent by input devices.
	 * @ingroup Input
	 */
	class InputSignalData : public SignalData {
	public:
		/**
		 * Default constructor.
		 */
		InputSignalData();
		/**
		 * Destructor.
		 */
		virtual ~InputSignalData();
	};
}

#endif