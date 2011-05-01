/**
 * @file
 * @input
 */
#ifndef RB_GAME_PAD_RB
#define RB_GAME_PAD_RB

#include <sigly.h>

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
		friend class InputManager;
	public:
		/// Signal sent when a buton is pressed down.
		sigly::Signal1<GamePadButtonSignalData> buttonPress;
		
		/// Signal sent when a button is being held.
		sigly::Signal1<GamePadButtonSignalData> buttonHold;
		
		/// Signal sent when a button is released.
		sigly::Signal1<GamePadButtonSignalData> butonRelease;
		
		/// Signal sent when a thumbstick is moved.
		sigly::Signal1<GamePadThumbstickSignalData> thumbstickMove;
		
		/**
		 * Gets a pointer to the default gamepad device.
		 * @return Pointer to the default gamepad device. Null if none are
		 * available.
		 */
		static GamePad* getDefault();

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
