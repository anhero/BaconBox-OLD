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
		 * @param font Pointer to the font to be used by the GraphicString.
		 * @param newPosition Position, (0,0) by default. WARNING! The origin of
		 * a string is not the top left corner, but the left tip, right tip or
		 * middle of the baseline depending on the alignment.
		 * @param alignment Alignment of the string (left, center or right),
		 * left by default.
		 * @param direction String direction, useful when you want to support
		 * i18n, left to right by default.
		 * @see RedBox::TextAlignment
		 * @see RedBox::TextDirection
		 */
		GraphicString(Font* newFont, const Vec2& newPosition = Vec2(),
					  TextAlignment newAlignment = TextAlignment::LEFT,
					  TextDirection newDirection = TextDirection::LEFT_TO_RIGHT);

		/**
		 * Parameterized constructor.
		 * @param font Pointer to the font to be used by the GraphicString.
		 * @param newXPosition Horizontal position, 0 by default. WARNING! The
		 * origin of a string is not the top left corner, but the left tip,
		 * right tip or middle of the baseline depending on the alignment.
		 * @param newYPosition Vertical osition, (0,0) by default. WARNING! The
		 * origin of a string is not the top left corner, but the left tip,
		 * right tip or middle of the baseline depending on the alignment.
		 * @param alignment Alignment of the string (left, center or right),
		 * left by default.
		 * @param direction String direction, useful when you want to support
		 * i18n, left to right by default.
		 * @see RedBox::TextAlignment
		 * @see RedBox::TextDirection
		 */
		GraphicString(Font* newFont, float newXPosition, float newYPosition,
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
		 * Sets the graphic string's text from a UTF8 string.
		 * @param text New text for the GraphicString.
		 * @see RedBox::GraphicString::internalString
		 */
		void setText(const std::string& text);

		/**
		 * Sets the graphic string's text from a UTF32 string.
		 * @param text New text for the GraphicString.
		 * @see RedBox::GraphicString::internalString
		 */
		void setText(const RB_String32& text);

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

		/// Updates the graphic string.
		void update();

		/// Renders the graphic string.
		void render();

		/// Returns the width of the GraphicString
		float getWidth() const;

		/// Returns the height of the GraphicString
		float getHeight() const;

		/**
		 * Most changes to the string will break it (Ex: if you call setText
		 * after seting a color you will lose this color), so we need to call
		 * the setString() before rendering each time a change is made.
		 */
		void setString();

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

		/**
		 * Most changes to the string will break it (Ex: if you call setText
		 * after seting a color you will lose this color), so we need to call
		 * the setString() method before rendering each time a change is made.
		 * This boolean is set to true when the string is broken (set back to
		 * false when the setString function is called). When set to true, the
		 * setString will automatically get called before rendering.
		 */
		bool needReset;

		/// Alignment of the string (Left, right, center)
		TextAlignment alignment;

		/**
		 * Rendering direction of the string (Left to right, right to left, up
		 * to down)
		 */
		TextDirection direction;

		/// Unicode values of the GraphicString
		RB_String32 internalString;

		/// List of StringFX applied to the current string.
		std::list<StringFX> renderEffects;

		/// List of sprite representing each glyph.
		GlyphList characters;

		/// Calculated width of the string
		float widthCache;

		/**
		 * The setPosition part of the setString is complicated a bit, so we put
		 * it in a separate function.
		 * It's a bit more expensive in operation, but it's cleaner this way.
		 */
		void setPosition();

		/**
		 * Refreshes the main color for all glyphs.
		 */
		void setColor();

		/**
		 * Frees memory occupied by the sprites in the character list and
		 * flushes it.
		 */
		void flushCharacters();

	};
}

#endif
