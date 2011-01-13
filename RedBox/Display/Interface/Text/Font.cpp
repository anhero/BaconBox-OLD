#include "Font.h"

using namespace RedBox;

FT_Library Font::fontRenderer = 0;
std::map<std::string, Font*> Font::fontCache;


void Font::setupFontRenderer(){
	if(FT_Init_FreeType( &fontRenderer )){
		$ECHO("Can not load freetype");
	}
}

void Font::loadFont(const std::string & fontPath){
int error = FT_New_Face( fontRenderer, fontPath.c_str(), 0, &font);
	if ( error == FT_Err_Unknown_File_Format )
	 {
		$ECHO("Can't load font, unknow font file format");
	 }
	else if ( error )
	 {
		$ECHO("Can't load font, unknow error");		
	 }
	this-> fontPath = fontPath;
}

void Font::setPixelSize(int pixelSize){
	if(FT_Set_Pixel_Sizes(font, 0, pixelSize)){
		$ECHO("Can't set pixel size");
	}
	fontSize = pixelSize + "px";

}

void Font::setPointSize(int pointSize, int dpi){
	if(FT_Set_Char_Size(font, 0, pointSize*64, dpi, dpi)){
		$ECHO("Can't set point size");
	}
	fontSize = pointSize + "pt";
}

bitmapChar Font::getCharPixMap(wchar_t charCode){
	bitmapChar aBitmapChar;
	std::map<wchar_t, bitmapChar>::iterator cacheIterator = glyphCache.find(charCode);
	if(cacheIterator == glyphCache.end())
	 {
		FT_UInt glyph_index; 
		glyph_index = FT_Get_Char_Index(font, charCode);
		if(FT_Load_Glyph( font, glyph_index, FT_LOAD_RENDER )){
			$ECHO("Can't load glyph");
		}
		
		
		FT_Glyph currentGlyph;

	
		if(FT_Get_Glyph( font->glyph,  &currentGlyph)){
			$ECHO("Can't extract glyph from freetype glyph slot");
		}
		
		aBitmapChar.glyph = (FT_BitmapGlyph)currentGlyph;
		aBitmapChar.xAdvance = font->glyph->advance.x >> 6;
		aBitmapChar.topDisplacement = font->glyph->bitmap_top;
		aBitmapChar.leftDisplacement = font->glyph->bitmap_left;
		aBitmapChar.textureManagerKey = fontPath + "-" + fontSize + "-"; 
		aBitmapChar.textureManagerKey += charCode;
		glyphCache[charCode] = aBitmapChar;
	 }
	else {
		aBitmapChar = (*cacheIterator).second;
	}

	
	return aBitmapChar;
}

const std::string& Font::getFontPath(){
	return fontPath;
}
const std::string& Font::getFontSize(){
	return fontSize;
}

Font * Font::addFont(const std::string& fontName, Font * aFont){
	std::map<std::string, Font*>::iterator cacheIterator = fontCache.find(fontName);
	if(!(cacheIterator == fontCache.end()))
	{
		delete fontCache[fontName];
	}
	fontCache[fontName] = aFont;
	return aFont;
}

Font * Font::getFont(const std::string& fontName){
	std::map<std::string, Font*>::iterator cacheIterator = fontCache.find(fontName);
	if(cacheIterator == fontCache.end())
	 {
	 	return NULL;
	 }
	else{
		return (*cacheIterator).second;
	}

}


void Font::removeFont(const std::string& fontName){
	std::map<std::string, Font*>::iterator cacheIterator = fontCache.find(fontName);
	if(!(cacheIterator == fontCache.end()))
	 {
		delete fontCache[fontName];
	 }
}
