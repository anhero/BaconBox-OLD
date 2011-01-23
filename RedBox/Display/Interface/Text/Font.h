/**
 * @file
 * @ingroup TextDisplay
 */
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>

#include <map>
#include "Debug.h"
#ifndef __FONT_H
#define __FONT_H


namespace RedBox {
    /**
     * @ingroup TextDisplay
     */
	struct bitmapChar{
		std::string textureManagerKey; //was used for OpenGL rendering, can't tell at the moment of writing
										   //if it will be used with DirectX

		int topDisplacement;
		int leftDisplacement;
		int xAdvance;
		FT_BitmapGlyph glyph; //Contain the buffer and info on the buffer, 
							  //we keep directly the glyph so we are able to release the memory later
	};
	/** 
     * @ingroup TextDisplay
     */
	class Font {
	private:
		static std::map<std::string, Font*> fontCache;
		static FT_Library fontRenderer;
		FT_Face font;
		std::map<wchar_t, bitmapChar> glyphCache;
		std::string fontPath; //use to create the texture manager key (used for rendering)
		std::string fontSize; //use to create the texture manager key (used for rendering)
	public:
		//Use to create the texture manager key
		const std::string& getFontPath();
		const std::string& getFontSize();
		
		void loadFont(const std::string & fontPath);
		void setPixelSize(int pixelSize);
		void setPointSize(int pointSize, int dpi);
		
		bitmapChar getCharPixMap(wchar_t charCode);
		
		static void setupFontRenderer();
		static Font * addFont(const std::string& fontName, Font * aFont); 
		static Font * getFont(const std::string& fontName);
		static void removeFont(const std::string& fontName);
		
	};
}
#endif