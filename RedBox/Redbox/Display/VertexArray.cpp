#include "VertexArray.h"

namespace RedBox {
	VertexArray::~VertexArray() {
	}

	bool VertexArray::operator==(const VertexArray &rhs) const {
		bool equal = true;
		ConstIterator i = getBegin();
		ConstIterator i2 = rhs.getBegin();

		while (equal && i != getEnd() && i2 != rhs.getEnd()) {
			if (*i == *i2) {
				++i;
				++i2;

			} else {
				equal = false;
			}
		}

		return equal && i == getEnd() && i2 == rhs.getEnd();
	}

	bool VertexArray::operator !=(const VertexArray &rhs) const {
		return !(this->operator==(rhs));
	}

	const Vector2 VertexArray::getMinimumXY() const {
		if (isEmpty()) {
			return Vector2(0.0f, 0.0f);

		} else {
			ConstIterator i = getBegin();
			Vector2 result = *i;
			++i;

			while (i != getEnd()) {
				if (i->getX() < result.getX()) {
					result.setX(i->getX());
				}

				if (i->getY() < result.getY()) {
					result.setY(i->getY());
				}

				++i;
			}

			return result;
		}
	}

	float VertexArray::getMinimumX() const {
		if (isEmpty()) {
			return 0.0f;

		} else {
			ConstIterator i = getBegin();
			float result = i->getX();
			++i;

			while (i != getEnd()) {
				if (i->getX() < result) {
					result = i->getX();
				}

				++i;
			}

			return result;
		}
	}

	float VertexArray::getMinimumY() const {
		if (isEmpty()) {
			return 0.0f;

		} else {
			ConstIterator i = getBegin();
			float result = i->getY();
			++i;

			while (i != getEnd()) {
				if (i->getY() < result) {
					result = i->getY();
				}

				++i;
			}

			return result;
		}
	}

	const Vector2 VertexArray::getMaximumXY() const {
		if (isEmpty()) {
			return Vector2(0.0f, 0.0f);

		} else {
			ConstIterator i = getBegin();
			Vector2 result = *i;
			++i;

			while (i != getEnd()) {
				if (i->getX() > result.getX()) {
					result.setX(i->getX());
				}

				if (i->getY() > result.getY()) {
					result.setY(i->getY());
				}

				++i;
			}

			return result;
		}
	}

	float VertexArray::getMaximumX() const {
		if (isEmpty()) {
			return 0.0f;

		} else {
			ConstIterator i = getBegin();
			float result = i->getX();
			++i;

			while (i != getEnd()) {
				if (i->getX() > result) {
					result = i->getX();
				}

				++i;
			}

			return result;
		}
	}

	float VertexArray::getMaximumY() const {
		if (isEmpty()) {
			return 0.0f;

		} else {
			ConstIterator i = getBegin();
			float result = i->getY();
			++i;

			while (i != getEnd()) {
				if (i->getY() > result) {
					result = i->getY();
				}

				++i;
			}

			return result;
		}
	}

	const Vector2 VertexArray::getSize() const {
		if (isEmpty()) {
			return Vector2(0.0f, 0.0f);

		} else {
			ConstIterator i = getBegin();
			Vector2 min = *i;
			Vector2 max = *i;
			++i;

			while (i != getEnd()) {
				if (i->getX() < min.getX()) {
					min.setX(i->getX());

				} else if (i->getX() > max.getX()) {
					max.setX(i->getX());
				}

				if (i->getY() < min.getY()) {
					min.setY(i->getY());

				} else if (i->getY() > max.getY()) {
					max.setY(i->getY());
				}

				++i;
			}

			return max - min;
		}
	}

	float VertexArray::getWidth() const {
		if (isEmpty()) {
			return 0.0f;

		} else {
			ConstIterator i = getBegin();
			float min = i->getX();
			float max = i->getX();
			++i;

			while (i != getEnd()) {
				if (i->getX() < min) {
					min = i->getX();

				} else if (i->getX() > max) {
					max = i->getX();
				}

				++i;
			}

			return max - min;
		}
	}

	float VertexArray::getHeight() const {
		if (isEmpty()) {
			return 0.0f;

		} else {
			ConstIterator i = getBegin();
			float min = i->getY();
			float max = i->getY();
			++i;

			while (i != getEnd()) {
				if (i->getY() < min) {
					min = i->getY();

				} else if (i->getY() > max) {
					max = i->getY();
				}

				++i;
			}

			return max - min;
		}
	}

	const Vector2 VertexArray::getCentroid() const {
		return getSumOfVertices() / static_cast<float>(getNbVertices());
	}

