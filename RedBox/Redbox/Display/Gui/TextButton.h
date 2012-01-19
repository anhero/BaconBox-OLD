/**
 * @file
 * @ingroup GUI
 */
#ifndef RB_TEXT_BUTTON_H
#define RB_TEXT_BUTTON_H

#include "Button.h"
#include "GraphicString.h"

namespace RedBox {
	/**
	 * Represents a simple buttons that has graphics for 4 states.
	 * @ingroup GUI
	 */
	class TextButton : public Button {
	public:
		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, each button frame will be equal to the texture's width
		 * divided by 4.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param newFont Font pointer to use as the text's font.
		 * @param newText UTF8 string to use as the string's text.
		 * @param newTextOffset Offset to apply to the text when the button is
		 * pressed.
		 * @param startingPosition Starting position at which to place the
		 * button.
		 * @param newSize Size of the button.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit TextButton(TexturePointer newTexture,
		                    FontPointer newFont,
		                    const std::string &newText = std::string(),
		                    const Vector2 &newTextOffset = Vector2(3.0f, 3.0f),
		                    const Vector2 &startingPosition = Vector2(),
		                    const Vector2 &newSize = Vector2(),
		                    const Vector2 &newTextureOffset = Vector2());

		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, each button frame will be equal to the texture's width
		 * divided by 4.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param newFont Font pointer to use as the text's font.
		 * @param newText Unicode string to use as the string's text.
		 * @param newTextOffset Offset to apply to the text when the button is
		 * pressed down.
		 * @param startingPosition Starting position at which to place the
		 * button.
		 * @param newSize Size of the button.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit TextButton(TexturePointer newTexture,
		                    FontPointer newFont,
		                    const String32 &newText = String32(),
		                    const Vector2 &newTextOffset = Vector2(3.0f, 3.0f),
		                    const Vector2 &startingPosition = Vector2(),
		                    const Vector2 &newSize = Vector2(),
		                    const Vector2 &newTextureOffset = Vector2());

		/**
		 * Copy constructor.
		 * @param src TextButton to make a copy of.
		 */
		TextButton(const TextButton &src);

		/**
		 * Destructor.
		 */
		virtual ~TextButton();

		/**
		 * Assignment operator.
		 * @param src TextButton to make a copy of.
		 * @return Reference to the modified TextButton.
		 */
		TextButton &operator=(const TextButton &src);

		/**
		 * Renders the body in the context.
		 */
		virtual void render();

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is used to mask
		 * the next rendered renderable body (if the next renderable body is set
		 * as a masked renderable body).
		 */
		virtual void mask();

		/**
		 * Undo what the mask function did. This function must be once after the
		 * masked renderable body has been rendered.
		 */
		virtual void unmask();

		/**
		 * Sets the renderable body used to mask the parent renderstep.
		 * @param newMask A mask sprite.
		 * @param inverted Sets this parameter to true if you want to invert
		 * the effect of the mask. False by default.
		 */
		virtual void setMask(Maskable *newMask, bool inverted = false);

		/**
		 * Gets the texture coordinates for the body.
		 * @return Texture coordinates used to map the texture on the body's
		 * polygon.
		 * @see RedBox::Animatable::frames
		 */
		const TextureCoordinates &getCurrentTextureCoordinates() const;

		using Button::move;

		/**
		 * Moves the Positionable horizontally and vertically.
		 * @param xDelta Value to add to the Positionable's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the Positionable to the left.
		 * @param yDelta Value to add to the Positionable's vertical position (in
		 * pixels). Positive value moves the Positionable down and a negative
		 * value moves the Positionable up.
		 * @see RedBox::Positionable::move(const Vector2& delta);
		 * @see RedBox::Positionable::position
		 */
		virtual void move(float xDelta, float yDelta);

		using Button::scaleFromPoint;

		/**
		 * Scales the body from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the body will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the body will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::Transformable::scaling
		 */
		virtual void scaleFromPoint(float xScaling, float yScaling,
		                            const Vector2 &fromPoint);

		/**
		 * Rotates the graphic body from a point.
		 * @param rotationAngle Angle to rotate the graphic body.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::Transformable::angle
		 */
		virtual void rotateFromPoint(float rotationAngle,
		                             const Vector2 &rotationPoint);

		/**
		 * Gets the graphic string's font.
		 * @return Pointer to the graphic string's font.
		 * @see RedBox::GraphicString::font
		 */
		Font *getFont() const;

		/**
		 * Sets the graphic string's font and refreshes the text to use the
		 * given font. Does nothing and keeps the old font if the new font is
		 * NULL.
		 * @param newFont Pointer to the new font to use.
		 */
		void setFont(FontPointer newFont);

		/**
		 * Gets the graphic string's text in UTF8.
		 * @return A copy of the graphic string's UTF32 string in UTF8 format.
		 * @see RedBox::GraphicString::text
		 */
		std::string getText() const;

		/**
		 * Sets the graphic string's text.
		 * @param newText UTF8 string to use as the graphic string's text.
		 * Converts it to UTF32 to store it.
		 * @see RedBox::GraphicString::text
		 */
		void setText(const std::string newText);

		/**
		 * Gets the graphic string's text in UTF32.
		 * @return String used by the graphic string as the text.
		 * @see RedBox::GraphicString::text
		 */
		const String32 &getUtf32Text() const;

		/**
		 * Sets the graphic string's text.
		 * @param newText UTF32 string to use as the graphic string's text.
		 * @see RedBox::GraphicString::text
		 */
		void setUtf32Text(const String32 &newText);

		/**
		 * Gets the text's color.
		 * @return Text's color.
		 * @see RedBox::TextButton::text
		 */
		const Color &getTextColor() const;

		/**
		 * Sets the text's color.
		 * @param newTextColor Text's new color.
		 * @see RedBox::TextButton::text
		 */
		void setTextColor(const Color &newTextColor);

		/**
		 * Sets the offset to apply to the text when the button is pressed.
		 * @return Horizontal and vertical offset to apply to the text when the
		 * button is pressed.
		 * @see RedBox::TextButton::textOffset
		 */
		const Vector2 &getTextOffset() const;

		/**
		 * Gets the offset applied to the text when the button is pressed.
		 * @param newTextOffset Horizontal and vertical offset applied to the
		 * text when the button is pressed.
		 * @see RedBox::TextButton::textOffset
		 */
		void setTextOffset(const Vector2 &newTextOffset);
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

		/**
		 * Positions the text at the center of the button.
		 */
		void refreshTextPosition();

		/// Represents the graphic string used for the button's text.
		GraphicString<Collidable> text;

		/**
		 * Offset to apply to the text when the button is pressed.
		 */
		Vector2 textOffset;
	};

}

#endif // RB_TEXT_BUTTON_H
