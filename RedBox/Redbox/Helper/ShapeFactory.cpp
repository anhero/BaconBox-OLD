#include "ShapeFactory.h"

#include <cmath>

#include "VerticesArray.h"

namespace RedBox {
	void ShapeFactory::createRegularPolygon(unsigned int nbSides, float sideLength,
	                                        const Vector2 &position,
	                                        VerticesArray *vertices) {
		// We make sure the recieved parameters are valid.
		if (nbSides >= 3 && vertices && vertices->getNbVertices() == nbSides &&
		    sideLength > 0.0f) {
			// We calculate the polygon's radius.
			float radius = sideLength / (2.0f * sinf(MathHelper::PI<float>() / nbSides));

			// Angle from the polygon's center.
			float incrementer = 360.0f / nbSides;
			float angle = incrementer / 2.0f;
			VerticesArray::Iterator i = vertices->getBegin();
			Vector2 tmpPosition(radius * sinf(MathHelper::degreesToRadians(angle)),
			                    radius * cosf(MathHelper::degreesToRadians(angle)));
			*i = tmpPosition;
			angle += incrementer;
			++i;

			while (i != vertices->getEnd()) {
				i->setXY(radius * sinf(MathHelper::degreesToRadians(angle)),
				         radius * cosf(MathHelper::degreesToRadians(angle)));

				if (i->getX() < tmpPosition.getX()) {
					tmpPosition.setX(i->getX());
				}

				if (i->getY() < tmpPosition.getY()) {
					tmpPosition.setY(i->getY());
				}

				angle += incrementer;

				++i;
			}

			// We calculate the delta to apply to the vertices to put it at the
			// asked position.
			Vector2 tmpDelta(position - tmpPosition);

			// We position the polygon as asked.
			i = vertices->getBegin();

			while (i != vertices->getEnd()) {
				i->addToXY(tmpDelta);
				++i;
			}
		}
	}

	void ShapeFactory::createRectangle(const Vector2 &size,
	                                   const Vector2 &position,
	                                   VerticesArray *vertices) {
		// We make sure the size makes sense, that the vertices are valid and
		// that we have 4 vertices.
		if (size.getX() > 0.0f && size.getY() > 0.0f && vertices &&
		    vertices->getNbVertices() == 4) {
			VerticesArray::Iterator i = vertices->getBegin();

			i->setXY(position.getX(), position.getY());
			++i;
			i->setXY(position.getX() + size.getX(), position.getY());
			++i;
			i->setXY(position.getX() + size.getX(), position.getY() + size.getY());
			++i;
			i->setXY(position.getX(), position.getY() + size.getY());
		}
	}

	void ShapeFactory::createSquare(float sideLength, const Vector2 &position,
	                                VerticesArray *vertices) {
		createRectangle(Vector2(sideLength, sideLength), position, vertices);
	}

	ShapeFactory::ShapeFactory() {
	}
}
