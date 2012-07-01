/**
 * @file
 * @ingroup Math
 */
#ifndef RB_VECTOR_2_H
#define RB_VECTOR_2_H

#include <iostream>
#include <cmath>

#include "MathHelper.h"
#include "Value.h"
#include "DefaultSerializer.h"
#include "Serializer.h"
#include "Array.h"
#include "Object.h"

namespace BaconBox {
#pragma pack(1)
	template <typename T, unsigned int NB_DIMENSIONS = 2u> class Vector;

	/**
	 * Represents a 2D euclidean vector. Templated so it can only be a vector of
	 * floats, doubles or long doubles.
	 * @ingroup Math
	 * @tparam T Type of data to use as the Vector2T's coordinates.
	 */
	template <typename T>
	class Vector<T, 2u> {
	public:
		/// Fundamental floating point number type the vector contains.
		typedef T ValueType;
		/// Number of dimensions the vector has.
		static const unsigned int NB_DIMENSIONS = 2u;
		/// Typedef for easier reading and writing.
		typedef Vector<ValueType, NB_DIMENSIONS> Vector2;
		/// Normalized vector that points up.
		static const Vector<ValueType, NB_DIMENSIONS> UP;
		/// Value equal to zero.
		static const ValueType ZERO;

		/// Type of component, either on the X axis or Y axis.
		enum ComponentType {
		    X,
		    Y
		};

		/**
		 * Represents a component of a Vector2.
		 * @tparam C Either X or Y.
		 */
		template <ComponentType C>
		struct Component {
			Component() : value(ZERO) {}
			Component(ValueType newValue) : value(newValue) {}
			Component(const Component<C> &src) : value(src.value) {}
			Component<C> &operator=(Component<C> src) {
				value = src.value;
				return *this;
			}

			// Compound assignment operators.
			Component<C> &operator+=(Component<C> rhs) {
				value += rhs.value;
				return *this;
			}
			Component<C> &operator-=(Component<C> rhs) {
				value -= rhs.value;
				return *this;
			}
			Component<C> &operator*=(Component<C> rhs) {
				value *= rhs.value;
				return *this;
			}
			Component<C> &operator/=(Component<C> rhs) {
				value /= rhs.value;
				return *this;
			}
			Component<C> &operator%=(Component<C> rhs) {
				value %= rhs.value;
				return *this;
			}
			Component<C> &operator&=(Component<C> rhs) {
				value &= rhs.value;
				return *this;
			}
			Component<C> &operator|=(Component<C> rhs) {
				value |= rhs.value;
				return *this;
			}
			Component<C> &operator^=(Component<C> rhs) {
				value ^= rhs.value;
				return *this;
			}
			Component<C> &operator<<=(Component<C> rhs) {
				value <<= rhs.value;
				return *this;
			}
			Component<C> &operator>>=(Component<C> rhs) {
				value >>= rhs.value;
				return *this;
			}

			Component<C> operator+(Component<C> other) {
				return Component<C>(*this) += other;
			}
			Component<C> operator-(Component<C> other) {
				return Component<C>(*this) -= other;
			}
			Component<C> operator*(Component<C> other) {
				return Component<C>(*this) *= other;
			}
			Component<C> operator/(Component<C> other) {
				return Component<C>(*this) /= other;
			}
			Component<C> operator%(Component<C> other) {
				return Component<C>(*this) %= other;
			}
			Component<C> operator&(Component<C> other) {
				return Component<C>(*this) &= other;
			}
			Component<C> operator|(Component<C> other) {
				return Component<C>(*this) |= other;
			}
			Component<C> operator^(Component<C> other) {
				return Component<C>(*this) ^= other;
			}
			Component<C> operator<<(Component<C> other) {
				return Component<C>(*this) <<= other;
			}
			Component<C> operator>>(Component<C> other) {
				return Component<C>(*this) >>= other;
			}

			Component<C> operator+() const {
				return Component<C>(+value);
			}
			Component<C> operator-() const {
				return Component<C>(-value);
			}

			Component<C> &operator++() {
				++value;
				return *this;
			}
			Component<C> operator++(int) {
				Component<C> result(*this);
				++value;
				return result;
			}
			Component<C> &operator--() {
				--value;
				return *this;
			}
			Component<C> operator--(int) {
				Component<C> result(*this);
				--value;
				return result;
			}

