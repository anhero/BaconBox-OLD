#include "SpriteFactory.h"

#include <cmath>
#include <vector>

#include "Sprite.h"
#include "RenderStep.h"
#include "MathHelper.h"

using namespace RedBox;



Sprite* SpriteFactory::makePolygon(unsigned int nbSides, float sideLength,
								   const Color& color) {
	if(nbSides >= 3 && sideLength > 0.0f) {
		// We calculate the polygon's radius.
		float radius = sideLength / (2 * sinf(MathHelper::PI/nbSides));

		// Angle from the polygon's center.
		float angle = 360.0f / nbSides / 2.0f;

		Sprite* result = new Sprite();
		
		for(unsigned int i = 0; i < nbSides; ++i) {
			result->createVertex(radius * sinf(MathHelper::degreesToRadians(angle)),
								 radius * cosf(MathHelper::degreesToRadians(angle)));
			angle += 360.0f / nbSides;
		}

		RenderStep* ren = new RenderStep();
		ren->setVerticesGroup(&result->getVertices());
		ren->setDeleteVerticesGroup(false);
		ren->setColor(color);
		ren->setMode(RenderStepMode::SHAPE | RenderStepMode::COLOR);
		result->addRenderStep(ren);

		return result;
	} else {
		return NULL;
	}
}