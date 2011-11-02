/**
 * @file
 * @ingroup GUI
 */
#ifndef RB_CHECKBOX_H
#define RB_CHECKBOX_H

#include "Button.h"

namespace RedBox {
	/**
	 * Represents a checkbox button. The texture to be used for the checkbox
	 * must contain in this order the frames for: normal unchecked, hovered
	 * unchecked, pressed unchecked, normal checked, hovered checked, pressed
	 * checked, disabled unchecked and disabled unchecked.
	 * @ingroup GUI
	 */
	class Checkbox : public Button {
	public:
		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, each button frame will be equal to the texture's width
		 * divided by 8.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param startingPosition Starting position at which to place the
		 * button.
		 * @param newSize Size of the button.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit Checkbox(TexturePointer newTexture,
		                  const Vector2 &startingPosition = Vector2(),
		                  const Vector2 &newSize = Vector2(),
		                  const Vector2 &newTextureOffset = Vector2());

		/**
		 * Copy constructor.
		 * @param src Checkbox to make a copy of.
		 */
		Checkbox(const Checkbox &src);

		/**
		 * Destructor.
		 */
		virtual ~Checkbox();

		/**
		 * Assignment operator.
		 * @param src Checkbox to make a copy of.
		 * @return Reference to the modified CheckBox.
		 */
		Checkbox &operator=(const Checkbox &src);

		/**
		 * Gets the texture coordinates for the body.
		 * @return Texture coordinates used to map the texture on the body's
		 * polygon.
		 * @see RedBox::Animatable::frames
		 */
		const TextureCoordinates &getCurrentTextureCoordinates() const;

		/**
		 * Checks if the checkbox i checked.
		 * @return True if checked, false if not.
		 * @see RedBox::Checkbox::checked
		 */
		bool isChecked() const;

		/**
		 * Sets whether the checkbox is checked or not.
		 * @param newChecked Checked value to set.
		 * @see RedBox::Checkbox::checked
		 */
		void setChecked(bool newChecked);

		/**
		 * Checks the checkbox.
		 * @see RedBox::Checkbox::checked
		 */
		void check();

		/**
		 * Unchecks the checkbox.
		 * @see RedBox::Checkbox::checked
		 */
		void uncheck();

		/**
		 * Toggles the checkbox. If it was checked, it becomes unchecked and if
		 * it was unchecked, it becomes checked.
		 * @see RedBox::Checkbox::checked
		 */
		void toggleChecked();
	private:
		// Set to true if the checkbox is checked, false if not.
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

		/**
		 * Initializes the 4 animations for the sprite.
		 */
		void initializeAnimations();
	};

}

#endif // RB_CHECKBOX_H