			bool operator==(Component<C> other) const {
				return value == other.value;
			}
			bool operator!=(Component<C> other) const {
				return value != other.value;
			}
			bool operator>(Component<C> other) const {
				return value > other.value;
			}
			bool operator<(Component<C> other) const {
				return value < other.value;
			}
			bool operator>=(Component<C> other) const {
				return value >= other.value;
			}
			bool operator<=(Component<C> other) const {
				return value <= other.value;
			}
			bool operator!() const {
				return !value;
			}
			bool operator&&(Component<C> other) const {
				return value && other.value;
			}
			bool operator||(Component<C> other) const {
				return value || other.value;
			}

			/// Value of the component.
			ValueType value;
		};

		/// Typedef for easier reading and writing.
		typedef Component<X> XComponent;
		/// Typedef for easier reading and writing.
		typedef Component<Y> YComponent;

		/**
		 * Default constructor.
		 */
		Vector();

		/**
		 * Initializes the vector with the given x component.
		 * @param newX X component to use.
		 */
		Vector(XComponent newX);

		/**
		 * Initializes the vector with the given x component.
		 * @param newY Y component to use.
		 */
		Vector(YComponent newY);

		/**
		 * Initializes the vector with the given x and y components.
		 * @param newX X component to use.
		 * @param newY Y component to use.
		 */
		Vector(XComponent newX, YComponent newY);

		/**
		 * Copy constructor.
		 * @param src Vector to make a copy of.
		 */
		Vector(const Vector2 &src);

		/**
		 * Assignment operator overload.
		 * @param src Vector to copy.
		 * @return Reference to the modified instance.
		 */
		Vector2 &operator=(const Vector2 &src);

		/**
		 * Checks wether or not the given vector is equal. Two vectors are said
		 * to be equal if their coordinates are equal.
		 * @param other Vector to compare the instance with.
		 * @return True if the coordinates are equal, false if not.
		 */
		bool operator==(const Vector2 &other) const;
		/**
		 * Checks wether or not the given vector is different. Two vectors are
		 * said to be equal if their coordinates are equal.
		 * @param other Vector to compare the instance with.
		 * @return True if at least one coordinate is different, false if not.
		 */
		bool operator!=(const Vector2 &other) const;

		Vector2 &operator+=(const Vector2 &other);
		Vector2 &operator+=(ValueType delta);
		Vector2 &operator+=(XComponent xDelta);
		Vector2 &operator+=(YComponent yDelta);

		Vector2 &operator-=(const Vector2 &other);
		Vector2 &operator-=(ValueType delta);
		Vector2 &operator-=(XComponent xDelta);
		Vector2 &operator-=(YComponent yDelta);

		Vector2 &operator*=(ValueType delta);
		Vector2 &operator*=(XComponent xDelta);
		Vector2 &operator*=(YComponent yDelta);

		Vector2 &operator/=(ValueType delta);
		Vector2 &operator/=(XComponent xDelta);
		Vector2 &operator/=(YComponent yDelta);

		Vector2 operator+(const Vector2 &other) const;
		Vector2 operator+(ValueType delta) const;
		friend Vector2 operator+(ValueType delta, const Vector2 &vector) {
			return Vector2(vector) += delta;
		}
		Vector2 operator+(XComponent xDelta) const;
		friend Vector2 operator+(XComponent xDelta, const Vector2 &vector) {
			return Vector2(vector) += xDelta;
		}
		Vector2 operator+(YComponent yDelta) const;
		friend Vector2 operator+(YComponent yDelta, const Vector2 &vector) {
			return Vector2(vector) += yDelta;
		}
		Vector2 operator+() const;

		Vector2 operator-(const Vector2 &other) const;
		Vector2 operator-(ValueType delta) const;
		friend Vector2 operator-(ValueType delta, const Vector2 &vector) {
			return Vector2(vector) -= delta;
		}
		Vector2 operator-(XComponent xDelta) const;
		friend Vector2 operator-(XComponent xDelta, const Vector2 &vector) {
			return Vector2(vector) -= xDelta;
		}
		Vector2 operator-(YComponent yDelta) const;
		friend Vector2 operator-(YComponent yDelta, const Vector2 &vector) {
			return Vector2(vector) -= yDelta;
		}
		Vector2 operator-() const;

		/**
		 * Calculates the dot product.
		 * @param other Other vector to use to calculate the dot product.
		 * @return Resulting dot product.
		 * @see BaconBox::Vector::getDotProduct()
		 */
		ValueType operator*(const Vector2 &other) const;

		Vector2 operator*(ValueType delta) const;
		friend Vector2 operator*(ValueType delta, const Vector2 &vector) {
			return Vector2(vector) *= delta;
		}
		Vector2 operator*(XComponent xDelta) const;
		friend Vector2 operator*(XComponent xDelta, const Vector2 &vector) {
			return Vector2(vector) *= xDelta;
		}
		Vector2 operator*(YComponent yDelta) const;
		friend Vector2 operator*(YComponent yDelta, const Vector2 &vector) {
			return Vector2(vector) *= yDelta;
		}

