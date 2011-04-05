/**
 * @file
 * @ingroup Input
 */
#ifndef RB_GAME_PAD_THUMBSTICK_SIGNAL_DATA_H
#define RB_GAME_PAD_THUMBSTICK_SIGNAL_DATA_H

#include "GamePadSignalData.h"

namespace RedBox {
	/**
	 * Contains data needed by slots that listen to signals sent by the game pad
	 * when a thumbstick is moved.
	 * @ingroup Input
	 */
	class GamePadThumbstickSignalData : public GamePadSignalData {
	public:
		/**
		 * Parameterizable constructor.
		 * @param newGamePadState State of the game pad that sent the signal.
		 * @param newThumbstickIndex Index of the thumbstick concerned by the
		 * signal.
		 */
		GamePadThumbstickSignalData(const GamePadState& newGamePadState,
									unsigned int newThumbstickIndex);
		
		/**
		 * Destructor.
		 */
		~GamePadThumbstickSignalData();
		
		/// Index of the thumbstick concerned by the signal.
		const unsigned int thumbstickIndex;
	};
}

#endif