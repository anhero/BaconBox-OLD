#include "BaconBox/Helper/ShapeFactory.h"

#include <cmath>

#include <algorithm>
#include <functional>
#include <list>

#include "BaconBox/Display/VertexArray.h"

namespace BaconBox {
	void ShapeFactory::createRegularPolygon(unsigned int nbSides, float sideLength,
	                                        const Vector2 &position,
	                                        VertexArray *vertices) {
		// We make sure the received parameters are valid.
		if (nbSides >= 3 && vertices && vertices->getNbVertices() == nbSides &&
		    sideLength > 0.0f) {
			// We calculate the polygon's radius.
			float radius = sideLength / (2.0f * std::sin(MathHelper::PI<float>() / nbSides));
			// Angle from the polygon's center.
			float incrementer = 360.0f / nbSides;
			float angle = incrementer * 0.5f ;
			VertexArray::SizeType adjustment = nbSides % 2;
			VertexArray::SizeType i = 0, half = nbSides / 2 + adjustment, lastIndex = nbSides - 1;
			VertexArray::Pointer tmp;
			VertexArray::ValueType minPosition(radius * std::sin(angle * MathHelper::AngleConvert<float>::DEGREES_TO_RADIANS),
			                                   radius * std::cos(angle * MathHelper::AngleConvert<float>::DEGREES_TO_RADIANS));

			tmp = &((*vertices)[(i < half) ? (i * 2) : (lastIndex - (i - half) * 2 - adjustment)]);

			*tmp = minPosition;
			angle += incrementer;

			while (++i < nbSides) {
				tmp = &((*vertices)[(i < half) ? (i * 2) : (lastIndex - (i - half) * 2 - adjustment)]);
				tmp->x = radius * std::sin(angle * MathHelper::AngleConvert<float>::DEGREES_TO_RADIANS);
				tmp->y = radius * std::cos(angle * MathHelper::AngleConvert<float>::DEGREES_TO_RADIANS);

				if (tmp->x < minPosition.x) {
					minPosition.x = tmp->x;
				}

				if (tmp->y < minPosition.y) {
					minPosition.y = tmp->y;
				}

				angle += incrementer;
			}

			// We calculate the delta to apply to the vertices to put it at the
			// asked position.
			Vector2 tmpDelta(position - minPosition);

			// We position the polygon as asked.
			for (VertexArray::Iterator i = vertices->getBegin(); i != vertices->getEnd(); ++i) {
				*i += tmpDelta;
			}
		}
	}

	void ShapeFactory::createRectangle(const Vector2 &size,
	                                   const Vector2 &position,
	                                   VertexArray *vertices) {
		// We make sure the size makes sense, that the vertices are valid and
		// that we have 4 vertices.
		if (size.x > 0.0f && size.y > 0.0f && vertices &&
		    vertices->getNbVertices() == 4) {
			VertexArray::Iterator i = vertices->getBegin();

			*i = position;
			++i;
			i->x = position.x + size.x;
			i->y = position.y;
			++i;
			i->x = position.x;
			i->y = position.y + size.y;
			++i;
			*i = position + size;
		}
	}

	void ShapeFactory::createSquare(float sideLength, const Vector2 &position,
	                                VertexArray *vertices) {
		createRectangle(Vector2(sideLength, sideLength), position, vertices);
	}
}
