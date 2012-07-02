/**
 * @file
 */
#ifndef RB_LINE_SLIDER_H
#define RB_LINE_SLIDER_H

#include <algorithm>

#include "BaconBox/Display/Gui/Slider.h"
#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Display/Layerable.h"
#include "BaconBox/Display/Collidable.h"
#include "BaconBox/Display/InanimateGraphicElement.h"
#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Engine.h"
#include "BaconBox/Display/StandardVertexArray.h"

namespace BaconBox {
	template <typename T>
	class LineSlider : public Slider<T>, public Collidable, public Layerable {
	public:
		typedef typename Slider<T>::ValueType ValueType;

		sigly::Signal0<> release;

		/**
		 * Parameterized constructor. Sets the minimum and maximum value.
		 * Clamps the current value to be within the possible range.
		 * @param newMinimumValue Range's minimum value.
		 * @param newMaximumValue Range's maximum value.
		 * @param newLineTexture Texture pointer to use as the texture for the
		 * background line.
		 * @param newButtonTexture Texture pointer to use as the texture for
		 * the movable button.
		 * @param startingPosition Position at which to place the line slider.
		 * @param newLineSize Size of the line background.
		 * @param newButtonSize Size of the movable button.
		 * @param newLineTextureOffset Offset in the texture of the background
		 * line.
		 * @param newButtonTextureOffset Offset in the texture of the movable
		 * button.
		 * @see BaconBox::Slider<T>::minimumValue
		 * @see BaconBox::Slider<T>::maximumValue
		 * @see BaconBox::Slider<T>::setMinimumMaximumValue(ValueType newMinimumValue, ValueType newMaximumValue)
		 */
		LineSlider(ValueType newMinimumValue, ValueType newMaximumValue,
		           TexturePointer newLineTexture,
		           TexturePointer newButtonTexture,
		           const Vector2 &startingPosition = Vector2(),
		           const Vector2 &newLineSize = Vector2(),
		           const Vector2 &newButtonSize = Vector2(),
		           const Vector2 &newLineTextureOffset = Vector2(),
		           const Vector2 &newButtonTextureOffset = Vector2()) :
			Slider<ValueType>(), Collidable(startingPosition), Layerable(),
			lineSprite(newLineTexture, startingPosition, newLineSize,
			           newLineTextureOffset),
			buttonSprite(newButtonTexture, startingPosition, newButtonSize,
			             newButtonTextureOffset), down(false),
			vertices(4, startingPosition) {
			initialize(newMinimumValue, newMaximumValue, newMinimumValue,
			           startingPosition);
		}

		/**
		 * Parameterized constructor. Sets the minimum and maximum value.
		 * Clamps the current value to be within the possible range.
		 * @param newMinimumValue Range's minimum value.
		 * @param newMaximumValue Range's maximum value.
		 * @param startingValue Starting current value.
		 * @param newLineTexture Texture pointer to use as the texture for the
		 * background line.
		 * @param newButtonTexture Texture pointer to use as the texture for
		 * the movable button.
		 * @param startingPosition Position at which to place the line slider.
		 * @param newLineSize Size of the line background.
		 * @param newButtonSize Size of the movable button.
		 * @param newLineTextureOffset Offset in the texture of the background
		 * line.
		 * @param newButtonTextureOffset Offset in the texture of the movable
		 * button.
		 * @see BaconBox::Slider<T>::minimumValue
		 * @see BaconBox::Slider<T>::maximumValue
		 * @see BaconBox::Slider<T>::setMinimumMaximumValue(ValueType newMinimumValue, ValueType newMaximumValue)
		 */
		LineSlider(ValueType newMinimumValue, ValueType newMaximumValue,
		           ValueType startingValue,
		           TexturePointer newLineTexture,
		           TexturePointer newButtonTexture,
		           const Vector2 &startingPosition = Vector2(),
		           const Vector2 &newLineSize = Vector2(),
		           const Vector2 &newButtonSize = Vector2(),
		           const Vector2 &newLineTextureOffset = Vector2(),
		           const Vector2 &newButtonTextureOffset = Vector2()) :
			Slider<ValueType>(), Collidable(startingPosition), Layerable(),
			lineSprite(newLineTexture, startingPosition, newLineSize,
			           newLineTextureOffset),
			buttonSprite(newButtonTexture, startingPosition, newButtonSize,
			             newButtonTextureOffset), down(false),
			vertices(4, startingPosition) {
			initialize(newMinimumValue, newMaximumValue, startingValue,
			           startingPosition);
		}

		/**
		 * Copy constructor.
		 * @param src Line slider to make a copy of.
		 */
		LineSlider(const LineSlider<ValueType>& src) : Slider<ValueType>(src),
			Collidable(src), Layerable(src), lineSprite(src.lineSprite),
			buttonSprite(src.buttonSprite), down(src.down),
			vertices(src.vertices) {
		}

