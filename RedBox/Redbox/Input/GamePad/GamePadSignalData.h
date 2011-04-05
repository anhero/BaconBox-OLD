/**
 * @file
 * @ingroup Input
 */
#ifndef RB_GAME_PAD_SIGNAL_DATA_H
#define RB_GAME_PAD_SIGNAL_DATA_H

#include "InputSignalData.h"
#include "GamePadState.h"

namespace RedBox {
	/**
	 * Base class that contains data needed by slots that listen to signals
	 * sent by a gamepad.
	 * @ingroup Input
	 */
	class GamePadSignalData : public InputSignalData {
	public:
		/**
		 * Parameterized constructor.
		 * @param newGamePadState State of the game pad that sent the signal.
		 */
		GamePadSignalData(const GamePadState& newGamePadState);
		
		/**
		 * Destructor.
		 */
		virtual ~GamePadSignalData();
		
		/// Reference to the state of the game pad that sent the signal.
		const GamePadState& gamePadState;
	};
}

#endif