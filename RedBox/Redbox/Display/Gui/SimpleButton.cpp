#include "SimpleButton.h"

using namespace RedBox;

SimpleButton::SimpleButton(TextureInfo* textureInfo, unsigned int frameWidth,
						   unsigned int frameHeight) : IButton(),
	buttonSprite(textureInfo, frameWidth, frameHeight, 3) {
	initializeAnimations();
}

SimpleButton::SimpleButton(const std::string& textureKey,
						   unsigned int frameWidth, unsigned int frameHeight) :
	IButton(), buttonSprite(textureKey, frameWidth, frameHeight, 3) {
	initializeAnimations();
}

SimpleButton::SimpleButton(const SimpleButton& src) : IButton(src),
	buttonSprite(src.buttonSprite) {
}

SimpleButton::~SimpleButton() {
}

SimpleButton& SimpleButton::operator=(const SimpleButton& src) {
	this->IButton::operator=(src);
	if(this != &src) {
		buttonSprite = src.buttonSprite;
	}
	return *this;
}

void SimpleButton::update() {
	this->IButton::update();
	buttonSprite.update();
}

void SimpleButton::render() {
	buttonSprite.render();
}

void SimpleButton::setPosition(float newXPosition, float newYPosition) {
	this->GraphicBody::setPosition(newXPosition, newYPosition);
	buttonSprite.setPosition(newXPosition, newYPosition);
}

void SimpleButton::setXPosition(float newXPosition) {
	this->GraphicBody::setXPosition(newXPosition);
	buttonSprite.setXPosition(newXPosition);
}

void SimpleButton::setYPosition(float newYPosition) {
	this->GraphicBody::setYPosition(newYPosition);
	buttonSprite.setYPosition(newYPosition);
}

float SimpleButton::getWidth() const {
	return buttonSprite.getWidth();
}

float SimpleButton::getHeight() const {
	return buttonSprite.getHeight();
}

void SimpleButton::setScaling(float newXScaling, float newYScaling) {
	this->GraphicBody::setScaling(newXScaling, newYScaling);
	buttonSprite.setScaling(newXScaling, newYScaling);
}

void SimpleButton::setAngle(float newAngle) {
	this->GraphicBody::setAngle(newAngle);
	buttonSprite.setAngle(newAngle);
}

void SimpleButton::onPress() {
	buttonSprite.playAnimation("p");
}

void SimpleButton::onHold() {
}

void SimpleButton::onRelease() {
	buttonSprite.playAnimation("h");
	click();
}

void SimpleButton::onEnter() {
	buttonSprite.playAnimation("h");
	hover();
}

void SimpleButton::onLeave() {
	buttonSprite.playAnimation("n");
}

void SimpleButton::initializeAnimations() {
	buttonSprite.addAnimation("n", 0.0, 1, 1, 0);
	buttonSprite.addAnimation("h", 0.0, 1, 1, 1);
	buttonSprite.addAnimation("p", 0.0, 1, 1, 2);
}

