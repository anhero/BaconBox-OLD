#include "Glyph.h"

namespace RedBox {
	Glyph::Glyph() : textureInfo(NULL) {
	}

	Glyph::Glyph(const Glyph &src) : advance(src.advance),
		horizontalBearing(src.horizontalBearing), size(src.size),
		textureInfo(src.textureInfo) {
	}

	Glyph &Glyph::operator=(const Glyph &src) {
		if (this != &src) {
			advance = src.advance;
			horizontalBearing = src.horizontalBearing;
			size = src.size;
			textureInfo = textureInfo;
		}

		return *this;
	}
}
