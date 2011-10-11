#include "GlyphInformation.h"

namespace RedBox {
	GlyphInformation::GlyphInformation() : advance(), horizontalBearing(),
		size(), textureInformation(NULL) {
	}

	GlyphInformation::GlyphInformation(const Vector2 &newAdvance,
	                                   const Vector2 &newHorizontalBearing,
	                                   const Vector2 &newSize,
	                                   TextureInformation *newTextureInformation) :
		advance(newAdvance), horizontalBearing(newHorizontalBearing),
		size(newSize), textureInformation(newTextureInformation) {
	}

	GlyphInformation::GlyphInformation(const GlyphInformation &src) :
		advance(src.advance), horizontalBearing(src.horizontalBearing),
		size(src.size), textureInformation(src.textureInformation) {
	}

	GlyphInformation &GlyphInformation::operator=(const GlyphInformation &src) {
		if (this != &src) {
			advance = src.advance;
			horizontalBearing = src.horizontalBearing;
			size = src.size;
			textureInformation = src.textureInformation;
		}

		return *this;
	}
}
