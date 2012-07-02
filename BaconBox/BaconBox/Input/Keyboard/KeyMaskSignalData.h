/**
 * @file
 * @ingroup Input
 */
#ifndef RB_KEY_MASK_SIGNAL_DATA_H
#define RB_KEY_MASK_SIGNAL_DATA_H

#include <string>

#include "BaconBox/Input/Keyboard/KeyboardSignalData.h"

namespace BaconBox {
	/**
	 * Contains data about a signal sent by a keyboard when a key mask is either
	 * pressed, released or held.
	 * @ingroup Input
	 */
	class KeyMaskSignalData : public KeyboardSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newKeyboardState State of the keyboard that sent the signal.
		 * @param newMaskName Name of the mask that is concerned by the signal.
		 */
		KeyMaskSignalData(const KeyboardState& newKeyboardState,
						  const std::string& newMaskName);
		
		/**
		 * Destructor.
		 */
		~KeyMaskSignalData();
		
		/// Name of the mask concerned by the signal.
		const std::string& maskName;
	};
}

#endif
