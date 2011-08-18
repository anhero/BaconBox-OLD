#include "IButton.h"

#include "Pointer.h"

using namespace RedBox;

IButton::IButton() : GraphicBody(), state(ButtonState::NORMAL), tmpHold(false) {
}

IButton::IButton(const IButton& src) : GraphicBody(src), state(src.state),
	tmpHold(false) {
}

IButton::~IButton() {
}

IButton& IButton::operator=(const IButton& src) {
	this->GraphicBody::operator=(src);

	if(this != &src) {
		state = src.state;
		tmpHold = src.tmpHold;
	}

	return *this;
}

void IButton::update() {
	this->GraphicBody::update();
	Pointer* ptr = Pointer::getDefault();

	// We make sure the pointer is initialized.
	if(ptr) {
		// If the cursor is over the button.
		if(AABB::overlaps(ptr->getPosition(), getAABB())) {
			switch(state.underlying()) {
				// If the button is currently in the normal state.
			case ButtonState::NORMAL:
				// It means the cursor just entered over the button.
				state = ButtonState::HOVER;
				onEnter();

				// If the user clicked at the exact same time it entered over
				// the button or if earlier the button was pressed on the
				// button, was held and then left the button just to later
				// re-enter over the button, we make it as if the button was
				// pressed.
				if(ptr->isButtonPressed(CursorButton::LEFT) ||
				   (tmpHold && ptr->isButtonHeld(CursorButton::LEFT))) {
					state = ButtonState::PRESSED;
					onPress();
				}

				break;

				// If the cursor was already hovering the button.
			case ButtonState::HOVER:

				// If the user presses the cursor button while over the button.
				if(ptr->isButtonPressed(CursorButton::LEFT)) {
					// We set the button to being pressed.
					state = ButtonState::PRESSED;
					onPress();
				}

				break;

				// If the button is currently pressed.
			case ButtonState::PRESSED:

				// If the user releases the cursor.
				if(ptr->isButtonReleased(CursorButton::LEFT)) {
					// We set the button back to its normal state.
					tmpHold = false;
					state = ButtonState::HOVER;
					onRelease();

				} else if(ptr->isButtonHeld(CursorButton::LEFT)) {
					// The cursor is currently being held down.
					onHold();
				}

				break;

			default:
				break;
			}

		} else {
			switch(state.underlying()) {
			case ButtonState::NORMAL:

				// If the button is on temporary hold and
				if(tmpHold && ptr->isButtonReleased(CursorButton::LEFT)) {
					tmpHold = false;
				}

				break;

			case ButtonState::HOVER:
				// If the button was currently hovered, it means the cursor
				// just left the button and wasn't pressed.
				state = ButtonState::NORMAL;
				onLeave();
				break;

			case ButtonState::PRESSED:

				// If the button was currently held and the cursor left the
				// button while still holding the left cursor button down.
				if(ptr->isButtonHeld(CursorButton::LEFT)) {
					tmpHold = true;
					state = ButtonState::NORMAL;
					onLeave();
				}

				break;

			default:
				break;
			}
		}
	}
}

ButtonState IButton::getState() const {
	return state;
}
