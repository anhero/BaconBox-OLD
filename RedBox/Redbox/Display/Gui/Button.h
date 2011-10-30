/**
 * @file
 * @ingroup GUI
 */
#ifndef RB_BUTTON_H
#define RB_BUTTON_H

#include <sigly.h>

#include "Sprite.h"
#include "ButtonState.h"
#include "TexturePointer.h"

namespace RedBox {
	/**
	 * All classes that represent a type of button are derived from this class.
	 * SimpleButton and Checkbox are two of those.
	 * @see RedBox::SimpleButton
	 * @see RedBox::Checkbox
	 * @ingroup GUI
	 */
	class Button : public Sprite {
	public:
		/// Signal sent when the button is clicked.
		sigly::Signal0<> click;

		/// Signal sent when the cursor starts hovering the button.
		sigly::Signal0<> hover;

		/**
		 * Default constructor.
		 */
		Button();

		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, it loads the the full texture as the size and image.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param startingPosition Starting position at which to place the
		 * sprite.
		 * @param newSize Size of the sprite.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @param nbFrames Number of frames to load.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit Button(TexturePointer newTexture,
		                const Vector2 &startingPosition = Vector2(),
		                const Vector2 &newSize = Vector2(),
		                const Vector2 &newTextureOffset = Vector2(),
		                unsigned int nbFrames = 1);

		/**
		 * Copy constructor.
		 * @param src Button to make a copy of.
		 */
		Button(const Button &src);

		/**
		 * Destructor.
		 */
		virtual ~Button();

		/**
		 * Assignment operator.
		 * @param src Button to make a copy of.
		 * @return Reference to the modified Button.
		 */
		Button &operator=(const Button &src);

		/**
		 * Updates the body.
		 */
		virtual void update();

		/**
		 * Gets the button's state.
		 * @return Button's current state.
		 * @see RedBox::IButton::state
		 */
		ButtonState getButtonState() const;
	protected:
		/**
		 * Called when a pointer button press is detected while the cursor is
		 * over the button.
		 */
		virtual void onPress() = 0;

		/**
		 * Called when a pointer button hold is detected while the cursor is
		 * over the button.
		 */
		virtual void onHold() = 0;

		/**
		 * Called when a pointer button release is detected while the cursor is
		 * over the button and that the button press was also on the same
		 * button.
		 */
		virtual void onRelease() = 0;

		/**
		 * Called when the button is up and the cursor hovers the button.
		 */
		virtual void onEnter() = 0;

		/**
		 * Called when the button is up and the cursor leaves the button.
		 */
		virtual void onLeave() = 0;
	private:
		/// Button's current state.
		ButtonState buttonState;

		/**
		 * Boolean value used when the button is pressed and the cursor leaves
		 * the button.
		 */
		bool tmpHold;
	};

}

#endif
