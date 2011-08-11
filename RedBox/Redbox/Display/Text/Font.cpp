#include "Font.h"
#include "FontImplementation.h"

using namespace RedBox;

void Font::initializeFontRenderer() {
	FontImplementation::initializeFontRenderer();
}

const std::string& Font::getName() const {
	return fontPimpl->getName();
}

Font::Font(const std::string& name, const std::string& path) : fontPimpl(NULL) {
	fontPimpl = new FontImplementation(name, path);
}

Glyph* Font::getGlyph(Char32 unicodeValue) {
	return fontPimpl->getGlyph(unicodeValue);
}

void Font::setPixelSize(int pixelSize) {
	fontPimpl->setPixelSize(pixelSize);
}

void Font::setPointSize(int pointSize, int dpi) {
	fontPimpl->setPointSize(pointSize, dpi);
}

int Font::getLineHeight() const {
	return fontPimpl->getLineHeight();
}

void Font::setManualLineHeight(int lineHeight) {
	fontPimpl->setManualLineHeight(lineHeight);
}

void Font::setAutomaticLineHeight() {
	fontPimpl->setAutomaticLineHeight();
}
