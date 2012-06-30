#include "VertexArray.h"

#include "Value.h"
#include "DefaultSerializer.h"
#include "Serializer.h"

namespace BaconBox {
	bool VertexArray::isValidValueStatic(const Value &node) {
		bool result = true;

		const Array &tmpArray = node.getArray();
		Array::size_type i = 0;

		while (result && i < tmpArray.size()) {
			if (Vector2::isValidValue(tmpArray[i])) {
				++i;

			} else {
				result = false;
			}
		}

		return result;
	}

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

	VertexArray::ValueType &VertexArray::at(SizeType index) {
		return *(getBegin() + index);
	}

	const VertexArray::ValueType &VertexArray::at(SizeType index) const {
		return *(getBegin() + index);
	}

	VertexArray::ValueType &VertexArray::operator[](SizeType index) {
		return *(getBegin() + index);
	}

	const VertexArray::ValueType &VertexArray::operator[](SizeType index) const {
		return *(getBegin() + index);
	}

	const Vector2 VertexArray::getMinimumXY() const {
		if (isEmpty()) {
			return Vector2(0.0f, 0.0f);

		} else {
			ConstIterator i = getBegin();
			Vector2 result = *i;
			++i;

			while (i != getEnd()) {
				if (i->x < result.x) {
					result.x = i->x;
				}

				if (i->y < result.y) {
					result.y = i->y;
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
			float result = i->x;
			++i;

			while (i != getEnd()) {
				if (i->x < result) {
					result = i->x;
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
			float result = i->y;
			++i;

			while (i != getEnd()) {
				if (i->y < result) {
					result = i->y;
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
				if (i->x > result.x) {
					result.x = i->x;
				}

				if (i->y > result.y) {
					result.y = i->y;
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
			float result = i->x;
			++i;

			while (i != getEnd()) {
				if (i->x > result) {
					result = i->x;
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
			float result = i->y;
			++i;

			while (i != getEnd()) {
				if (i->y > result) {
					result = i->y;
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
				if (i->x < min.x) {
					min.x = i->x;

				} else if (i->x > max.x) {
					max.x = i->x;
				}

				if (i->y < min.y) {
					min.y = i->y;

				} else if (i->y > max.y) {
					max.y = i->y;
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
			float min = i->x;
			float max = i->x;
			++i;

			while (i != getEnd()) {
				if (i->x < min) {
					min = i->x;

				} else if (i->x > max) {
					max = i->x;
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
			float min = i->y;
			float max = i->y;
			++i;

			while (i != getEnd()) {
				if (i->y < min) {
					min = i->y;

				} else if (i->y > max) {
					max = i->y;
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
			result += *i;
		}

		return result;
	}

	void VertexArray::move(float xDelta, float yDelta) {
		for (Iterator i = getBegin(); i != getEnd(); ++i) {
			i->x += xDelta;
			i->y += yDelta;
		}
	}

	void VertexArray::scaleFromPoint(float xScaling, float yScaling,
	                                 const Vector2 &fromPoint) {
		for (Iterator i = getBegin(); i != getEnd(); ++i) {
			*i -= fromPoint;
			i->x *= xScaling;
			i->y *= yScaling;
			*i += fromPoint;
		}
	}

	void VertexArray::rotateFromPoint(float rotationAngle,
	                                  const Vector2 &rotationPoint) {
		for (Iterator i = getBegin(); i != getEnd(); ++i) {
			*i -= rotationPoint;
			i->rotate(rotationAngle);
			*i += rotationPoint;
		}
	}

	bool VertexArray::overlaps(const Vector2 &point) const {
		bool result = false;

		for (VertexArray::ConstIterator i = this->getBegin(), j = --this->getEnd(); i != this->getEnd(); ++i) {
			if ((i->y < point.y && j->y >= point.y) ||
			    ((j->y < point.y && i->y >= point.y) &&
			     (i->x <= point.x || j->x <= point.x))) {
				if (i->x + (point.y - i->y) / (j->y - i->y) * (j->x - i->x) < point.x) {
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
				if (i->x < result.getXPosition()) {
					result.setXPosition(i->x);

				} else if (i->x > result.getWidth()) {
					result.setWidth(i->x);
				}

				if (i->y < result.getYPosition()) {
					result.setYPosition(i->y);

				} else if (i->y > result.getHeight()) {
					result.setHeight(i->y);
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
					line.x = -line.y;
					line.y = line.x;
					// We normalize the axis.
					line.normalize();

					// Project every vertex in the first polygon on the axis and
					// store min and max.
					j = getBegin();
					min1 = max1 = (line.x * j->x + line.y * j->y) / (line.x * line.x + line.x * line.y);
					++j;

					while (j != getEnd()) {
						proj = (line.x * j->x + line.y * j->y) / (line.x * line.x + line.x * line.y);

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
					min2 = max2 = (line.x * j->x + line.y * j->y) / (line.x * line.x + line.x * line.y);
					++j;

					while (j != other.getEnd()) {
						proj = (line.x * j->x + line.y * j->y) / (line.x * line.x + line.x * line.y);

						if (proj < min2) {
							min2 = proj;

						} else if (proj > max2) {
							max2 = proj;
						}

						++j;
					}

					// If the projections don't overlap, it means there are no
					// collisions.
					if (!(max1 >= min2 && min1 <= max2)) {
						result = false;
					}

					++i;
					++iNext;
				}
			}
		}

		return result;
	}

	void VertexArray::serialize(Value &node, bool setName) const {
		if (setName) {
			node.setName("VertexArray");
		}
		node.setArray(Array(this->getNbVertices()));
		node.setArrayOfSameTypes(true);

		for (SizeType i = 0; i < this->getNbVertices(); ++i) {
			DefaultSerializer::serialize(this->operator[](i), node[i], false);
		}
	}

	bool VertexArray::deserialize(const Value &node) {
		bool result = this->isValidValue(node);

		if (result) {
			this->resize(node.getArray().size());
			for (Array::size_type i = 0; i < node.getArray().size(); ++i) {
				DefaultSerializer::deserialize(node.getArray()[i], this->operator[](i));
			}
		}

		return result;
	}

	bool VertexArray::isValidValue(const Value &node) const {
		return VertexArray::isValidValueStatic(node);
	}

	std::ostream &operator<<(std::ostream &output, const VertexArray &v) {
		Value tmpValue;
		DefaultSerializer::serialize(v, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}
}
