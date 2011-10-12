#include "TextButton.h"

#include "TextureInformation.h"

namespace RedBox {
	TextButton::TextButton(TexturePointer newTexture,
	                       FontPointer newFont,
	                       const std::string &newText,
	                       const Vector2 &newTextOffset,
	                       const Vector2 &startingPosition,
	                       const Vector2 &newSize,
	                       const Vector2 &newTextureOffset) : Button(),
		text(newFont, newText, TextAlignment::CENTER), textOffset(newTextOffset) {
		this->setPosition(startingPosition);
		this->setTextureInformation(newTexture);

		if (newSize.getX() > 0.0f && newSize.getY() > 0.0f) {
			construct(newSize, startingPosition, newTextureOffset, 4);
			this->initializeAnimations();

		} else if (this->getTextureInformation()) {
			construct(Vector2(static_cast<float>(this->getTextureInformation()->imageWidth / 4),
			                  static_cast<float>(this->getTextureInformation()->imageHeight)),
			          startingPosition, newTextureOffset, 4);
			this->initializeAnimations();
		}

		refreshTextPosition();
	}

	TextButton::TextButton(TexturePointer newTexture,
	                       FontPointer newFont,
	                       const String32 &newText,
	                       const Vector2 &newTextOffset,
	                       const Vector2 &startingPosition,
	                       const Vector2 &newSize,
	                       const Vector2 &newTextureOffset) : Button(),
		text(newFont, newText, TextAlignment::CENTER), textOffset(newTextOffset) {
		this->setPosition(startingPosition);
		this->setTextureInformation(newTexture);

		if (newSize.getX() > 0.0f && newSize.getY() > 0.0f) {
			construct(newSize, startingPosition, newTextureOffset, 4);
			this->initializeAnimations();

		} else if (this->getTextureInformation()) {
			construct(Vector2(static_cast<float>(this->getTextureInformation()->imageWidth / 4),
			                  static_cast<float>(this->getTextureInformation()->imageHeight)),
			          startingPosition, newTextureOffset, 4);
			this->initializeAnimations();
		}

		refreshTextPosition();
	}

	TextButton::TextButton(const TextButton &src) : Button(src), text(src.text),
		textOffset(src.textOffset) {
	}

	TextButton::~TextButton() {
	}

	TextButton &TextButton::operator=(const TextButton &src) {
		this->Button::operator=(src);

		if (this != &src) {
			text = src.text;
			textOffset = src.textOffset;
		}

		return *this;
	}

	void TextButton::render() {
		this->Button::render();
		text.render();
	}

	void TextButton::mask() {
		this->Button::mask();
		text.mask();
	}

	void TextButton::unmask() {
		this->Button::unmask();
		text.unmask();
	}

	void TextButton::setMask(Maskable *newMask, bool inverted) {
		this->Button::setMask(newMask, inverted);
		text.setMask(newMask, inverted);
	}

	const TextureCoordinates &TextButton::getCurrentTextureCoordinates() const {
		if (this->isActive()) {
			return this->Button::getCurrentTextureCoordinates();

		} else {
			return this->getFrames()[3];
		}
	}

	void TextButton::move(float xDelta, float yDelta) {
		this->Button::move(xDelta, yDelta);
		text.move(xDelta, yDelta);
	}

	void TextButton::scaleFromPoint(float xScaling, float yScaling,
	                                const Vector2 &fromPoint) {
		this->Button::scaleFromPoint(xScaling, yScaling, fromPoint);
		refreshTextPosition();
	}

	void TextButton::rotateFromPoint(float rotationAngle,
	                                 const Vector2 &rotationPoint) {
		this->Button::rotateFromPoint(rotationAngle, rotationPoint);
		text.rotateFromPoint(rotationAngle, rotationPoint);
	}

	Font *TextButton::getFont() const {
		return text.getFont();
	}

	void TextButton::setFont(FontPointer newFont) {
		text.setFont(newFont);
		refreshTextPosition();
	}

	std::string TextButton::getText() const {
		return text.getText();
	}

	void TextButton::setText(const std::string newText) {
		text.setText(newText);
		refreshTextPosition();
	}

	const String32 &TextButton::getUtf32Text() const {
		return text.getUtf32Text();
	}

	void TextButton::setUtf32Text(const String32 &newText) {
		text.setUtf32Text(newText);
		refreshTextPosition();
	}

	const Color &TextButton::getTextColor() const {
		return text.getColor();
	}

	void TextButton::setTextColor(const Color &newTextColor) {
		text.setColor(newTextColor);
	}

	const Vector2 &TextButton::getTextOffset() const {
		return textOffset;
	}

	void TextButton::setTextOffset(const Vector2 &newTextOffset) {
		textOffset = newTextOffset;
	}

	void TextButton::onPress() {
		this->startAnimation("p");
		text.move(textOffset);
	}

	void TextButton::onHold() {
	}

	void TextButton::onRelease() {
		this->startAnimation("h");
		refreshTextPosition();
		click();
	}

	void TextButton::onEnter() {
		this->startAnimation("h");
		hover();
	}

	void TextButton::onLeave() {
		this->startAnimation("n");
		refreshTextPosition();
	}

	void TextButton::initializeAnimations() {
		this->addAnimation("n", 0.0, 1, 1, 0);
		this->addAnimation("h", 0.0, 1, 1, 1);
		this->addAnimation("p", 0.0, 1, 1, 2);
		this->addAnimation("i", 0.0, 1, 1, 3);
	}

	void TextButton::refreshTextPosition() {
		text.setPosition(getPosition() + getSize() * 0.5f - text.getSize() * 0.5f);
	}
}
