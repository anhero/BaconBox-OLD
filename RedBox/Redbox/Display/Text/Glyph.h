/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef RB_GLYPH_H
#define RB_GLYPH_H

#include "Object.h"

#include "Vec2.h"

namespace RedBox{
	class TextureInfo;
	/** 
	 * This class contain the needed informations to render a glyph. 
     * @ingroup TextDisplay
     */
	struct Glyph : public Object {
		/**
		 * Amount of pixels we need to add to the current horizontal and
		 * vertical position before rendering the next character. The horizontal
		 * advance is the amount of pixels we need to add to the "pen" position
		 * before rendering the next glyph when we are drawing in horizontal
		 * layout.
		 */
		Vec2 advance;

		/**
		 * Amount in pixels we must add to the current cursor position before
		 * rendering the current glyph in horizontal layout. (It's the space
		 * between each character)
		 * Amount in pixel we must add to the vertical position
		 * before rendering the glyph in horizontal layout.
		 * (We need this value because character are not all drawn
		 * at the the same height EX. 'y' go below the baseline)
		 */
		Vec2 horizontalBearing;

		/// Glyph's size.
		Vec2 size;

		/// Pointer to the texture handle and texture size.
		TextureInfo* textureInfo;

		/**
		 * Default constructor.
		 */
		Glyph();

		/**
		 * Copy constructor.
		 * @param src Glyph to make a copy of.
		 */
		Glyph(const Glyph& src);

		/**
		 * Assignment operator overload.
		 * @param src Glyph to make a copy of.
		 * @return Reference to the modified glyph.
		 */
		Glyph& operator=(const Glyph& src);
	};
}

#endif
