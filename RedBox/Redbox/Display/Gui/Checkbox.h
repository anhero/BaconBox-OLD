#ifndef RB_CHECK_BOX_H
#define RB_CHECK_BOX_H

#include "IButton.h"
#include "Sprite.h"

namespace RedBox {
	class Checkbox : public IButton {
	public:
		/**
		 * Parameterized constructor.
		 */
		Checkbox(const std::string& textureKey, unsigned int frameWidth,
		         unsigned int frameHeight);

		Checkbox(TextureInfo* textureInfo, unsigned int frameWidth,
		         unsigned int frameHeight);

		Checkbox(const Checkbox& src);

		~Checkbox();

		Checkbox& operator=(const Checkbox& src);

		/**
		 * Updates the checkbox and its sprite.
		 */
		void update();

		/**
		 * Renders the checkbox's sprite.
		 */
		void render();

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is
		 * used to mask the next rendered graphic body (if the next graphic
		 * body is set as a masked sprite).
		 */
		void mask();

		/**
		 * Undo what the mask function did. This function
		 * MUST be once after the masked graphic body has been rendered.
		 */
		void unmask();

		/**
		 * Gets the graphic body masking the current checkbox.
		 * @return Pointer to the button's mask.
		 */
		GraphicBody* getMask();

		/**
		 * Sets the graphic body used to mask the checkbox.
		 * @param newMask A mask graphic body.
		 * @param inverted Set this parameter to true if you want to inverse
		 * the effect of the mask. False by default.
		 */
		void setMask(GraphicBody* newMask, bool inverted = false);

		using GraphicBody::setPosition;

		/**
		 * Sets the checkbox's horizontal and vertical position.
		 * @param newXPosition New horizontal position (in pixels). Lower value
		 * means more to the left.
		 * @param newYPosition New vertical position (in pixels). Lower value
		 * means more at the top.
		 */
		void setPosition(float newXPosition, float newYPosition);

		/**
		 * Gets the checkbox's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const;

		/**
		 * Gets the checkbox's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const;

		using GraphicBody::scaleFromPoint;

		/**
		 * Scales the checkbox from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the checkbox will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the checkbox will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::GraphicBody::scaling
		 */
		virtual void scaleFromPoint(float xScaling, float yScaling,
		                            const Vector2& fromPoint);

		/**
		 * Rotates the checkbox from a point.
		 * @param rotationAngle Angle to rotate the simple button.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::GraphicBody::angle
		 */
		void rotateFromPoint(float rotationAngle, const Vector2& rotationPoint);

		/**
		 * Creates a copy of the current checkbox.
		 * @return Pointer to the new checkbox.
		 */
		GraphicBody* clone() const;

		bool isChecked() const;

		void setChecked(bool newChecked);

		void toggleChecked();
	private:
		Sprite buttonSprite;
		bool checked;

		/**
		 * Called when a pointer button press is detected while the cursor is
		 * over the button.
		 */
		void onPress();

		/**
		 * Called when a pointer button hold is detected while the cursor is
		 * over the button.
		 */
		void onHold();

		/**
		 * Called when a pointer button release is detected while the cursor is
		 * over the button and that the button press was also on the same
		 * button.
		 */
		void onRelease();

		/**
		 * Called when the button is up and the cursor hovers the button.
		 */
		void onEnter();

		/**
		 * Called when the button is up and the cursor leaves the button.
		 */
		void onLeave();

		void initializeAnimations();
	};
}

#endif
