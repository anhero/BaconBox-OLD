#if 0
/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef RB_GRAPHICSTRING_H
#define RB_GRAPHICSTRING_H

#include <list>

#include "GraphicBody.h"
#include "StringFX.h"
#include "Sprite.h"
#include "RBString32.h"
#include "Glyph.h"
#include "TextAlignment.h"
#include "TextDirection.h"
#include "Color.h"

namespace RedBox {
	class Font;
	/**
	 * A GraphicString is a GraphicBody object that print text
	 * to the screen.
	 * @ingroup Group
	 */
	class GraphicString : public GraphicBody {
	public:
		/**
		 * Parameterized constructor.
		 * @param newAlignment Alignment of the string (left, center or right),
		 * left by default.
		 * @param newDirection String direction, useful when you want to support
		 * i18n, left to right by default.
		 * @see RedBox::GraphicString::alignment
		 * @see RedBox::GraphicString::direction
		 */
		GraphicString(Font* newFont,
		              TextAlignment newAlignment = TextAlignment::LEFT,
		              TextDirection newDirection = TextDirection::LEFT_TO_RIGHT);

		/**
		 * Gets the rendering font for the string.
		 * @return Pointer to the current rendering font used.
		 * @see RedBox::GraphicString::font
		 */
		Font* getFont();

		/**
		 * Sets the rendering font for the string.
		 * @param newFont Pointer to the font to use for displaying the graphic
		 * string.
		 * @param RedBox::GraphicString::font
		 */
		void setFont(Font* newFont);

		/**
		 * Gets the graphic string's color.
		 * @return Current color used to display the graphic string.
		 * @see RedBox::GraphicString::color
		 */
		const Color& getColor() const;

		/**
		 * Sets the graphic string's color.
		 * @param newcolor New color to use to display the graphic string.
		 * @see RedBox::GraphicString::color
		 */
		void setColor(const Color& newColor);

		/**
		 * Gets the graphic string's alignment.
		 * @return Graphic string's current text alignment. Either left, center
		 * or right.
		 * @see RedBox::GraphicString::alignment
		 */
		TextAlignment getAlignment() const;

		/**
		 * Sets the graphic string's alignment.
		 * @param newAlignment New text alignment. It's either left, center or
		 * right.
		 * @see RedBox::GraphicString::alignment
		 */
		void setAlignment(TextAlignment newAlignment);

		/**
		 * Gets the rendering direction.
		 * @return Current rendering direction.
		 * @see RedBox::GraphicString::direction
		 */
		TextDirection getDirection() const;

		/**
		 * Sets the rendering direction.
		 * @param newDirection New rendering direction.
		 * @see RedBox::GraphicString::direction
		 */
		void setDirection(TextDirection newDirection);

		/**
		 * Gets the graphic string's text in utf8.
		 * @return Utf8 string containing the graphic string's text.
		 */
		std::string getText() const;

		/**
		 * Gets the graphic string's text in utf32.
		 * @return Utf32 string containing the graphic string's text.
		 */
		const String32& getTextUtf32() const;

		/**
		 * Sets the graphic string's text from a UTF8 string.
		 * @param text New text for the GraphicString.
		 * @see RedBox::GraphicString::internalString
		 */
		void setText(const std::string& newText);

		/**
		 * Sets the graphic string's text from a UTF32 string.
		 * @param text New text for the GraphicString.
		 * @see RedBox::GraphicString::internalString
		 */
		void setText(const String32& newText);

		using GraphicBody::setPosition;

		/**
		 * Sets the GraphicString's position. Depending on the alignment, the
		 * position will correspond to the left side, center or right side of
		 * the string.
		 * WARNING! The origin of a string (In horizontal rendering) is the
		 * top-left, top-center or top-right (depending on the alignment of the
		 * line height. Some character CAN be higher than the line height, so
		 * don't assume that every character are lower than the position you
		 * set. For vertical rendering it's the same thing but with a horizontal
		 * line "height" and a top-left, middle-left, bottom-left origin.
		 */
		void setPosition(float newXPosition, float newYPosition);

		using GraphicBody::scaleFromPoint;

		/**
		 * Scales the graphic strin from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the graphic string will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the graphic string will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::GraphicBody::scaling
		 */
		virtual void scaleFromPoint(float xScaling, float yScaling,
		                            const Vector2& fromPoint);

		/**
		 * Rotates the graphic string from a point.
		 * @param rotationAngle Angle to rotate the graphic string.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::GraphicBody::angle
		 */
		void rotateFromPoint(float rotationAngle, const Vector2& rotationPoint);

		/**
		 * Set the string size in pixel.
		 * Warning: character wont necesserly be "pixelSize" wide.
		 * @param pixelSize New pixel size. Characters will not necessarily have
		 * that width.
		 */
		void setPixelSize(int pixelSize);

		/**
		 * Set the string size in font point (1/72 inch).
		 * The function require the dpi to fix the appropriate
		 * pixel size.
		 * @param pointSize Size in font point (1/72 inch)
		 * @param dpi DPI of the screen (pixel per inch)
		 */
		void setPointSize(int pointSize, int dpi);

		/**
		 * Tell the rendering font to use automatic line height (which is not
		 * always availlable, but it's there most of the time.
		 */
		void setAutomaticLineHeight();

		/**
		 * Tells the rendering font to use the given line height and resets the
		 * string. Call setAutomaticLineHeight() to return to the default
		 * automatic line height.
		 * @param lineHeight New line height (in pixels).
		 */
		void setManualLineHeight(int lineHeight);

		/**
		 * Updates the graphic string.
		 */
		void update();

		/**
		 * Renders the graphic string.
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
		 * MUST be once after the masked graphic string has been rendered.
		 */
		void unmask();

		/**
		 * Gets the graphic body masking the current graphic string.
		 * @return Pointer to the graphic string's mask.
		 */
		GraphicBody* getMask();

		/**
		 * Sets the graphic string used to mask the graphic string.
		 * @param newMask A mask graphic string.
		 * @param inversed Set this parameter to true if you want to inverse
		 * the effect of the mask. False by default.
		 */
		void setMask(GraphicBody* newMask, bool inversed = false);

		/**
		 * Gets the graphic string's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const;

		/**
		 * Gets the graphic string's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const;

		/**
		 * Gets the font's line height.
		 * @return Font's line height (in pixels). If no valid font is set,
		 * returns 0.
		 */
		int getLineHeight() const;

		/**
		 * Creates a copy of the current graphic string.
		 * @return Pointer to the new graphic string.
		 */
		GraphicBody* clone() const;
	private:
		typedef std::list<std::pair<Glyph*, Sprite*> > GlyphList;

		/// Rendering font.
		Font* font;

		/// RGBA color components of the string. The range is 0 to 255.
		Color color;

		/// Alignment of the string (Left, right, center)
		TextAlignment alignment;

		/**
		 * Rendering direction of the string (Left to right, right to left, up
		 * to down)
		 */
		TextDirection direction;

		/// Unicode values of the GraphicString
		String32 text;

		/// List of StringFX applied to the current string.
		std::list<StringFX> renderEffects;

		/// List of sprite representing each glyph.
		GlyphList characters;

		/**
		 * Frees memory occupied by the sprites in the character list and
		 * flushes it.
		 */
		void clearCharacters();

		/**
		 * Finds the real horizontal and vertical position and sets graphic
		 * string's position to them.
		 */
		void refreshPosition();
	};
}

#endif
#endif
