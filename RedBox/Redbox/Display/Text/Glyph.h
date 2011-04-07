/**
 * @file
 * @ingroup TextDisplay
 */

#ifndef RB_GLYPH_H
#define RB_GLYPH_H

#include "TextureInfo.h"
namespace RedBox{
	/** 
	 * This class contain the needed informations to render a glyph. 
     * @ingroup TextDisplay
     */
	class Glyph{
	public:
	
		/**
		 * Set the horizontal advance with the given parameters. 
		 * The horizontal Advance is the amount of pixels we need 
		 * to add to the "pen" position before rendering the next
		 * glyph when we are drawing in horizontal layout.
		 */
		void setHoriAdvance(int horiAdvance);
		
		/**
		 * Return the horizontal advance. 
		 * Which is the amount of pixels we need to
		 * add to the current "pen" position before rendering
		 * the next glyph when we are drawing in horizontal layout.
		 */
		int getXAdvance();
		
		
		/**
		 * Set the horizontal x bearing with the given parameters.
		 * Which is an amount in pixel we must add to the
		 * current cursor position before rendering the current 
		 * glyph in horizontal layout. 
		 * (It's the space between each character)
		 */
		void setHoriBearingX(int horiBearingX);
		
		/**
		 * Return the horizontal x bearing.
		 * Which is an amount in pixel we must add to the
		 * current cursor position before rendering the current 
		 * glyph in horizontal layout. 
		 * (It's the space between each character)
		 */
		int getHoriBearingX();
		
		
		/**
		 * Set the horizontal y bearing with the given parameters.
		 * Which is an amount in pixel we must add to the vertical position
		 * before rendering the glyph in horizontal layout.
		 * (We need this value because character are not all drawn 
		 * at the the same height EX. 'y' go below the baseline)
		 */
		void setHoriBearingY(int horiBearingY);
		
		/**
		 * Return the horizontal y bearing.
		 * Which is an amount in pixel we must add to the vertical position
		 * before rendering the glyph in horizontal layout.
		 * (We need this value because character are not all drawn 
		 * at the the same height EX. 'y' go below the baseline)
		 */
		int getHoriBearingY();
		
		/**
		 * Set the TextureInfo object of the glyph with the
		 * given one.
		 */
		void setTextureInfo(TextureInfo * textureInfo);
		
		/**
		 * Return the TextureInfo object of the glyph.
		 */
		TextureInfo * getTextureInfo();
		
		///Return the height of the glyph in pixels
		int getHeight();
		
		///Set the height of the glyph in pixels 
		void setHeight(int height);
		
		///Return the width of the glyph in pixels.
		int getWidth();
		
		///Set the width of the glyph in pixels.
		void setWidth(int width);
		
	private:
		/**
		 * Amount of pixels we need to
		 * add to the current x position before rendering
		 * the next character.
		 */
		int horiAdvance;
		
		
		/**
		* Amount in pixel we must add to the vertical position
		* before rendering the glyph in horizontal layout.
		* (We need this value because character are not all drawn 
		* at the the same height EX. 'y' go below the baseline)
		*/
		int horiBearingY;
		
		/**
		 * Amount in pixel we must add to the
		 * current cursor position before rendering the current 
		 * glyph in horizontal layout. 
		 * (It's the space between each character)
		 */
		int horiBearingX;
		
		///Glyph width in pixels.
		int width;
		
		///Glyph height in pixels
		int height;
		
		///Hold the texture handle and texture size.
		TextureInfo * textureInfo;

	};
}

#endif