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
		 * Default constructor
		 * If you use the default constructor, you need
		 * to call the setFont(Font*) function before setting any text.
		 */
		 GraphicString();
		
		///Constructor that set the rendering font with the one given in parameter.
		GraphicString(Font * font);
		
		/**
		 * Set the text of the GraphicString with an
		 * UTF8 string.
		 */
		void setText(std::string & text);
		
		/**
		 * Set the text of the GraphicString with an 
		 * UTF32 string.
		 */
		void setText(RB_String32 &  text);
		
		///Set the rendering direction of the string. (See the StringDirection enum)
		void setDirection(StringDirection direction);
		
		///Set the alignment of the string (Left, right or centered)
		void setAlignment(Alignment alignment);
		
		/**
		 * Set the position of the string.
		 * Depending on the alignment,
		 * the position will correspond to the left side, center
		 * or right side of the string.
		 */
		void setPosition(int x, int y);
		
		///Set the rendering font for the string.
		void setFont(Font * font);
		
		///Render the graphic string.
		void render();
		
		///Update the graphic string.
		void update();
		
	private:
		///X position
		int x;
		
		///Y position
		int y;
		
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
		
	};
}

#endif
