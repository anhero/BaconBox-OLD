/**
 * @file
 * @ingroup TextDisplay
 */

#ifndef RB_GRAPHICSTRING_H
#define RB_GRAPHICSTRING_H

#include "Renderable.h"
#include "Font.h"
#include "StringFX.h"
#include "Sprite.h"
#include "RBString32.h"
#include "Glyph.h"
#include <list>
namespace RedBox{
	/** 
	 * Rendering direction for a string.
	 * Some language require right to left rendering.
     * @ingroup TextDisplay
     */
	enum StringDirection{
			leftToRight,
			rightToLeft,
			//upToDown  //not implemented yet
	};
	
	/** 
	 * Alignment of the string.
     * @ingroup Group
     */
	enum Alignment{
		left,
		right,
		center
	};
	
	/** 
	 * A GraphicString is a renderable object that print text
	 * to the screen.
     * @ingroup Group
     */
	class GraphicString : public Renderable{
	public:
		
		/**
		 * Constructor
		 * @param font Rendering font.
		 * @param x X position, 0 by default. WARNING! The origin of a string is not 
		 * the top left corner, but the left tip, right tip or middle of the baseline depending on the alignment.
		 * @param y Y position, 0 by default. WARNING! The origin of a string is not 
		 * the top left corner, but the left tip, right tip or middle of the baseline depending on the alignment.
		 * @param alignment Alignment of the string (left, center or right), left by default.
		 * @param direction String direction, useful when you want to support i18n (leftToRight, rightToLeft, 
		 * upToDown), leftToRight by default.
		 */
		GraphicString(Font * font, int x = 0, int y = 0, Alignment alignment = left, StringDirection direction = leftToRight);
		
		/**
		 * Set the text of the GraphicString with an
		 * UTF8 string.
		 */
		void setText(const std::string & text);
		
		/**
		 * Set the text of the GraphicString with an 
		 * UTF32 string.
		 */
		void setText(const RB_String32 &  text);
		
		///Set the rendering direction of the string. (See the StringDirection enum)
		void setDirection(StringDirection direction);
		
		///Set the alignment of the string (Left, right or centered)
		void setAlignment(Alignment alignment);
		
		
		///Set the color of the string with the given RGBA components 
		void setColor(int red, int green, int blue, int alpha);
		
		/**
		 * Set the position of the string.
		 * Depending on the alignment,
		 * the position will correspond to the left side, center
		 * or right side of the string.
		 * WARNING! The origin of a string (In horizontal rendering) is the top-left, top-center or top-right (depending on the
		 * alignment of the line height. Some character CAN be higher than the line height, so don't assume
		 * that every character are lower than the position you set.
		 * For vertical rendering it's the same thing but with a horizontal line "height"
		 * and a top-left, middle-left, bottom-left origin.
		 */
		void setPosition(int x, int y);
		
		
		/**
		 * Set the string size in pixel.
		 * Warning: character wont necesserly be "pixelSize" wide.
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
		 * Tell the rendering font to use automatic line height (which is not always availlable,
		 * but it's there most of the time.
		 */
		void setAutomaticLineHeight();
		
		/**
		 * Tell the rendering font to use the given line height and reset the string.
		 * Call setAutomaticLineHeight() to return to the default automatic line height.
		 */
		void setManualLineHeight(int lineHeight);
		
		
		///Set the rendering font for the string.
		void setFont(Font * font);
		
		///Render the graphic string.
		void render();
		
		///Update the graphic string.
		void update();
		
	private:
		/**
		 * Most change to the string will break it (Ex: if you call setText after seting a color 
		 * you will lose this color), so we need to call the setString() before rendering each time a change is made.
		 */
		void setString();
		
		/**
		 * The setPosition part of the setString is complicated a bit, so we put it in a separate function.
		 * It's a bit more expensive in operation, but it's cleaner this way.
		 */
		void setPosition();
		///Free memory occupied by the sprites in the characters list and flush it.
		void flushCharacters();
		
		///X position
		int x;
		
		///Y position
		int y;
		
		///RGBA color components of the string. The range is 0 to 255.
		int color[4];
		
		/**
		 * Most change to the string will break it (Ex: if you call setText after seting a color 
		 * you will lose this color), so we need to call the setString() before rendering each time a change is made.
		 * This boolean is set to true when the string is broken (set back to false when the setString function is called).
		 * When set to true, the setString will automatically get called before rendering.
		 */
		bool needReset;
		///Rendering font.
		Font * font;
		
		///List of StringFX applied to the current string.
		std::list<StringFX> renderEffects;
		
		///Alignment of the string (Left, right, center)
		Alignment alignment;
		
		///Rendering direction of the string (Left to right, right to left, up to down)
		StringDirection direction;
		
		///List of sprite representing each glyph.
		std::list<std::pair<Glyph*, Sprite*> > characters;
		
		///Unicode values of the GraphicString
		RB_String32 internalString;
		
	};
}

#endif
