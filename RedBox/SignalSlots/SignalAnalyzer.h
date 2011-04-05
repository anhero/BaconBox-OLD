/**
 * @file
 * @ingroup Events
 */
#ifndef RB_SIGNAL_ANALYZER_H
#define RB_SIGNAL_ANALYZER_H

#include <sigly.h>

namespace RedBox {
	/**
	 * Used for analyzing signals to generate higher level complex signals. Used
	 * to provide high-level signals. For example, implementing a swipe or a
	 * pinch signal for a multi-touch interface, it would be done by writing a
	 * signal analyzer inheriting from this class. The said analyzer would have
	 * slots listening to the needed events to produce the higher level signal.
	 * For example, a signal analyzer for a swipe would listen to Pointer events
	 * and would shoot a swipe signal when needed.
	 * @ingroup Events
	 */
	class SignalAnalyzer : public sigly::HasSlots<> {
	public:
		/**
		 * Default constructor.
		 */
		SignalAnalyzer();
		/**
		 * Destructor.
		 */
		virtual ~SignalAnalyzer();
	};
}

#endif
