#if 0
#include "SpriteFactory.h"

#include <cmath>
#include <vector>

#include "Sprite.h"
#include "MathHelper.h"

using namespace RedBox;

Sprite* SpriteFactory::makePolygon(unsigned int nbSides, float sideLength,
								   const Color& color) {
	if(nbSides >= 3 && sideLength > 0.0f) {
		// We calculate the polygon's radius.
		float radius = sideLength / (2.0f * sin(MathHelper::PI<float>() / nbSides));

		// Angle from the polygon's center.
		float angle = 360.0f / nbSides / 2.0f;

		Sprite* result = new Sprite();
		
		for(unsigned int i = 0; i < nbSides; ++i) {
			result->createVertex(radius * sin(MathHelper::degreesToRadians(angle)),
								 radius * cos(MathHelper::degreesToRadians(angle)));
			angle += 360.0f / nbSides;
		}

		result->setMainColor(color);
		result->setRenderModes(FlagSet<RenderMode>(RenderMode::SHAPE) |
		                       FlagSet<RenderMode>(RenderMode::COLOR));

		Vector2 tmpVec(result->getVertices().getPosition());
		result->GraphicBody::setPosition(tmpVec.getX(), tmpVec.getY());

		result->setPosition(0.0f, 0.0f);

		return result;
	} else {
		return NULL;
	}
}
#endif
