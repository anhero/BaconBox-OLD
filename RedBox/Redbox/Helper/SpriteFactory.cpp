#include "SpriteFactory.h"

namespace RedBox {
	Sprite *SpriteFactory::makePolygon(unsigned int nbSides, float sideLength,
	                                   const Color &color) {
		return makeSpecificPolygon<Sprite>(nbSides, sideLength, color);
	}

	InanimateSprite *SpriteFactory::makeInanimatePolygon(unsigned int nbSides,
	                                                     float sideLength,
	                                                     const Color &color) {
		return makeSpecificPolygon<InanimateSprite>(nbSides, sideLength, color);
	}
}
