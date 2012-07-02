/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef RB_FONT_IMPLEMENTATION_H
#define RB_FONT_IMPLEMENTATION_H

#include <ft2build.h>
#include <freetype/freetype.h>
#include <string>
#include <vector>
#include <map>

#include "BaconBox/Display/Text/GlyphInformation.h"
#include "BaconBox/Display/RBString32.h"

namespace BaconBox {
	/**
	 * Font implementation is used to hide the freetype private member in the
	 * font interface (pimpl idiom) It should not be used directly when
	 * developing a game, you should use the Font class instead. With the pimpl
	 * idiom, we don't have to specify where are the freetype's header in the
	 * BaconBoxapp project.
	 * @ingroup TextDisplay
	 */
	class FontImplementation {
		friend class Font;
	private:
		typedef std::map<std::string, std::map< Char32, GlyphInformation *> > GlyphCache;
		/**
		 * Initialize the font renderer (freetype).
		 */
		static void initializeFontRenderer();

		/**
		 * Constructor. Load the font in memory.
		 * @param newName Name of the font.
		 * @param newPath Path of the font.
		 */
		FontImplementation(const std::string &newName, const std::string &newPath);

		/**
		 * Destructor
		 */
		~FontImplementation();

		/**
		 * Return the name of the font.
		 */
		const std::string &getName() const;

		/**
		 * Gets the glyph specified by the unicode value.
		 * The size of the font should be set before calling
		 * this function.
		 */
		const GlyphInformation *getGlyphInformation(Char32 unicodeValue);

		/**
		 * Set the font size in pixel.
		 * Warning: character wont necesserly be "pixelSize" wide.
		 */
		void setPixelSize(int pixelSize);

		/**
		 * Set the font size in font point (1/72 inch).
		 * The function require the dpi to fix the appropriate
		 * pixel size.
		 * @param pointSize Size in font point (1/72 inch)
		 * @param dpi DPI of the screen (pixel per inch)
		 */
		void setPointSize(int pointSize, int dpi);

		/**
		 * Gets the line's height (automatic or manual depending on the case,
		 * automatic by default).
		 * @return Line's height in pixels.
		 */
		int getLineHeight() const;

		/**
		 * Tell the rendering font to use automatic line height (which is not always availlable,
		 * but it's there most of the time.
		 */
		void setAutomaticLineHeight();

		/**
		 * Tell the rendering font to use the given line height and reset the string.
		 * Call setAutomaticLineHeight() to return to the default automatic line height.
		 */
		void setManualLineHeight(int newLineHeight);

		/// Name of the font
		std::string name;

		/**
		 * Size of the font.
		 * It can be in pixel or in point (1/72 inch).
		 * The size (int) is append with the unit. "px"
		 * for pixel, "pt" for point.
		 * Ex. "12px" or "14pt"
		 */
		std::string size;

		/**
		 * Freetype face. It contain the vector
		 * data of the font and function render glyphs and
		 * retrieve glyphs' metric.
		 */
		FT_Face font;

		bool automaticLineHeight;

		int lineHeight;

		/**
		 * Vector of texture key used by the font.
		 * Used to unload textures when unloading
		 * a font.
		 */
		std::vector<std::string> texturesKey;

		/**
		 * Glyph are cached in this map by size then
		 * by unicode value.
		 * The first map key is the size (Ex. "12pt"),
		 * the value is a second map, which key is the
		 * unicode value and value a pointer to the glyph.
		 *(Size, (unicode value, glyph*))
		 */
		GlyphCache glyphCache;

		/// Global font renderer (Freetype library).
		static FT_Library fontRenderer;


	};
}

#endif
