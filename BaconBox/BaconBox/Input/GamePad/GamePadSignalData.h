/**
 * @file
 * @ingroup Input
 */
#ifndef RB_GAME_PAD_SIGNAL_DATA_H
#define RB_GAME_PAD_SIGNAL_DATA_H

#include "BaconBox/Input/InputSignalData.h"
#include "BaconBox/Input/GamePad/GamePadState.h"

namespace BaconBox {
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
		 * @param gamePadIndex Index of the game pad.
		 */
		GamePadSignalData(const GamePadState &newGamePadState,
		                  unsigned int gamePadIndex);

		/**
		 * Destructor.
		 */
		virtual ~GamePadSignalData();

		/// Reference to the state of the game pad that sent the signal.
		const GamePadState &gamePadState;


		const unsigned int gamePadIndex;
	};
}

#endif