		Vector2 operator/(ValueType delta) const;
		friend Vector2 operator/(ValueType delta, const Vector2 &vector) {
			return Vector2(vector) /= delta;
		}
		Vector2 operator/(XComponent xDelta) const;
		friend Vector2 operator/(XComponent xDelta, const Vector2 &vector) {
			return Vector2(vector) /= xDelta;
		}
		Vector2 operator/(YComponent yDelta) const;
		friend Vector2 operator/(YComponent yDelta, const Vector2 &vector) {
			return Vector2(vector) /= yDelta;
		}

		/**
		 * Calculates the instance's length. Also known as the magnitude or the
		 * norm.
		 * @return Instance's length.
		 */
		ValueType getLength() const;

		/**
		 * Changes the vector's length.
		 * @param newLength New length to set to the vector.
		 */
		void setLength(ValueType newLength);

		/**
		 * Calculates the instance's squared length.
		 * @return Instance's length.
		 */
		ValueType getSquaredLength() const;

		/**
		 * Calculates the dot product between the instance and another vector.
		 * @param other Other vector used to calculate the dot product.
		 * @return Resulting dot product.
		 */
		ValueType getDotProduct(const Vector2 &other) const;

		/**
		 * Gets a normalized version of the instance. Same as doing
		 * setLength(1) on a copy of the instance.
		 * @return Copy of the instance, but normalized.
		 */
		Vector2 getNormalized() const;

		/**
		 * Normalizes the instance. Same as calling setLength(1).
		 */
		void normalize();

		/**
		 * Multiplies the other vector's coordinates with the instance's.
		 * First multiplies the other vector's x coordinate with the instance's
		 * x coordinate then multiplies the other vector's y coordinate with
		 * the instance's y coordinate.
		 * @param other Other vector to multiply the instance with.
		 * @return Referene to the modified instance.
		 */
		Vector2 &coordinatesMultiply(const Vector2 &other);

		/**
		 * Applies coordinatesMultiply(other) on a copy of the instance.
		 * @param other Other vector to multiply the instance with.
		 * @return Copy of the instance with coordinatesMultiply(other) applied
		 * to it.
		 */
		Vector2 getCoordinatesMultiplication(const Vector2 &other) const;

		/**
		 * Divides the instance's coordinates by the other vector's coordinates.
		 * First dividies the instance's x coordinate by the other vector's x
		 * coordinate, then divides the instance's y coordinate by the other
		 * vector's y coordinate.
		 * @param other Other vector to divide the instance by.
		 * @return Reference to the modified instance.
		 */
		Vector2 &coordinatesDivide(const Vector2 &other);

		/**
		 * Applies coordinatesDivide(other) on a copy of the instance.
		 * @param other Other vector to divide the instance by.
		 * @return Copy of the instance with coordinatesDivide(other) applied to
		 * it.
		 */
		Vector2 getCoordinatesDivision(const Vector2 &other) const;

		/**
		 * Gets the angle relative to the UP vector (in degrees).
		 * @return Angle between -180 and 180. Angle increases as it goes
		 * counter clockwise.
		 */
		ValueType getAngle() const;

		/**
		 * Calculates the angle between the instance and another vector.
		 * @param other Other vector to calculate the angle between.
		 * @return Angle between the two vectors.
		 */
		ValueType getAngleBetween(const Vector2 &other) const;

		/**
		 * Sets the angle of the vector without affecting its length.
		 * @param newAngle New angle to set to the instance.
		 */
		void setAngle(ValueType newAngle);

		/**
		 * Gets a copy of the vector, but rotated.
		 * @param angle Angle to rotate the copy (in degrees). Positive values
		 * make the instance rotate counter clockwise, while negative values
		 * make the instance rotate clockwise.
		 */
		Vector2 getRotated(ValueType angle) const;

		/**
		 * Rotates the instance.
		 * @param angle Angle to rotate the instance (in degrees). Positive
		 * values make the instance rotate counter clockwise, while negative
		 * values make the instance rotate clockwise.
		 */
		void rotate(ValueType angle);

		/**
		 * Gets a copy of the instance projected on the given direction vector.
		 * @param direction Vector on which to project the copy.
		 * @return Copy of the instance projected on the direction vector.
		 */
		Vector2 getProjection(const Vector2 &direction) const;

		/**
		 * Projects the instance on a vector.
		 * @param direction Vector to project the instance onto.
		 */
		void project(const Vector2 &direction);

