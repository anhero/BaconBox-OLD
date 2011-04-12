#include "SpriteFactory.h"

#include <cmath>
#include <vector>

#include "Sprite.h"
#include "RenderStep.h"

using namespace RedBox;

const float SpriteFactory::PI = 3.141592f;
const float SpriteFactory::DEGREE_TO_RADIAN = 0.017453f;

Sprite* SpriteFactory::makePolygon(unsigned int nbSides, float sideLength,
								   unsigned char red, unsigned char green,
								   unsigned char blue, unsigned char alpha) {
	if(nbSides >= 3 && sideLength > 0.0f) {
		// We calculate the polygon's radius.
		float radius = sideLength / (2 * sinf(PI/nbSides));

		// Angle from the polygon's center.
		float angle = 360.0f / nbSides / 2.0f;

		Sprite* result = new Sprite();
		
		for(unsigned int i = 0; i < nbSides; ++i) {
			result->createVertex(radius * sinf(degreeToRadian(angle)),
								 radius * cosf(degreeToRadian(angle)));
			angle += 360.0f / nbSides;
		}

		RenderStep* ren = new RenderStep();
		ren->setVerticesGroup(&result->getVertices());
		ren->setDeleteVerticesGroup(false);
		ren->setColor(red, green, blue, alpha);
		ren->setMode(RenderStepMode::SHAPE | RenderStepMode::COLOR);
		result->addRenderStep(ren);

		return result;
	} else {
		return NULL;
	}
}


/*std::vector<Vec2>* SpriteFactory::createLine(float length) {
	std::vector<Vec2>* result = new std::vector<Vec2>(2, Vec2(0.0f, 0.0f));
	result->at(1).setX(length);
	return result;
}*/

float SpriteFactory::degreeToRadian(float degree) {
	return degree * DEGREE_TO_RADIAN;
}
