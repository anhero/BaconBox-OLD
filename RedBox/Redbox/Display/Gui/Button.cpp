#include "Button.h"

#include "Pointer.h"
#include "Engine.h"

namespace RedBox {
	Button::Button() : Sprite(), click(), hover(),
		buttonState(ButtonState::NORMAL), tmpHold(false) {
	}

	Button::Button(TexturePointer newTexture,
	               const Vector2 &startingPosition,
	               const Vector2 &newSize,
	               const Vector2 &newTextureOffset,
	               unsigned int nbFrames) :
		Sprite(newTexture, startingPosition, newSize, newTextureOffset,
		       nbFrames), click(), hover(), buttonState(ButtonState::NORMAL),
		tmpHold(false) {
	}

	Button::Button(const Button &src) : Sprite(src), click(src.click),
		hover(src.hover), buttonState(src.buttonState), tmpHold(src.tmpHold) {
	}

	Button::~Button() {
	}

	Button &Button::operator=(const Button &src) {
		this->Sprite::operator=(src);

		if (this != &src) {
			click = src.click;
			hover = src.hover;
			buttonState = src.buttonState;
			tmpHold = src.tmpHold;
		}

		return *this;
	}

	void Button::update() {
		Pointer *ptr = Pointer::getDefault();

		// We make sure the pointer is initialized.
		if (ptr) {
			// If the cursor is over the button.
			if (this->getAxisAlignedBoundingBox().overlaps(Engine::getCurrentState()->getCamera().screenToWorld(ptr->getPosition()))) {
				switch (buttonState.underlying()) {
					// If the button is currently in the normal state.
				case ButtonState::NORMAL:
					// It means the cursor just entered over the button.
					buttonState = ButtonState::HOVER;
					onEnter();

					// If the user clicked at the exact same time it entered over
					// the button or if earlier the button was pressed on the
					// button, was held and then left the button just to later
					// re-enter over the button, we make it as if the button was
					// pressed.
					if (ptr->isButtonPressed(CursorButton::LEFT) ||
					    (tmpHold && ptr->isButtonHeld(CursorButton::LEFT))) {
						buttonState = ButtonState::PRESSED;
						onPress();
					}

					break;

					// If the cursor was already hovering the button.
				case ButtonState::HOVER:

					// If the user presses the cursor button while over the button.
					if (ptr->isButtonPressed(CursorButton::LEFT)) {
						// We set the button to being pressed.
						buttonState = ButtonState::PRESSED;
						onPress();
					}

					break;

					// If the button is currently pressed.
				case ButtonState::PRESSED:

					// If the user releases the cursor.
					if (ptr->isButtonReleased(CursorButton::LEFT)) {
						// We set the button back to its normal state.
						tmpHold = false;
						buttonState = ButtonState::HOVER;
						onRelease();

					} else if (ptr->isButtonHeld(CursorButton::LEFT)) {
						// The cursor is currently being held down.
						onHold();
					}

					break;

				default:
					break;
				}

			} else {
				switch (buttonState.underlying()) {
				case ButtonState::NORMAL:

					// If the button is on temporary hold and
					if (tmpHold && ptr->isButtonReleased(CursorButton::LEFT)) {
						tmpHold = false;
					}

					break;

				case ButtonState::HOVER:
					// If the button was currently hovered, it means the cursor
					// just left the button and wasn't pressed.
					buttonState = ButtonState::NORMAL;
					onLeave();
					break;

				case ButtonState::PRESSED:

					// If the button was currently held and the cursor left the
					// button while still holding the left cursor button down.
					if (ptr->isButtonHeld(CursorButton::LEFT)) {
						tmpHold = true;
						buttonState = ButtonState::NORMAL;
						onLeave();
					}

					break;

				default:
					break;
				}
			}
		}
	}

	ButtonState Button::getButtonState() const {
		return buttonState;
	}
}
