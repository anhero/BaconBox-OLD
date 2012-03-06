#include "Checkbox.h"

#include "TextureInformation.h"

namespace RedBox {
	Checkbox::Checkbox(TexturePointer newTexture,
	                   const Vector2 &startingPosition,
	                   const Vector2 &newSize,
	                   const Vector2 &newTextureOffset) : Button() {
		this->setPosition(startingPosition);
		this->setTextureInformation(newTexture);

		if (newSize.x > 0.0f && newSize.y > 0.0f) {
			this->construct(newSize, startingPosition, newTextureOffset, 8);
			this->initializeAnimations();

		} else if (this->getTextureInformation()) {
			this->construct(Vector2(static_cast<float>(this->getTextureInformation()->imageWidth / 8),
			                        static_cast<float>(this->getTextureInformation()->imageHeight)),
			                startingPosition, newTextureOffset, 8);
			this->initializeAnimations();
		}
	}

	Checkbox::Checkbox(const Checkbox &src) : Button(src), checked(src.checked) {
	}

	Checkbox::~Checkbox() {
	}

	Checkbox &Checkbox::operator=(const Checkbox &src) {
		this->Button::operator=(src);

		if (this != &src) {
			checked = src.checked;
		}

		return *this;
	}

	const TextureCoordinates &Checkbox::getCurrentTextureCoordinates() const {
		if (this->isActive()) {
			return this->Button::getCurrentTextureCoordinates();

		} else if (isChecked()) {
			return this->getFrames()[7];

		} else {
			return this->getFrames()[6];
		}
	}
	bool Checkbox::isChecked() const {
		return checked;
	}

	void Checkbox::setChecked(bool newChecked) {
		checked = newChecked;

		if (this->isActive()) {
			if (this->getButtonState() == ButtonState::NORMAL) {
				if (isChecked()) {
					this->startAnimation("cn");

				} else {
					this->startAnimation("n");
				}

			} else if (this->getButtonState() == ButtonState::HOVER) {
				if (isChecked()) {
					this->startAnimation("ch");

				} else {
					this->startAnimation("h");
				}

			} else if (this->getButtonState() == ButtonState::PRESSED) {
				if (isChecked()) {
					this->startAnimation("cp");

				} else {
					this->startAnimation("p");
				}
			}

		} else {
			if (isChecked()) {
				this->startAnimation("cd");

			} else {
				this->startAnimation("d");
			}
		}
	}

	void Checkbox::check() {
		setChecked(true);
	}

	void Checkbox::uncheck() {
		setChecked(false);
	}

	void Checkbox::toggleChecked() {
		setChecked(!isChecked());
	}

	void Checkbox::onPress() {
		if (isChecked()) {
			this->startAnimation("cp");

		} else {
			this->startAnimation("p");
		}
	}

	void Checkbox::onHold() {
	}

	void Checkbox::onRelease() {
		toggleChecked();

		if (isChecked()) {
			this->startAnimation("ch");

		} else {
			this->startAnimation("h");
		}

		click();
	}

	void Checkbox::onEnter() {
		if (isChecked()) {
			this->startAnimation("ch");

		} else {
			this->startAnimation("h");
		}

		hover();
	}

	void Checkbox::onLeave() {
		if (isChecked()) {
			this->startAnimation("cn");

		} else {
			this->startAnimation("n");
		}
	}

	void Checkbox::initializeAnimations() {
		this->addAnimation("n", 0.0, 0, 1, 0);
		this->addAnimation("h", 0.0, 0, 1, 1);
		this->addAnimation("p", 0.0, 0, 1, 2);
		this->addAnimation("cn", 0.0, 0, 1, 3);
		this->addAnimation("ch", 0.0, 0, 1, 4);
		this->addAnimation("cp", 0.0, 0, 1, 5);
		this->addAnimation("d", 0.0, 0, 1, 6);
		this->addAnimation("cd", 0.0, 0, 1, 7);
	}
}
