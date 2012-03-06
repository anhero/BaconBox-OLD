#include "SimpleButton.h"

#include "TextureInformation.h"

namespace RedBox {
	SimpleButton::SimpleButton(TexturePointer newTexture,
	                           const Vector2 &startingPosition,
	                           const Vector2 &newSize,
	                           const Vector2 &newTextureOffset) : Button() {
		this->setPosition(startingPosition);
		this->setTextureInformation(newTexture);

		if (newSize.x > 0.0f && newSize.y > 0.0f) {
			construct(newSize, startingPosition, newTextureOffset, 4);
			this->initializeAnimations();

		} else if (this->getTextureInformation()) {
			construct(Vector2(static_cast<float>(this->getTextureInformation()->imageWidth / 4),
			                  static_cast<float>(this->getTextureInformation()->imageHeight)),
			          startingPosition, newTextureOffset, 4);
			this->initializeAnimations();
		}
	}

	SimpleButton::SimpleButton(const SimpleButton &src) : Button(src) {
	}

	SimpleButton::~SimpleButton() {
	}

	SimpleButton &SimpleButton::operator=(const SimpleButton &src) {
		this->Button::operator=(src);
		return *this;
	}

	const TextureCoordinates &SimpleButton::getCurrentTextureCoordinates() const {
		if (this->isActive()) {
			return this->Button::getCurrentTextureCoordinates();

		} else {
			return this->getFrames()[3];
		}
	}

	void SimpleButton::onPress() {
		this->startAnimation("p");
	}

	void SimpleButton::onHold() {
	}

	void SimpleButton::onRelease() {
		this->startAnimation("h");
		click();
	}

	void SimpleButton::onEnter() {
		this->startAnimation("h");
		hover();
	}

	void SimpleButton::onLeave() {
		this->startAnimation("n");
	}

	void SimpleButton::initializeAnimations() {
		this->addAnimation("n", 0.0, 1, 1, 0);
		this->addAnimation("h", 0.0, 1, 1, 1);
		this->addAnimation("p", 0.0, 1, 1, 2);
		this->addAnimation("i", 0.0, 1, 1, 3);
	}
}
