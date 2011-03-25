#include "Font.h"
#include "Debug.h"
#include "ResourceManager.h"
#include "MathHelper.h"
#include <sstream>
#include "FontImplementation.h"

using namespace RedBox;


void Font::initializeFontRenderer(){
	FontImplementation::initializeFontRenderer();
}

std::string Font::getName(){
	return fontPimpl->getName();
}


Font::Font(const std::string& name, const std::string & path){
	fontPimpl = new FontImplementation(name, path);
}


Glyph * Font::getGlyph(RB_Char32 unicodeValue){
	return fontPimpl->getGlyph(unicodeValue);
}



void Font::setPixelSize(int pixelSize){
	fontPimpl->setPixelSize(pixelSize);
}


void Font::setPointSize(int pointSize, int dpi){
	fontPimpl->setPointSize(pointSize, dpi);
}

