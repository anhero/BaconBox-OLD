/**
 * @file
 * @ingroup Events
 */
#ifndef RB_SIGNAL_DATA_H
#define RB_SIGNAL_DATA_H

namespace BaconBox {
	/**
	 * Base class of all of the engine's signals to send the signal's
	 * information.
	 * @ingroup Events
	 */
	class SignalData {
	public:
		/**
		 * Default constructor.
		 */
		SignalData();
		/**
		 * Destructor.
		 */
		virtual ~SignalData();
	};
}

#endif
