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

void SimpleButton::mask() {
	buttonSprite.mask();
}

void SimpleButton::unmask() {
	buttonSprite.unmask();
}

GraphicBody* SimpleButton::getMask() {
	return buttonSprite.getMask();
}

void SimpleButton::setMask(GraphicBody* newMask, bool inversed) {
	buttonSprite.setMask(newMask, inversed);
}

void SimpleButton::setPosition(float newXPosition, float newYPosition) {
	this->GraphicBody::setPosition(newXPosition, newYPosition);
	buttonSprite.setPosition(newXPosition, newYPosition);
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
	this->GraphicBody::setPosition(buttonSprite.getXPosition(),
	                               buttonSprite.getYPosition());
}

void SimpleButton::rotateFromPoint(float rotationAngle,
                                   const Vec2& rotationPoint) {
	this->GraphicBody::rotateFromPoint(rotationAngle, rotationPoint);
	buttonSprite.rotateFromPoint(rotationAngle, rotationPoint);
	this->GraphicBody::setPosition(buttonSprite.getXPosition(),
	                               buttonSprite.getYPosition());
}

GraphicBody* SimpleButton::clone() const {
	return new SimpleButton(*this);
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

