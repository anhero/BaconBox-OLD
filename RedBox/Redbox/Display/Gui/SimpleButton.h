/**
 * @file
 * @ingroup GUI
 */
#ifndef RB_SIMPLE_BUTTON_H
#define RB_SIMPLE_BUTTON_H

#include "Button.h"

namespace RedBox {
	/**
	 * Represents a simple buttons that has graphics for 4 states.
	 * @ingroup GUI
	 */
	class SimpleButton : public Button {
	public:
		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, each button frame will be equal to the texture's width
		 * divided by 4.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param startingPosition Starting position at which to place the
		 * button.
		 * @param newSize Size of the button.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit SimpleButton(TexturePointer newTexture,
		                      const Vector2 &startingPosition = Vector2(),
		                      const Vector2 &newSize = Vector2(),
		                      const Vector2 &newTextureOffset = Vector2());

		/**
		 * Copy constructor.
		 * @param src SimpleButton to make a copy of.
		 */
		SimpleButton(const SimpleButton &src);

		/**
		 * Destructor.
		 */
		virtual ~SimpleButton();

		/**
		 * Assignment operator.
		 * @param src SimpleButton to make a copy of.
		 * @return Reference to the modified SimpleButton.
		 */
		SimpleButton &operator=(const SimpleButton &src);

		/**
		 * Gets the texture coordinates for the body.
		 * @return Texture coordinates used to map the texture on the body's
		 * polygon.
		 * @see RedBox::Animatable::frames
		 */
		const TextureCoordinates &getCurrentTextureCoordinates() const;
	private:
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
		 * Initializes the 4 animations for the sprite.
		 */
		void initializeAnimations();
	};

}

#endif
