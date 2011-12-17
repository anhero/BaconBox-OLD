#include "SpriteFactory.h"

#include "Sprite.h"
#include "InanimateSprite.h"
#include "ShapeFactory.h"

namespace RedBox {

	Sprite *SpriteFactory::makePolygon(unsigned int nbSides, float sideLength,
	                                   const Color &color) {
		Sprite *result = NULL;

		if (nbSides >= 3 && sideLength > 0.0f) {
			result = new Sprite();
			result->getVertices().resize(nbSides);
			ShapeFactory::createRegularPolygon(nbSides, sideLength, Vector2(), &(result->getVertices()));
			result->setColor(color);
			result->setRenderModes(FlagSet<RenderMode>(RenderMode::SHAPE) |
			                       FlagSet<RenderMode>(RenderMode::COLOR));
		}

		return result;
	}

	InanimateSprite *SpriteFactory::makeInanimatePolygon(unsigned int nbSides,
	                                                     float sideLength,
	                                                     const Color &color) {
		InanimateSprite *result = NULL;

		if (nbSides >= 3 && sideLength > 0.0f) {
			result = new InanimateSprite();
			result->getVertices().resize(nbSides);
			ShapeFactory::createRegularPolygon(nbSides, sideLength, Vector2(), &(result->getVertices()));
			result->setColor(color);
			result->setRenderModes(FlagSet<RenderMode>(RenderMode::SHAPE) |
			                       FlagSet<RenderMode>(RenderMode::COLOR));
		}

		return result;
	}
}
