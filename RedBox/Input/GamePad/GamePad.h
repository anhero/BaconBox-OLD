/**
 * @file
 * @input
 */
#ifndef RB_GAME_PAD_RB
#define RB_GAME_PAD_RB

#include <sigly/sigly.h>

#include "InputDevice.h"
#include "GamePadState.h"
#include "GamePadButtonSignalData.h"
#include "GamePadThumbstickSignalData.h"

namespace RedBox {
	/**
	 * Represents a game pad device.
	 * @ingroup Input
	 */
	class GamePad : public InputDevice {
	public:
		/// Signal sent when a buton is pressed down.
		sigly::Signal1<GamePadButtonSignalData> buttonDown;
		
		/// Signal sent when a button is released.
		sigly::Signal1<GamePadButtonSignalData> buttonUp;
		
		/// Signal sent when a button is being held.
		sigly::Signal1<GamePadButtonSignalData> buttonHold;
		
		/// Signal sent when a thumbstick is moved.
		sigly::Signal1<GamePadThumbstickSignalData> thumbstickMove;
		
		/**
		 * Gets the game pad's state containing the buttons' and the 
		 * thumbsticks' state.
		 * @return Game pad's state.
		 */
		const GamePadState& getState() const;
	protected:
		/// Contains the game pad's buttons' and thumbstick' state.
		GamePadState state;
		
		/**
		 * Default constructor.
		 */
		GamePad();
		
		/**
		 * Destructor.
		 */
		virtual ~GamePad();
	};
}

#endif
