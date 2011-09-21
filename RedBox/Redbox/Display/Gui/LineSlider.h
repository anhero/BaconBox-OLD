#ifndef RB_LINE_SLIDER_H
#define RB_LINE_SLIDER_H

#include <algorithm>

#include "Slider.h"
#include "Sprite.h"
#include "Pointer.h"

namespace RedBox {
	template <typename T>
	class LineSlider : public Slider<T> {
	public:
		typedef typename Slider<T>::ValueType ValueType;

		sigly::Signal0<> release;

		/**
		 * Parameterized constructor. Creates the line and the slider's
		 * button from texture keys.
		 * @param newMinimumValue Slider's minimum value.
		 * @param newMaximumValue Slider's maximum value.
		 * @param startingValue Slider's starting value. Clamped to stay
		 * within the slider's range.
		 * @param lineTextureKey Texture key to use for the line's texture.
		 * @param buttonTextureKey Texture key to use for the button's texture.
		 * @see RedBox::LineSlider<T>::lineSprite
		 * @see RedBox::LineSlider<T>::buttonSprite
		 * @see RedBox::Slider<T>
		 */
		LineSlider(ValueType newMinimumValue, ValueType newMaximumValue,
		           ValueType startingValue, const std::string &lineTextureKey,
		           const std::string &buttonTextureKey) :
			Slider<T>(newMinimumValue, newMaximumValue, startingValue),
			lineSprite(lineTextureKey), buttonSprite(buttonTextureKey),
			down(false) {
			placeButton();
		}

		/**
		 * Copy constructor.
		 * @param src Line slider to make a copy of.
		 */
		LineSlider(const LineSlider<ValueType>& src) : Slider<T>(src),
			lineSprite(src.lineSprite), buttonSprite(src.buttonSprite),
			down(false) {
		}

		/**
		 * Assignment operator overload.
		 * @param src Line slider to make a copy of.
		 * @return Reference to the modified line slider.
		 */
		LineSlider<ValueType>& operator=(const LineSlider<ValueType>& src) {
			this->Slider<T>::operator=(src);

			if (this != &src) {
				lineSprite = src.lineSprite;
				buttonSprite = src.buttonSprite;
				down = false;
			}

			return *this;
		}

		/**
		 * Updates the slider and its sprites.
		 */
		void update() {
			this->Slider<T>::update();
			lineSprite.update();
			buttonSprite.update();
			Pointer *ptr = Pointer::getDefault();

			if (ptr) {
				const CursorState &cur = ptr->getState().getCursorState();

				if (!down) {
					if (cur.isButtonPressed(CursorButton::LEFT) && AABB::overlaps(cur.getPosition(), lineSprite.getAABB())) {
						down = true;
					}
				}

				if (down) {
					if (cur.isButtonReleased(CursorButton::LEFT)) {
						down = false;
						release.shoot();

					} else if ((!cur.isButtonPressed(CursorButton::LEFT) && !cur.isButtonHeld(CursorButton::LEFT))) {
						down = false;

					} else {
						// We get the button's sprite's real width.
						unsigned int i = 0;
                        std::vector<Vector2*>tmpArray = buttonSprite.getVertices().getVertices();
						//std::vector<Vector2>::iterator i = buttonSprite.getVertices().getVertices().begin();
						Vector2 tmpLine(*(tmpArray[i]));
						++i;
						Vector2 line(*tmpArray[i]);
						Vector2 horizontalLine = line - tmpLine;
						// We get the upper left vertex's position.
						i = 0;
						tmpArray = lineSprite.getVertices().getVertices();
						tmpLine = *tmpArray[i];
						// We get the upper right vertex's position.
						++i;
						line = *tmpArray[i];
						// We get the line's sprite's real center right position.
						++i;
						line += (*(tmpArray[i]) - line) * 0.5f;
						line -= horizontalLine * 0.5f;
						// We get the line's sprite's real center left position.
						++i;
						tmpLine += (*(tmpArray[i]) - tmpLine) * 0.5f;
						tmpLine += horizontalLine * 0.5f;
						// We get the line that goes from the line's sprite's
						// left center position to its right center position.
						line -= tmpLine;
						// We get the cursor's position relative to the line's
						// sprite's left center position.
						tmpLine = cur.getPosition() - tmpLine;
						// We project the cursor's relative position onto
						// the line's sprite's horizontal center line.
						tmpLine.project(line);
						// We calculate the new current value from the
						// projected cursor's position's length.
						this->setCurrentValue(this->getMinimumValue() + static_cast<ValueType>((((MathHelper::sameSign(line.getX(), tmpLine.getX()) && MathHelper::sameSign(line.getY(), tmpLine.getY())) ? (tmpLine.getLength()) : (-tmpLine.getLength())) / line.getLength()) * static_cast<float>(this->getMaximumValue() - this->getMinimumValue())));
					}
				}
			}
		}

		/**
		 * Renders the slider's sprites.
		 */
		void render() {
			lineSprite.render();
			buttonSprite.render();
		}

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is
		 * used to mask the next rendered graphic body (if the next graphic
		 * body is set as a masked sprite).
		 */
		void mask() {
			lineSprite.mask();
			buttonSprite.mask();
		}

