#include "Font.h"
#include "Debug.h"
#include "ResourceLoader.h"
#include "MathHelper.h"
#include <sstream>
using namespace RedBox;

FT_Library Font::fontRenderer = NULL;


void Font::initializeFontRenderer(){
	if(FT_Init_FreeType( &fontRenderer )){
		$ECHO("Can not load freetype");
	}
}

std::string Font::getName(){
	return name;
}


Font::Font(std::string& name, std::string path){
	
	this->name = name;

	//We load the font face
	int error = FT_New_Face( fontRenderer, path.c_str(), 0, &font);
	if ( error == FT_Err_Unknown_File_Format )
	{
		$ECHO("Can't load font, unknow font file format");
	}
	else if ( error )
	{
		$ECHO("Can't load font, unknow error");		
	}
}


Glyph * Font::getGlyph(RB_Char32 unicodeValue){
	std::map<std::string, std::map< RB_Char32, Glyph*> >::iterator i = glyphCache.find(size);
	Glyph * aGlyph;
	if(i != glyphCache.end()){
		std::map<RB_Char32, Glyph*>::iterator j = i->second.find(unicodeValue);
		if (j != i->second.end()) {
			aGlyph = j->second;
		}
	}
	
	if (aGlyph == NULL) {
		FT_UInt glyph_index; 
		glyph_index = FT_Get_Char_Index(font, unicodeValue);
		if(FT_Load_Glyph( font, glyph_index, FT_LOAD_RENDER )){
			$ECHO("Can't load glyph");
		}
//		FT_Glyph currentGlyph;
//		if(FT_Get_Glyph( font->glyph,  &currentGlyph)){
//			$ECHO("Can't extract glyph from freetype glyph slot");
//		}
		
		
		int glyphWidth = font->glyph->bitmap.width;
		int glyphHeight = font->glyph->bitmap.rows;
		
		int widthPoweredToTwo = MathHelper::nextPowerOf2(glyphWidth);
		int heightPoweredToTwo = MathHelper::nextPowerOf2(glyphHeight);
		unsigned char * poweredTo2Buffer =  new unsigned char [widthPoweredToTwo * heightPoweredToTwo];	
		
		for(int j = 0; j < glyphWidth; j++){
			for(int k = 0; k < glyphHeight; k++) {
				poweredTo2Buffer[k*widthPoweredToTwo + j] = font->glyph->bitmap.buffer[k* glyphWidth + j];
			}
		}
		
		
		
		aGlyph = new Glyph();
		std::stringstream key;
		key << name << "-" << size << "-" << unicodeValue;
		aGlyph->setTextureInfo(*ResourceLoader::addTexture(key.str(),poweredTo2Buffer, widthPoweredToTwo, heightPoweredToTwo));
		aGlyph->setHoriAdvance(font->glyph->advance.x >> 6);
		
		
		aGlyph->setHoriBearingX( font->glyph->bitmap_left);
		
		aGlyph->setHoriBearingY( font->glyph->bitmap_top);

		
		float * texCoord = aGlyph->getTextureCoordinates();
		texCoord[0] = 0;
		texCoord[1] = 0;
		
		texCoord[2] = glyphWidth / widthPoweredToTwo;
		texCoord[3] = 0;
		
		texCoord[4] = 0;
		texCoord[5] = glyphHeight / heightPoweredToTwo;
		
		texCoord[6] = texCoord[2];
		texCoord[7] = texCoord[5];
	}
		
	return aGlyph;
	

}



void Font::setPixelSize(int pixelSize){
	if(FT_Set_Pixel_Sizes(font, 0, pixelSize)){
		$ECHO("Can't set pixel size");
	}
	size = pixelSize + "px";
	
}


void Font::setPointSize(int pointSize, int dpi){
	if(FT_Set_Char_Size(font, 0, pointSize*64, dpi, dpi)){
		$ECHO("Can't set point size");
	}
	size = pointSize + "pt";
}

