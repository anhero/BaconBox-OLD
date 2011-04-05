/**
 * @file
 * @ingroup TextDisplay
 */
#include <ft2build.h>
#include <freetype/freetype.h>
#include <string>
#include "Glyph.h"
#include "RBString32.h"
#include <vector>
#include <map>
#ifndef RB_FONTIMPLEMENTATION_H
#define RB_FONTIMPLEMENTATION_H

namespace RedBox{
	/** 
	 * Font implementation is used to hide the freetype private member in the font interface (pimpl idiom)
	 * It should not be used directly when developing a game, you should use the Font class instead.
	 * With the pimpl idiom, we don't have to specify where are the freetype's header in the redboxapp project.
     * @ingroup TextDisplay
     */
	class FontImplementation{
		friend class Font;
	private:
				
		/**
		 * Initialize the font renderer (freetype)
		 */
		static void initializeFontRenderer();
	
		
		/**
		 * Constructor. Load the font in memory.
		 * @param name Name of the font.
		 * @param path Path of the font.
		 */
		FontImplementation(const std::string& name, const std::string & path);
		
		/**
		 * Return the name of the font.
		 */
		std::string getName();
		
		/**
		 * Return the glyph specified by the unicode value.
		 * The size of the font should be set before calling 
		 * this function.
		 */
		Glyph * getGlyph(RB_Char32 unicodeValue);
		
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
		///Return the lineHeight (automatic or manual depending on the case, automatic by default)
		int getLineHeight();
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
	
		///Name of the font
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
		std::map<std::string, std::map< RB_Char32, Glyph*>* > glyphCache;
		
		///Global font renderer (Freetype library).
		static FT_Library fontRenderer;


	};
}

#endif