		/**
		 * Gets a copy of the instance reflected about the given vector.
		 * @param mirror Vector to reflect the copy about.
		 * @return Copy of the instance reflected about the given vector.
		 */
		Vector2 getReflected(const Vector2 &mirror) const;

		/**
		 * Reflects the instance about another vector.
		 * @param mirror Vector to reflect the instance about.
		 */
		void reflect(const Vector2 &mirror);

		/**
		 * Serializes the instance to a Value.
		 * @param node Value to serialize the Vector2T to.
		 * @param setName Wether or not we need to set the name.
		 * @see BaconBox::DefaultSerializer
		 */
		void serialize(Value &node, bool setName = true) const {
			if (setName) {
				node.setName("Vector2");
			}

			// We set the value's attributes correctly.
			node["x"].setDouble(static_cast<double>(x));
			node["x"].setAttribute(true);
			node["y"].setDouble(static_cast<double>(y));
			node["y"].setAttribute(true);
		}

		/**
		 * Deserializes the instance from a Value.
		 * @param node Value to deserialize the value from.
		 * @see BaconBox::DefaultSerializer
		 */
		bool deserialize(const Value &node) {
			bool result = true;

			// The vector can either be an array of two values or an object
			// with the x and y members.
			if (node.getArray().size() == 2) {
				x = static_cast<ValueType>(node.getArray()[0].getDouble());
				y = static_cast<ValueType>(node.getArray()[1].getDouble());
			} else {
				Object::const_iterator itX = node.getObject().find("x");
				Object::const_iterator itY = node.getObject().find("y");

				// We make sure the value contains the "x" and "y" values.
				if (itX != node.getObject().end() &&
				    itY != node.getObject().end() &&
				    itX->second.isNumeric() && itY->second.isNumeric()) {

					x = static_cast<ValueType>(itX->second.getDouble());
					y = static_cast<ValueType>(itY->second.getDouble());

				} else {
					result = false;
				}
			}

			return result;
		}

		/**
		 * Checks whether or not the Value contains the necessary information
		 * to deserialize a Vector2T.
		 * @param node Value to check.
		 * @return True if the value contains the necessary information, false
		 * if not.
		 */
		static bool isValidValue(const Value &node) {
			Object::const_iterator itX = node.getObject().find("x");
			Object::const_iterator itY = node.getObject().find("y");

			return node.getArray().size() == 2 || (itX != node.getObject().end() && itY != node.getObject().end() &&
			       itX->second.isNumeric() && itY->second.isNumeric());

		}

		/**
		 * X coordinate. Positive values increase towards the right, while
		 * negative values decrease towards the left.
		 */
		ValueType x;