	const Vector2 VertexArray::getSumOfVertices() const {
		Vector2 result;

		for (ConstIterator i = getBegin(); i != getEnd(); ++i) {
			result.addToXY(*i);
		}

		return result;
	}

	void VertexArray::move(float xDelta, float yDelta) {
		for (Iterator i = getBegin(); i != getEnd(); ++i) {
			i->addToXY(xDelta, yDelta);
		}
	}

	void VertexArray::scaleFromPoint(float xScaling, float yScaling,
	                                   const Vector2 &fromPoint) {
		for (Iterator i = getBegin(); i != getEnd(); ++i) {
			i->subtractFromXY(fromPoint);
			i->scalarMultiplication(xScaling, yScaling);
			i->addToXY(fromPoint);
		}
	}

	void VertexArray::rotateFromPoint(float rotationAngle,
	                                    const Vector2 &rotationPoint) {
		for (Iterator i = getBegin(); i != getEnd(); ++i) {
			i->subtractFromXY(rotationPoint);
			i->rotate(rotationAngle);
			i->addToXY(rotationPoint);
		}
	}

	bool VertexArray::overlaps(const Vector2 &point) const {
		bool result = false;

		for (VertexArray::ConstIterator i = this->getBegin(), j = --this->getEnd(); i != this->getEnd(); ++i) {
			if ((i->getY() < point.getY() && j->getY() >= point.getY()) ||
				 ((j->getY() < point.getY() && i->getY() >= point.getY()) &&
				(i->getX() <= point.getX() || j->getX() <= point.getX()))) {
				if (i->getX() + (point.getY() - i->getY()) / (j->getY() - i->getY()) * (j->getX() - i->getX()) < point.getX()) {
					result = !result;
				}
			}

			j = i;
		}

		return result;
	}

	AxisAlignedBoundingBox VertexArray::getAxisAlignedBoundingBox() const {
		AxisAlignedBoundingBox result;

		if (!isEmpty()) {
			ConstIterator i = getBegin();
			result.setPosition(*i);
			result.setSize(*i);
			++i;

			while (i != getEnd()) {
				if (i->getX() < result.getXPosition()) {
					result.setXPosition(i->getX());

				} else if (i->getX() > result.getWidth()) {
					result.setWidth(i->getX());
				}

				if (i->getY() < result.getYPosition()) {
					result.setYPosition(i->getY());

				} else if (i->getY() > result.getHeight()) {
					result.setHeight(i->getY());
				}

				++i;
			}

			result.setSize(result.getSize() - result.getPosition());
		}

		return result;
	}

	bool VertexArray::intersects(const VertexArray &other) const {
		bool result = false;

		// We make sure the arrays aren't empty.
		if (getNbVertices() >= 3 && other.getNbVertices() >= 3) {
			// Useless to check for intersection if the polygons' bounding box
			// aren't even colliding.
			if (getAxisAlignedBoundingBox().overlaps(other.getAxisAlignedBoundingBox())) {
				result = true;
				Vector2 line;
				ConstIterator i = getBegin();
				ConstIterator iNext = getBegin();
				++iNext;
				ConstIterator j;
				float proj, min1, min2, max1, max2;

				while (result && iNext != getEnd()) {
					// We take the line representing the edge.
					line = *iNext - *i;
					// We get the line perendicular to the edge's line.
					line.setXY(-line.getY(), line.getX());
					// We normalize the axis.
					line.normalize();

					// Project every vertex in the first polygon on the axis and
					// store min and max.
					j = getBegin();
					min1 = max1 = (line.getX() * j->getX() + line.getY() * j->getY()) / (line.getX() * line.getX() + line.getX() * line.getY());
					++j;
					while (j != getEnd()) {
						proj = (line.getX() * j->getX() + line.getY() * j->getY()) / (line.getX() * line.getX() + line.getX() * line.getY());
						if (proj < min1) {
							min1 = proj;
						} else if (proj > max1) {
							max1 = proj;
						}
						++j;
					}

					// Project every vertex in the second polygon on the axis
					// and store min and max.
					j = other.getBegin();
					min2 = max2 = (line.getX() * j->getX() + line.getY() * j->getY()) / (line.getX() * line.getX() + line.getX() * line.getY());
					++j;
					while (j != other.getEnd()) {
						proj = (line.getX() * j->getX() + line.getY() * j->getY()) / (line.getX() * line.getX() + line.getX() * line.getY());
						if (proj < min2) {
							min2 = proj;
						} else if (proj > max2) {
							max2 = proj;
						}
						++j;
					}

					// If the projections don't overlap, it means there are no
					// collisions.
					if(!(max1 >= min2 && min1 <= max2)) {
						result = false;
					}

					++i;
					++iNext;
				}
			}
		}

		return result;
	}
}
