#include "Glyph.h"

using namespace RedBox;

Glyph::Glyph() : Object(), textureInfo(NULL) {
}

Glyph::Glyph(const Glyph& src) : Object(src), advance(src.advance),
	horizontalBearing(src.horizontalBearing), size(src.size),
	textureInfo(src.textureInfo) {
}

Glyph& Glyph::operator=(const Glyph& src) {
	this->Object::operator=(src);
	if(this != &src) {
		advance = src.advance;
		horizontalBearing = src.horizontalBearing;
		size = src.size;
		textureInfo = textureInfo;
	}
	return *this;
}