		/**
		 * Y coordinate. Positive values increase towards the bottom, while
		 * negative values decrease towards the top.
		 */
		ValueType y;
	};
#pragma pack()
	template <typename T>
	Vector<T, 2u>::Vector() : x(ZERO), y(ZERO) {}
	template <typename T>
	Vector<T, 2u>::Vector(XComponent newX) : x(newX.value), y(ZERO) {}
	template <typename T>
	Vector<T, 2u>::Vector(YComponent newY) : x(ZERO), y(newY.value) {}
	template <typename T>
	Vector<T, 2u>::Vector(XComponent newX, YComponent newY) : x(newX.value), y(newY.value) {}
	template <typename T>
	Vector<T, 2u>::Vector(const Vector2 &src) : x(src.x), y(src.y) {}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator=(const Vector2 &src) {
		x = src.x;
		y = src.y;
		return *this;
	}
	template <typename T>
	bool Vector<T, 2u>::operator==(const Vector2 &other) const {
		return x == other.x && y == other.y;
	}
	template <typename T>
	bool Vector<T, 2u>::operator!=(const Vector2 &other) const {
		return x != other.x || y != other.y;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator+=(const Vector2 &other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator+=(ValueType delta) {
		x += delta;
		y += delta;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator+=(XComponent xDelta) {
		x += xDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator+=(YComponent yDelta) {
		y += yDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator-=(const Vector2 &other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator-=(ValueType delta) {
		x -= delta;
		y -= delta;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator-=(XComponent xDelta) {
		x -= xDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator-=(YComponent yDelta) {
		y -= yDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator*=(ValueType delta) {
		x *= delta;
		y *= delta;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator*=(XComponent xDelta) {
		x *= xDelta.value;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator*=(YComponent yDelta) {
		y *= yDelta.value;
		return *this;
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator/=(ValueType delta) {
		x /= delta;
		y /= delta;
		return *this;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator/=(XComponent xDelta) {
		x /= xDelta.value;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::operator/=(YComponent yDelta) {
		y /= yDelta.value;
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator+(const Vector2 &other) const {
		return Vector2(*this) += other;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator+(ValueType delta) const {
		return Vector2(*this) += delta;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator+(XComponent xDelta) const {
		return Vector2(*this) += xDelta;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator+(YComponent yDelta) const {
		return Vector2(*this) += yDelta;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator+() const {
		return Vector2(+x, +y);
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator-(const Vector2 &other) const {
		return Vector2(*this) -= other;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator-(ValueType delta) const {
		return Vector2(*this) -= delta;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator-(XComponent xDelta) const {
		return Vector2(*this) -= xDelta;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator-(YComponent yDelta) const {
		return Vector2(*this) -= yDelta;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator-() const {
		return Vector2(-x, -y);
	}

	template <typename T>
	typename Vector<T, 2u>::ValueType Vector<T, 2u>::operator*(const Vector2 &other) const {
		return getDotProduct(other);
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator*(ValueType delta) const {
		return Vector2(*this) *= delta;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator*(XComponent xDelta) const {
		return Vector2(*this) *= xDelta;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator*(YComponent yDelta) const {
		return Vector2(*this) *= yDelta;
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator/(ValueType delta) const {
		return Vector2(*this) /= delta;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator/(XComponent xDelta) const {
		return Vector2(*this) /= xDelta;
	}
	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::operator/(YComponent yDelta) const {
		return Vector2(*this) /= yDelta;
	}

	template <typename T>
	typename Vector<T, 2u>::ValueType Vector<T, 2u>::getLength() const {
		return std::sqrt(getDotProduct(*this));
	}

	template <typename T>
	void Vector<T, 2u>::setLength(ValueType newLength) {
		normalize();
		this->operator*=(newLength);
	}

	template <typename T>
	typename Vector<T, 2u>::ValueType Vector<T, 2u>::getSquaredLength() const {
		return getDotProduct(*this);
	}

	template <typename T>
	typename Vector<T, 2u>::ValueType Vector<T, 2u>::getDotProduct(const Vector2 &other) const {
		return x * other.x + y * other.y;
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::getNormalized() const {
		return *this / getLength();
	}

	template <typename T>
	void Vector<T, 2u>::normalize() {
		this->operator/=(getLength());
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::coordinatesMultiply(const Vector2 &other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::getCoordinatesMultiplication(const Vector2 &other) const {
		return Vector2(*this).coordinatesMultiply(other);
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 &Vector<T, 2u>::coordinatesDivide(const Vector2 &other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::getCoordinatesDivision(const Vector2 &other) const {
		return Vector2(*this).coordinatesDivide(other);
	}

	template <typename T>
	typename Vector<T, 2u>::ValueType Vector<T, 2u>::getAngle() const {
		return (x < UP.x) ? (getAngleBetween(UP)) : (-getAngleBetween(UP));
	}

	template <typename T>
	typename Vector<T, 2u>::ValueType Vector<T, 2u>::getAngleBetween(const Vector2 &other) const {
		return MathHelper::AngleConvert<T>::RADIANS_TO_DEGREES * (std::acos(getDotProduct(other) / (getLength() * other.getLength())));
	}

	template <typename T>
	void Vector<T, 2u>::setAngle(ValueType newAngle) {
		rotate(newAngle - getAngle());
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::getRotated(ValueType angle) const {
		Vector2 result(*this);
		result.rotate(angle);
		return result;
	}

	template <typename T>
	void Vector<T, 2u>::rotate(ValueType angle) {
		ValueType radians = MathHelper::AngleConvert<ValueType>::DEGREES_TO_RADIANS * angle;
		ValueType tmpX = x;
		x = x * std::cos(radians) + y * std::sin(radians);
		y = y * std::cos(radians) - tmpX * std::sin(radians);
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::getProjection(const Vector2 &direction) const {
		Vector2 result(*this);
		result.project(direction);
		return result;
	}

	template <typename T>
	void Vector<T, 2u>::project(const Vector2 &direction) {
		*this = direction * (*this * direction) / (direction * direction);
	}

	template <typename T>
	typename Vector<T, 2u>::Vector2 Vector<T, 2u>::getReflected(const Vector2 &mirror) const {
		Vector2 result(*this);
		result.reflect(mirror);
		return result;
	}

	template <typename T>
	void Vector<T, 2u>::reflect(const Vector2 &mirror) {
		Vector2 original(*this);
		project(mirror);
		*this += *this - original;
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &output, const Vector<T, 2u>& v) {
		Value tmpValue;
		DefaultSerializer::serialize(v, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}

	typedef Vector<float> Vector2;
}

#endif
