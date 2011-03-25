/**
 * @file
 * @ingroup TextDisplay
 */
#include <string>
#include "Glyph.h"
#include "RBString32.h"

#ifndef RB_FONT_H
#define RB_FONT_H

namespace RedBox{
	
	class FontImplementation;
	
	/** 
	 * Font use a font file (loaded by the resourceManager) to render glyphs.
     * @ingroup TextDisplay
     */
	class Font{
	public:
				
		/**
		 * Initialize the font renderer (freetype)
		 */
		static void initializeFontRenderer();
	
		
		/**
		 * Constructor. Load the font in memory.
		 * @param name Name of the font.
		 * @param path Path of the font.
		 */
		Font(const std::string& name, const std::string & path);
		
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
	private:
		
		/**
		 * Private implementation of the font (pimpl idiom)
		 * It is used to abstract/hide freetype from the engine user point of view.
		 * If we don't do this, the user will need to specify where are the freetype's header in
		 * is project.
		 */
		FontImplementation * fontPimpl;

	};
}

#endif
