#include "FontImplementation.h"
#include "Debug.h"
#include "ResourceManager.h"
#include "MathHelper.h"
#include "Parser.h"
#include <sstream>
#include <freetype/ftglyph.h>
#include <algorithm>

using namespace RedBox;

FT_Library FontImplementation::fontRenderer = NULL;


void FontImplementation::initializeFontRenderer(){
	if(FT_Init_FreeType( &fontRenderer )){
		RB_ECHO("Can not load freetype");
	}
}

std::string FontImplementation::getName(){
	return name;
}


FontImplementation::FontImplementation(const std::string& name, const std::string & path){
	
	this->name = name;
	
	//We load the font face
	int error = FT_New_Face( fontRenderer, path.c_str(), 0, &font);
	if ( error == FT_Err_Unknown_File_Format )
	{
		RB_ECHO("Can't load font, unknow font file format");
	}
	else if ( error )
	{
		RB_ECHO("Can't load font, unknow error");
	}
	
	setPixelSize(30);
	automaticLineHeight = true;
}


Glyph * FontImplementation::getGlyph(RB_Char32 unicodeValue){
	std::map<std::string, std::map< RB_Char32, Glyph*>* >::iterator i = glyphCache.find(size);
	Glyph * aGlyph;
	bool glyphCached = false;
	//we check if the glyph is already loaded and cached.
	if(i != glyphCache.end()){
		std::map<RB_Char32, Glyph*>::iterator j = i->second->find(unicodeValue);
		if (j != i->second->end()) {
			aGlyph = j->second;
			glyphCached = true;
		}
	}
	
	//If the glyph is not already cached
	if(glyphCached == false){
		FT_UInt glyph_index; 
		//We ask the font face what is the glyph index for the given unicode value
		glyph_index = FT_Get_Char_Index(font, unicodeValue);
		
		//we load the glyph  
		if(FT_Load_Glyph( font, glyph_index, FT_LOAD_RENDER )){
			RB_ECHO("Can't load glyph");
		}
		
		FT_Glyph currentGlyph;
		if(FT_Get_Glyph( font->glyph,  &currentGlyph)){
			RB_ECHO("Can't extract glyph from freetype glyph slot");
		}
		
		FT_BitmapGlyph  currentBitmapGlyph = (FT_BitmapGlyph)currentGlyph;
		
		//We save the size of the glyph 
		int glyphWidth = font->glyph->bitmap.width;
		int glyphHeight = font->glyph->bitmap.rows;
		
		
		aGlyph = new Glyph();
		std::stringstream key;
		key << name << "-" << size << "-" << unicodeValue;
		
		int bufferSize = glyphWidth*glyphHeight;

//		uint8_t * reversedBuffer = new uint8_t[bufferSize];
//		for (int i = 0; i < glyphHeight; i++) {
//			for(int j =0; j < glyphWidth; j++){
//				reversedBuffer[glyphWidth * i + j] = std::min((uint8_t) currentBitmapGlyph->bitmap.buffer[glyphWidth * (glyphHeight-(i+1)) + j], (uint8_t)10);
//			}
//		}
//		
		PixMap * aPixMap = new PixMap(currentBitmapGlyph->bitmap.buffer, glyphWidth, glyphHeight, Alpha);
		aGlyph->setTextureInfo(ResourceManager::addTexture(key.str(), aPixMap));
		aGlyph->setHoriAdvance(font->glyph->advance.x >> 6);
		
		
		aGlyph->setWidth(glyphWidth);
		aGlyph->setHeight(glyphHeight);
		
		aGlyph->setHoriBearingX( font->glyph->bitmap_left);
		
		aGlyph->setHoriBearingY( font->glyph->bitmap_top);
		
		i = (glyphCache.insert(std::pair<std::string, 
							   std::map<RB_Char32, Glyph*>* >(size, new std::map<RB_Char32, Glyph*>()) )).first;
		
			i->second->insert(std::pair<RB_Char32, Glyph*>(unicodeValue, aGlyph));
		
	}
	
	return aGlyph;
	
	
}



void FontImplementation::setPixelSize(int pixelSize){
	if(FT_Set_Pixel_Sizes(font, 0, pixelSize)){
		RB_ECHO("Can't set pixel size");
	}
	size = Parser::intToString(pixelSize) + "px";
	
}


void FontImplementation::setPointSize(int pointSize, int dpi){
	if(FT_Set_Char_Size(font, 0, pointSize*64, dpi, dpi)){
		RB_ECHO("Can't set point size");
	}
	size = Parser::intToString(pointSize) + "pt";
}
void FontImplementation::setManualLineHeight(int lineHeight){
	this->lineHeight = lineHeight;
	automaticLineHeight = false;
}
int FontImplementation::getLineHeight(){
	if (automaticLineHeight){
		return  font->size->metrics.height >> 6;
	}
	else{
		return lineHeight;
	}
}

void FontImplementation::setAutomaticLineHeight(){
	automaticLineHeight = true;
}