		/**
		 * Assignment operator overload.
		 * @param src Line slider to make a copy of.
		 * @return Reference to the modified line slider.
		 */
		LineSlider<ValueType>& operator=(const LineSlider<ValueType>& src) {
			this->Slider<T>::operator=(src);
			this->Collidable::operator=(src);
			this->Layerable::operator=(src);

			if (this != &src) {
				lineSprite = src.lineSprite;
				buttonSprite = src.buttonSprite;
				down = false;
				vertices = src.vertices;
			}

			return *this;
		}

		/**
		 * Updates the slider.
		 */
		void update() {
			this->Collidable::update();
			Pointer *ptr = Pointer::getDefault();
			State *currentState = Engine::getCurrentState();

			if (ptr && currentState) {
				const CursorState &cur = ptr->getState().getCursorState();

				if (!down) {
					if (cur.isButtonPressed(CursorButton::LEFT) &&
					this->getAxisAlignedBoundingBox().overlaps((isHud()) ? (cur.getPosition()) : (currentState->getCamera().screenToWorld(cur.getPosition())))) {
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
						VertexArray::ConstIterator i = buttonSprite.getVertices().getBegin();
						Vector2 tmpLine(*i);
						++i;
						Vector2 horizontalLine = *i - tmpLine;
						// We get the upper left vertex's position.
						i = lineSprite.getVertices().getBegin();
						tmpLine = *i;
						// We get the upper right vertex's position.
						++i;
						Vector2 line(*i);
						// We get the line's sprite's real center right
						// position.
						++i;
						++i;
						line += (*i - line) * 0.5f;
						line -= horizontalLine * 0.5f;
						// We get the line's sprite's real center left
						// position.
						--i;
						tmpLine += (*i - tmpLine) * 0.5f;
						tmpLine += horizontalLine * 0.5f;
						// We get the line that goes from the line's sprite's
						// left center position to its right center position.
						line -= tmpLine;
						// We get the cursor's position relative to the line's
						// sprite's left center position.
						tmpLine = currentState->getCamera().screenToWorld(cur.getPosition()) - tmpLine;
						// We project the cursor's relative position onto the
						// line's sprite's horizontal center line.
						tmpLine.project(line);
						// We calculate the new current value from the
						// projected cursor's position's length.
						this->setCurrentValue(this->getMinimumValue() + static_cast<ValueType>((((MathHelper::sameSign(line.x, tmpLine.x) && MathHelper::sameSign(line.y, tmpLine.y)) ? (tmpLine.getLength()) : (-tmpLine.getLength())) / line.getLength()) * static_cast<float>(this->getMaximumValue() - this->getMinimumValue())));
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
		 * render to the alpha component of the color buffer. It is used to mask
		 * the next rendered renderable body (if the next renderable body is set
		 * as a masked renderable body).
		 */
		void mask() {
			lineSprite.mask();
			buttonSprite.mask();
		}

		/**
		 * Undo what the mask function did. This function must be once after the
		 * masked renderable body has been rendered.
		 */
		void unmask() {
			lineSprite.unmask();
			buttonSprite.unmask();
		}

		/**
		 * Gets the renderable body masking the current renderable body.
		 * @return Pointer to the renderable body's mask.
		 */
		Maskable *getMask() const {
			return lineSprite.getMask();
		}

		/**
		 * Sets the renderable body used to mask the parent renderstep.
		 * @param newMask A mask sprite.
		 * @param inverted Sets this parameter to true if you want to invert
		 * the effect of the mask. False by default.
		 */
		void setMask(Maskable *newMask, bool inverted = false) {
			lineSprite.setMask(newMask, inverted);
			buttonSprite.setMask(newMask, inverted);
		}

		using Collidable::move;

		/**
		 * Moves the Positionable horizontally and vertically.
		 * @param xDelta Value to add to the Positionable's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the Positionable to the left.
		 * @param yDelta Value to add to the Positionable's vertical position (in
		 * pixels). Positive value moves the Positionable down and a negative
		 * value moves the Positionable up.
		 * @see BaconBox::Positionable::move(const Vector2& delta);
		 * @see BaconBox::Positionable::position
		 */
		virtual void move(float xDelta, float yDelta) {
			this->Collidable::move(xDelta, yDelta);
			lineSprite.move(xDelta, yDelta);
			buttonSprite.move(xDelta, yDelta);
			vertices.move(xDelta, yDelta);
		}

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		const Vector2 getSize() const {
			return vertices.getSize();
		}

		/**
		 * Gets the line slider's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const {
			return vertices.getWidth();
		}

		/**
		 * Gets the line slider's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const {
			return vertices.getHeight();
		}

		using Collidable::scaleFromPoint;

		/**
		 * Scales the line slider from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the line slider will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the line slider will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see BaconBox::GraphicBody::scaling
		 */
		virtual void scaleFromPoint(float xScaling, float yScaling,
		                            const Vector2 &fromPoint) {
			this->Collidable::scaleFromPoint(xScaling, yScaling, fromPoint);
			lineSprite.scaleFromPoint(xScaling, yScaling, fromPoint);
			buttonSprite.scaleFromPoint(xScaling, yScaling, fromPoint);
			vertices.scaleFromPoint(xScaling, yScaling, fromPoint);
			refreshPosition();
		}

		/**
		 * Rotates the line slider from a point.
		 * @param rotationAngle Angle to rotate the simple button.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see BaconBox::GraphicBody::angle
		 */
		void rotateFromPoint(float rotationAngle, const Vector2 &rotationPoint) {
			this->Collidable::rotateFromPoint(rotationAngle, rotationPoint);
			lineSprite.rotateFromPoint(rotationAngle, rotationPoint);
			buttonSprite.rotateFromPoint(rotationAngle, rotationPoint);
			vertices.rotateFromPoint(rotationAngle, rotationPoint);
			refreshPosition();
		}

		/**
		 * Sets the slider's current value.
		 * @param newCurrentValue New value to set.
		 * @see BaconBox::Slider<T>::currentValue
		 */
		void setCurrentValue(ValueType newCurrentValue) {
			this->Slider<T>::setCurrentValue(newCurrentValue);
			placeButton();
		}
	private:
		/// Sprite used to represent the background line.
		InanimateGraphicElement<Transformable> lineSprite;

		/// Sprite used to represent the selecting button.
		InanimateGraphicElement<Transformable> buttonSprite;

		/// Set to true when the slider is being slided.
		bool down;

		/// Array containing the 4 vertices for the bounding box.
		StandardVertexArray vertices;

		/**
		 * Initializes the line slider.
		 */
		void initialize(ValueType newMinimumValue, ValueType newMaximumValue,
		                ValueType startingValue,
		                const Vector2 &startingPosition) {
			// We initialize the minimum, the maximum and the starting values.
			this->setMinimumMaximumValue(newMinimumValue, newMaximumValue);
			this->setCurrentValue(startingValue);
			// We position the line and the button at the starting position.
			Vector2 delta(std::min(lineSprite.getXPosition(), buttonSprite.getXPosition()),
			              std::min(lineSprite.getYPosition(), buttonSprite.getYPosition()));
			delta = startingPosition - delta;
			lineSprite.move(delta);
			buttonSprite.move(delta);
			// We initialize the vertices representing the control's box.
			initializeVertices();
		}

		/**
		 * Places the button at the position corresponding to the current value.
		 */
		void placeButton() {
			// We clamp the current value between 0 and 1.
			float clampedValue = static_cast<float>(this->getCurrentValue() - this->getMinimumValue()) / static_cast<float>(this->getMaximumValue() - this->getMinimumValue());

			// If there is no range, we make sure the button is at the center.
			if (this->getMaximumValue() == this->getMinimumValue()) {
				clampedValue = 0.5f;
			}

			// We get the initial upper left corner's position.
			VertexArray::ConstIterator i = lineSprite.getVertices().getBegin();
			Vector2 initialPosition = *i;
			++i;
			// While we're doing that, we take note of the line's real
			// width.
			Vector2 lineLength = *i - initialPosition;
			++i;
			++i;
			initialPosition += (*i - initialPosition) * 0.5f;
			i = buttonSprite.getVertices().getBegin();
			Vector2 tmpPosition = *i;
			++i;
			lineLength -= *i - tmpPosition;
			++i;
			++i;
			initialPosition += (tmpPosition - *i) * 0.5f;
			buttonSprite.move((initialPosition + (lineLength * clampedValue)) - *buttonSprite.getVertices().getBegin());
		}

		/**
		 * Refreshes the position.
		 */
		void refreshPosition() {
			Vector2 delta = vertices.getMinimumXY() - getPosition();
			this->Collidable::move(delta.x, delta.y);
		}

		/**
		 * Initializes the vertices.
		 */
		void initializeVertices() {
			StandardVertexArray::Iterator i = vertices.getBegin();
			++i;
			Vector2 realSize(std::max(lineSprite.getWidth(), buttonSprite.getWidth()),
			                 std::max(lineSprite.getHeight(), buttonSprite.getHeight()));
			i->x += realSize.x;
			++i;
			*i += realSize;
			++i;
			i->y += realSize.y;
		}
	};
}

#endif // RB_LINE_SLIDER_H