		/**
		 * Undo what the mask function did. This function
		 * MUST be once after the masked graphic body has been rendered.
		 */
		void unmask() {
			lineSprite.unmask();
			buttonSprite.unmask();
		}

		/**
		 * Gets the graphic body masking the current button.
		 * @return Pointer to the slider's mask.
		 */
		GraphicBody *getMask() {
			return lineSprite.getMask();
		}

		/**
		 * Sets the graphic body used to mask the slider.
		 * @param newMask A mask graphic body.
		 * @param inversed Set this parameter to true if you want to inverse
		 * the effect of the mask. False by default.
		 */
		void setMask(GraphicBody *newMask, bool inversed = false) {
			lineSprite.setMask(newMask, inversed);
			buttonSprite.setMask(newMask, inversed);
		}

		using GraphicBody::setPosition;

		/**
		 * Sets the line slider's horizontal and vertical position.
		 * @param newXPosition New horizontal position (in pixels). Lower value
		 * means more to the left.
		 * @param newYPosition New vertical position (in pixels). Lower value
		 * means more at the top.
		 */
		void setPosition(float newXPosition, float newYPosition) {
			Vector2 delta(newXPosition, newYPosition);
			delta -= this->getPosition();
			this->Slider<T>::setPosition(newXPosition, newYPosition);
			lineSprite.move(delta);
			buttonSprite.move(delta);
		}

		/**
		 * Gets the line slider's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const {
			return std::max(lineSprite.getXPosition() + lineSprite.getWidth(), buttonSprite.getXPosition() + buttonSprite.getWidth()) -
			       std::min(lineSprite.getXPosition(), buttonSprite.getXPosition());
		}

		/**
		 * Gets the line slider's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const {
			return std::max(lineSprite.getYPosition() + lineSprite.getHeight(), buttonSprite.getYPosition() + buttonSprite.getHeight()) -
			       std::min(lineSprite.getYPosition(), buttonSprite.getYPosition());
		}

		using GraphicBody::scaleFromPoint;

		/**
		 * Scales the line slider from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the line slider will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the line slider will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::GraphicBody::scaling
		 */
		virtual void scaleFromPoint(float xScaling, float yScaling,
		                            const Vector2 &fromPoint) {
			this->Slider<T>::scaleFromPoint(xScaling, yScaling, fromPoint);
			lineSprite.scaleFromPoint(xScaling, yScaling, fromPoint);
			buttonSprite.scaleFromPoint(xScaling, yScaling, fromPoint);
			refreshPosition();
		}

		/**
		 * Rotates the line slider from a point.
		 * @param rotationAngle Angle to rotate the simple button.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::GraphicBody::angle
		 */
		void rotateFromPoint(float rotationAngle, const Vector2 &rotationPoint) {
			this->Slider<T>::rotateFromPoint(rotationAngle, rotationPoint);
			lineSprite.rotateFromPoint(rotationAngle, rotationPoint);
			buttonSprite.rotateFromPoint(rotationAngle, rotationPoint);
			refreshPosition();
		}

		/**
		 * Creates a copy of the current simple button.
		 * @return Pointer to the new simple button.
		 */
		GraphicBody *clone() const {
			return new LineSlider<ValueType>(*this);
		}

		/**
		 * Sets the slider's current value.
		 * @param newCurrentValue New value to set.
		 * @see RedBox::Slider<T>::currentValue
		 */
		void setCurrentValue(ValueType newCurrentValue) {
			this->Slider<T>::setCurrentValue(newCurrentValue);
			placeButton();
		}
	private:
		/// Sprite used to represent the background line.
		Sprite lineSprite;

		/// Sprite used to represent the selecting button.
		Sprite buttonSprite;

		/// Set to true when the slider is being slided.
		bool down;

		/**
		 * Places the button at the position corresponding to the curent value.
		 */
		void placeButton() {
			float tmpAngle = this->getAngle();

			if (tmpAngle != 0.0f) {
				this->setAngle(0.0f);
			}

			if (this->getMaximumValue() == this->getMinimumValue()) {
				buttonSprite.setPosition(lineSprite.getPositionCenter() - Vector2(buttonSprite.getWidth(), buttonSprite.getHeight()) * 0.5f);

			} else {
				float clampedValue = static_cast<float>(this->getCurrentValue() - this->getMinimumValue()) / static_cast<float>(this->getMaximumValue() - this->getMinimumValue());
				buttonSprite.setPosition(lineSprite.getXPosition() + (lineSprite.getWidth() - buttonSprite.getWidth()) * clampedValue,
				                         lineSprite.getYPositionCenter() - buttonSprite.getHeight() * 0.5f);
			}

			if (tmpAngle != 0.0f) {
				this->setAngle(tmpAngle);
			}

			refreshPosition();
		}

		/**
		 * Refreshes the parent graphic body's position.
		 */
		void refreshPosition() {
			this->Slider<T>::setPosition(std::min(lineSprite.getXPosition(), buttonSprite.getXPosition()),
			                             std::min(lineSprite.getYPosition(), buttonSprite.getYPosition()));
		}
	};
}

#endif
