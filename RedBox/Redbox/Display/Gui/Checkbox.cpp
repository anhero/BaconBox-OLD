#include "Checkbox.h"

using namespace RedBox;

Checkbox::Checkbox(const std::string& textureKey, unsigned int frameWidth,
                   unsigned int frameHeight) : IButton(),
	buttonSprite(textureKey, frameWidth, frameHeight, 6), checked(false) {
	initializeAnimations();
}

Checkbox::Checkbox(TextureInfo* textureInfo, unsigned int frameWidth,
                   unsigned int frameHeight) : IButton(),
	buttonSprite(textureInfo, frameWidth, frameHeight, 6), checked(false) {
	initializeAnimations();
}

Checkbox::Checkbox(const Checkbox& src) : IButton(src),
	buttonSprite(src.buttonSprite), checked(false) {
}

Checkbox::~Checkbox() {
}

Checkbox& Checkbox::operator=(const Checkbox& src) {
	this->IButton::operator=(src);
	if(this != &src) {
		buttonSprite = src.buttonSprite;
		checked = src.checked;
	}
	return *this;
}

void Checkbox::update() {
	this->IButton::update();
	buttonSprite.update();
}

void Checkbox::render() {
	buttonSprite.render();
}

void Checkbox::mask() {
	buttonSprite.mask();
}

void Checkbox::unmask() {
	buttonSprite.unmask();
}

GraphicBody* Checkbox::getMask() {
	return buttonSprite.getMask();
}

void Checkbox::setMask(GraphicBody* newMask, bool inverted) {
	buttonSprite.setMask(newMask, inverted);
}

void Checkbox::setPosition(float newXPosition, float newYPosition) {
	this->IButton::setPosition(newXPosition, newYPosition);
	buttonSprite.setPosition(newXPosition, newYPosition);
}

float Checkbox::getWidth() const {
	return buttonSprite.getWidth();
}

float Checkbox::getHeight() const {
	return buttonSprite.getHeight();
}

void Checkbox::setScaling(float newXScaling, float newYScaling) {
	this->IButton::setScaling(newXScaling, newYScaling);
	buttonSprite.setScaling(newXScaling, newYScaling);
	this->IButton::setPosition(buttonSprite.getXPosition(), buttonSprite.getYPosition());
}

void Checkbox::rotateFromPoint(float rotationAngle,
							   const Vector2& rotationPoint) {
	this->IButton::rotateFromPoint(rotationAngle, rotationPoint);
	buttonSprite.rotateFromPoint(rotationAngle, rotationPoint);
	this->IButton::setPosition(buttonSprite.getXPosition(), buttonSprite.getYPosition());
}

GraphicBody* Checkbox::clone() const {
	return new Checkbox(*this);
}

bool Checkbox::isChecked() const {
	return checked;
}

void Checkbox::setChecked(bool newChecked) {
	checked = newChecked;
	if(this->getState() == ButtonState::NORMAL) {
		if(isChecked()) {
			buttonSprite.playAnimation("cn");
		} else {
			buttonSprite.playAnimation("n");
		}
	} else if(this->getState() == ButtonState::HOVER) {
		if(isChecked()) {
			buttonSprite.playAnimation("ch");
		} else {
			buttonSprite.playAnimation("h");
		}
	} else if(this->getState() == ButtonState::PRESSED) {
		if(isChecked()) {
			buttonSprite.playAnimation("cp");
		} else {
			buttonSprite.playAnimation("p");
		}
	}
}

void Checkbox::toggleChecked() {
	setChecked(!checked);
}

void Checkbox::onPress() {
	if(isChecked()) {
		buttonSprite.playAnimation("cp");
	} else {
		buttonSprite.playAnimation("p");
	}
}

void Checkbox::onHold() {
}

void Checkbox::onRelease() {
	toggleChecked();
	if(isChecked()) {
		buttonSprite.playAnimation("ch");
	} else {
		buttonSprite.playAnimation("h");
	}
	click();
}

void Checkbox::onEnter() {
	if(isChecked()) {
		buttonSprite.playAnimation("ch");
	} else {
		buttonSprite.playAnimation("h");
	}
	hover();
}

void Checkbox::onLeave() {
	if(isChecked()) {
		buttonSprite.playAnimation("cn");
	} else {
		buttonSprite.playAnimation("n");
	}
}

void Checkbox::initializeAnimations() {
	buttonSprite.addAnimation("n", 0.0, 1, 1, 0);
	buttonSprite.addAnimation("h", 0.0, 1, 1, 1);
	buttonSprite.addAnimation("p", 0.0, 1, 1, 2);
	buttonSprite.addAnimation("cn", 0.0, 1, 1, 3);
	buttonSprite.addAnimation("ch", 0.0, 1, 1, 4);
	buttonSprite.addAnimation("cp", 0.0, 1, 1, 5);

}
