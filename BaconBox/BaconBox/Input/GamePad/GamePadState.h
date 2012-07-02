/**
 * @file
 * @ingroup Input
 */
#ifndef RB_GAME_PAD_STATE_H
#define RB_GAME_PAD_STATE_H

#include <vector>
#include <utility>

#include "BaconBox/Input/InputState.h"
#include "BaconBox/Vector2.h"

namespace BaconBox {
	/**
	 * Represents a game pad's buttons' and analogs' state.
	 * @ingroup Input
	 */
	class GamePadState : public InputState {
		friend class GamePad;
	public:
		/**
		 * Default constructor.
		 */
		GamePadState();
		
		/**
		 * Destructor.
		 */
		~GamePadState();
		
		/**
		 * Gets a button's state.
		 * @return Value representing the pressure applied on the button. 0.0
		 * means it isn't being pressed, 1.0 is when it is fully pressed or
		 * if on a non-analog game pad, 1.0 is when it is simply pressed
		 * (whatever the pressure applied on the button.
		 */
		float getButton(unsigned int buttonIndex) const;
		/**
		 * Gets a button's previous state.
		 * @return Value representing the pressure applied on the button. 0.0
		 * means it isn't being pressed, 1.0 is when it is fully pressed or
		 * if on a non-analog game pad, 1.0 is when it is simply pressed
		 * (whatever the pressure applied on the button.
		 */
		float getPreviousButton(unsigned int buttonIndex) const;
		
		/**
		 * Gets a thumbstick's state.
		 * @return 2-dimensional vector containing the horizontal and vertical
		 * values of the thumbstick's position.
		 */
		const float getThumbstick(unsigned int thumbstickIndex) const;
        
        void init(unsigned int nbOfButtons, unsigned int nbOfThumbstick);
	private:
        
        
        bool isButtonPressed(unsigned int buttonIndex) const;
        bool isButtonHeld(unsigned int buttonIndex) const;
        bool isButtonReleased(unsigned int buttonIndex) const;
        
		/**
		 * Vector containing buttons' status. Values represent the pressure
		 * applied on the button. 0.0 means it isn't being pressed, 1.0 is when
		 * it is fully pressed or if on a non-analog game pad, 1.0 is when it is
		 * simply pressed (whatever the pressure applied on the button.
		 */
		std::vector<float> buttons;
		/**
		 * Buttons' state from the last game pad update.
		 */
		std::vector<float> previousButtons;
		/**
		 * Vector containing values for the thumbsticks' position.
		 */
		std::vector<float> thumbsticks;
        std::vector<float> previousThumbsticks;

	};
}

#endif
