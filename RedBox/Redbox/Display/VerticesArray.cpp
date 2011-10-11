#include "VerticesArray.h"

namespace RedBox {
	VerticesArray::~VerticesArray() {
	}

	bool VerticesArray::operator==(const VerticesArray &rhs) const {
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

	bool VerticesArray::operator !=(const VerticesArray &rhs) const {
		return !(this->operator==(rhs));
	}

	const Vector2 VerticesArray::getMinimumXY() const {
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

	float VerticesArray::getMinimumX() const {
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

	float VerticesArray::getMinimumY() const {
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

	const Vector2 VerticesArray::getMaximumXY() const {
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

	float VerticesArray::getMaximumX() const {
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

	float VerticesArray::getMaximumY() const {
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

	const Vector2 VerticesArray::getSize() const {
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

	float VerticesArray::getWidth() const {
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

	float VerticesArray::getHeight() const {
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

	const Vector2 VerticesArray::getCentroid() const {
		return getSumOfVertices() / static_cast<float>(getNbVertices());
	}

	const Vector2 VerticesArray::getSumOfVertices() const {
		Vector2 result;
		for (ConstIterator i = getBegin(); i != getEnd(); ++i) {
			result.addToXY(*i);
		}
		return result;
	}

	void VerticesArray::move(float xDelta, float yDelta) {
		for (Iterator i = getBegin(); i != getEnd(); ++i) {
			i->addToXY(xDelta, yDelta);
		}
	}

	void VerticesArray::scaleFromPoint(float xScaling, float yScaling,
	                                   const Vector2 &fromPoint) {
		for (Iterator i = getBegin(); i != getEnd(); ++i) {
			i->subtractFromXY(fromPoint);
			i->scalarMultiplication(xScaling, yScaling);
			i->addToXY(fromPoint);
		}
	}

	void VerticesArray::rotateFromPoint(float rotationAngle,
	                                    const Vector2 &rotationPoint) {
		for (Iterator i = getBegin(); i != getEnd(); ++i) {
			i->subtractFromXY(rotationPoint);
			i->rotate(rotationAngle);
			i->addToXY(rotationPoint);
		}
	}
}
