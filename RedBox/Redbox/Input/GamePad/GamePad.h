/**
 * @file
 * @ingroup Input
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
		sigly::Signal1<GamePadButtonSignalData> buttonRelease;
		
		/// Signal sent when a thumbstick is moved.
		sigly::Signal1<GamePadThumbstickSignalData> thumbstickMove;
		
		/**
		 * Connect a function callback to the buttonPress signal.
		 * @param pclass Pointer to the instance concerned by the signal.
		 * @param pmemfun Pointer to the function to call.
		 */
		template <class desttype>
		static void connectButtonPress(desttype* pclass, void (desttype::*pmemfun)(GamePadButtonSignalData)) {
			GamePad* gamePad = getDefault();
			if(gamePad) {
				gamePad->buttonPress.connect(pclass, pmemfun);
			}
		}

		/**
		 * Connect a function callback to the buttonHold signal.
		 * @param pclass Pointer to the instance concerned by the signal.
		 * @param pmemfun Pointer to the function to call.
		 */
		template <class desttype>
		static void connectButtonHold(desttype* pclass, void (desttype::*pmemfun)(GamePadButtonSignalData)) {
			GamePad* gamePad = getDefault();
			if(gamePad) {
				gamePad->buttonHold.connect(pclass, pmemfun);
			}
		}

		/**
		 * Connect a function callback to the buttonRelease signal.
		 * @param pclass Pointer to the instance concerned by the signal.
		 * @param pmemfun Pointer to the function to call.
		 */
		template <class desttype>
		static void connectButtonRelease(desttype* pclass, void (desttype::*pmemfun)(GamePadButtonSignalData)) {
			GamePad* gamePad = getDefault();
			if(gamePad) {
				gamePad->buttonRelease.connect(pclass, pmemfun);
			}
		}

		/**
		 * Connect a function callback to the thumbstickMove signal.
		 * @param pclass Pointer to the instance concerned by the signal.
		 * @param pmemfun Pointer to the function to call.
		 */
		template <class desttype>
		static void connectThumbStickMove(desttype* pclass, void (desttype::*pmemfun)(GamePadThumbstickSignalData)) {
			GamePad* gamePad = getDefault();
			if(gamePad) {
				gamePad->thumbstickMove.connect(pclass, pmemfun);
			}
		}

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

		/**
		 * Abstract update method. This will be called to update the device's
		 * state.
		 */
		virtual void updateDevice();
	};
}

#endif
