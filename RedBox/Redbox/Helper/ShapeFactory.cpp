#include "ShapeFactory.h"

#include <cmath>

#include <algorithm>
#include <list>

#include "VertexArray.h"

namespace RedBox {
	void ShapeFactory::createRegularPolygon(unsigned int nbSides, float sideLength,
	                                        const Vector2 &position,
	                                        VertexArray *vertices) {
		// We make sure the received parameters are valid.
		if (nbSides >= 3 && vertices && vertices->getNbVertices() == nbSides &&
		    sideLength > 0.0f) {
			// We calculate the polygon's radius.
			float radius = sideLength / (2.0f * sinf(MathHelper::PI<float>() / nbSides));
			// Angle from the polygon's center.
			float incrementer = 360.0f / nbSides;
			float angle = incrementer * 0.5f ;
			VertexArray::SizeType adjustment = nbSides % 2;
			VertexArray::SizeType i = 0, half = nbSides / 2 + adjustment, lastIndex = nbSides - 1;
			VertexArray::Pointer tmp;
			VertexArray::ValueType minPosition(radius * sinf(MathHelper::degreesToRadians(angle)),
			                                   radius * cosf(MathHelper::degreesToRadians(angle)));

			tmp = &((*vertices)[(i < half) ? (i * 2) : (lastIndex - (i - half) * 2 - adjustment)]);

			*tmp = minPosition;
			angle += incrementer;

			while (++i < nbSides) {
				tmp = &((*vertices)[(i < half) ? (i * 2) : (lastIndex - (i - half) * 2 - adjustment)]);
				tmp->setXY(radius * sinf(MathHelper::degreesToRadians(angle)),
				           radius * cosf(MathHelper::degreesToRadians(angle)));

				if (tmp->getX() < minPosition.getX()) {
					minPosition.setX(tmp->getX());
				}

				if (tmp->getY() < minPosition.getY()) {
					minPosition.setY(tmp->getY());
				}

				angle += incrementer;
			}

			// We calculate the delta to apply to the vertices to put it at the
			// asked position.
			Vector2 tmpDelta(position - minPosition);

			// We position the polygon as asked.
			for (VertexArray::Iterator i = vertices->getBegin(); i != vertices->getEnd(); ++i) {
				i->addToXY(tmpDelta);
			}
		}
	}

	void ShapeFactory::createRectangle(const Vector2 &size,
	                                   const Vector2 &position,
	                                   VertexArray *vertices) {
		// We make sure the size makes sense, that the vertices are valid and
		// that we have 4 vertices.
		if (size.getX() > 0.0f && size.getY() > 0.0f && vertices &&
		    vertices->getNbVertices() == 4) {
			VertexArray::Iterator i = vertices->getBegin();

			i->setXY(position.getX(), position.getY());
			++i;
			i->setXY(position.getX() + size.getX(), position.getY());
			++i;
			i->setXY(position.getX(), position.getY() + size.getY());
			++i;
			i->setXY(position.getX() + size.getX(), position.getY() + size.getY());
		}
	}

	void ShapeFactory::createSquare(float sideLength, const Vector2 &position,
	                                VertexArray *vertices) {
		createRectangle(Vector2(sideLength, sideLength), position, vertices);
	}

	ShapeFactory::ShapeFactory() {
	}
}
