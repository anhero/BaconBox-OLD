/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef RB_GLYPH_INFORMATION_H
#define RB_GLYPH_INFORMATION_H

#include "BaconBox/Vector2.h"

namespace BaconBox {
	/**
	 * This struct contain the needed informations to render a glyph.
	 * @ingroup TextDisplay
	 */
	struct TextureInformation;
	struct GlyphInformation {
	public:
		/**
		 * Amount of pixels we need to add to the current horizontal and
		 * vertical position before rendering the next character. The horizontal
		 * advance is the amount of pixels we need to add to the "pen" position
		 * before rendering the next glyph when we are drawing in horizontal
		 * layout.
		 */
		Vector2 advance;

		/**
		 * Amount in pixels we must add to the current cursor position before
		 * rendering the current glyph in horizontal layout. (It's the space
		 * between each character)
		 * Amount in pixel we must add to the vertical position
		 * before rendering the glyph in horizontal layout.
		 * (We need this value because character are not all drawn
		 * at the same height EX. 'y' go below the baseline)
		 */
		Vector2 horizontalBearing;

		/// Glyph's size.
		Vector2 size;

		/// Pointer to the texture handle and texture size.
		TextureInformation *textureInformation;

		/**
		 * Default constructor.
		 */
		GlyphInformation();

		/**
		 * Parameterized constructor.
		 * @param newAdvance Advance of the glyph.
		 * @param newHorizontalBearing Horizontal bearing.
		 * @param newSize Size of the glyph.
		 * @param newTextureInformation Pointer to the glyph's texture
		 * information.
		 */
		GlyphInformation(const Vector2 &newAdvance,
		                 const Vector2 &newHorizontalBearing,
		                 const Vector2 &newSize,
		                 TextureInformation *newTextureInformation);

		/**
		 * Copy constructor.
		 * @param src GlyphInformation to make a copy of.
		 */
		GlyphInformation(const GlyphInformation &src);

		/**
		 * Assignment operator.
		 * @param src GlyphInformation to make a copy of.
		 * @return Reference to the modified GlyphInformation.
		 */
		GlyphInformation &operator=(const GlyphInformation &src);
	};

}

#endif // RB_GLYPH_INFORMATION_H
