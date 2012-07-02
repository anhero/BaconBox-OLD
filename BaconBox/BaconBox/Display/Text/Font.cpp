#include "BaconBox/Display/Text/Font.h"
#include "BaconBox/Display/Text/FreetypeImplementation/FontImplementation.h"

using namespace BaconBox;

void Font::initializeFontRenderer() {
	FontImplementation::initializeFontRenderer();
}

const std::string &Font::getName() const {
	return fontPimpl->getName();
}

Font::Font(const std::string &name, const std::string &path) : fontPimpl(NULL) {
	fontPimpl = new FontImplementation(name, path);
}

const GlyphInformation *Font::getGlyphInformation(Char32 unicodeValue) {
	return fontPimpl->getGlyphInformation(unicodeValue);
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
