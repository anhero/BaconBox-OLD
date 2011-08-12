/**
 * @file
 * @ingroup GUI
 */
#ifndef RB_SIMPLE_BUTTON_H
#define RB_SIMPLE_BUTTON_H

#include <string>

#include "IButton.h"
#include "Sprite.h"

namespace RedBox {
	/**
	 * Represents a simple buttons that has graphics for 3 states.
	 * @ingroup GUI
	 */
	class SimpleButton : public IButton {
	public:
		/**
		 * Parameterized constructor. Loads a button using the texture in the
		 * resource manager with the corresponding key. Only takes the asked
		 * part of the texture with the given width and height.
		 * @param textureKey Texture's key in the ResourceManager to use for the
		 * constructed sprite.
		 * @param frameWidth Width of the frames to read from the image (in
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 */
		SimpleButton(const std::string& textureKey, unsigned int frameWidth,
		             unsigned int frameHeight);

		/**
		 * Parameterized constructor. Loads a button using a pointer to a
		 * TextureInfo. Only takes the asked part of the texture with the given
		 * width and height.
		 * @param textureInfo Pointer to the texture information to load the
		 * button from.
		 * @param frameWidth Width of the frames to read from the image (in
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 */
		SimpleButton(TextureInfo* textureInfo, unsigned int frameWidth,
		             unsigned int frameHeight);

		/**
		 * Copy constructor.
		 * @param src Simple button to make a copy of.
		 */
		SimpleButton(const SimpleButton& src);

		/**
		 * Destructor.
		 */
		~SimpleButton();

		/**
		 * Assignment operator overload.
		 * @param src Simple button to make a copy of.
		 * @return Reference to the modified simple button.
		 */
		SimpleButton& operator=(const SimpleButton& src);

		/**
		 * Updates the button and its sprite.
		 */
		void update();

		/**
		 * Renders the button's sprite.
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
		 * Gets the graphic body masking the current button.
		 * @return Pointer to the button's mask.
		 */
		GraphicBody* getMask();

		/**
		 * Sets the graphic body used to mask the button.
		 * @param newMask A mask graphic body.
		 * @param inversed Set this parameter to true if you want to inverse
		 * the effect of the mask. False by default.
		 */
		void setMask(GraphicBody* newMask, bool inversed = false);

		using GraphicBody::setPosition;

		/**
		 * Sets the simple button's horizontal and vertical position.
		 * @param newXPosition New horizontal position (in pixels). Lower value
		 * means more to the left.
		 * @param newYPosition New vertical position (in pixels). Lower value
		 * means more at the top.
		 */
		void setPosition(float newXPosition, float newYPosition);

		/**
		 * Gets the simple button's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const;

		/**
		 * Gets the simple button's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const;

		using GraphicBody::setScaling;

		/**
		 * Change the simple button's scaling.
		 * @param xScaling New horizontal scaling to apply.
		 * @param yScaling New vertical scaling to apply.
		 */
		void setScaling(float newXScaling, float newYScaling);

		/**
		 * Rotates the simple button from a point.
		 * @param rotationAngle Angle to rotate the simple button.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::GraphicBody::angle
		 */
		void rotateFromPoint(float rotationAngle, const Vec2& rotationPoint);

		/**
		 * Creates a copy of the current simple button.
		 * @return Pointer to the new simple button.
		 */
		GraphicBody* clone() const;
	private:
		/// Sprite representing the button's graphic.
		Sprite buttonSprite;

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

		/**
		 * Initializes the 3 animations for the sprite.
		 */
		void initializeAnimations();
	};
}

#endif
