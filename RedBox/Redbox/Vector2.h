/**
 * @file
 * @ingroup Math
 */
#ifndef RB_VECTOR_2_H
#define RB_VECTOR_2_H

#include <iostream>
#include <cmath>

#include "StaticAssert.h"
#include "IsNumber.h"
#include "MathHelper.h"

namespace RedBox {
#pragma pack(1)
	/**
	 * Represents a 2D euclidean vector. Templated so it can only be a vector of
	 * floats, doubles or long doubles.
	 * @ingroup Math
	 * @tparam T Type of data to use as the Vector2T's coordinates.
	 */
	template <typename T>
	class Vector2T {
		template <typename U> friend std::ostream &operator<<(std::ostream &output, const Vector2T<U>& v);
	public:
		/// Fundamental floating point number type the vector contains.
		typedef T ValueType;

		/// Normalized vector that points up.
		static const Vector2T<ValueType> UP;

		/// Default value.
		static const ValueType DEFAULT_VALUE;

		/**
		 * Default constructor.
		 */
		Vector2T() : x(DEFAULT_VALUE), y(DEFAULT_VALUE) {
		}

		/**
		 * Parameterized constructor.
		 * @param newX Starting x value.
		 * @param newY Starting y value.
		 */
		Vector2T(ValueType newX, ValueType newY) : x(newX), y(newY) {
		}

		/**
		 * Copy constructor.
		 * @param src Vector2 to make a copy of.
		 */
		Vector2T(const Vector2T<ValueType>& src) : x(src.x), y(src.y) {
		}

		/**
		 * Assignment operator overload.
		 * @param src Vector2 to make a copy of.
		 * @return Reference to the modified instance.
		 */
		Vector2T<ValueType>& operator=(const Vector2T<ValueType>& src) {
			if (this != &src) {
				setX(src.getX());
				setY(src.getY());
			}

			return *this;
		}

		/**
		 * Adds a vector to the instance. Adds the right-hand side vector's
		 * x and y coordinates to the instance's x and y coordinates
		 * respectively.
		 * @param rhs Vector to add to the instance.
		 * @return Reference to the modified instance.
		 */
		Vector2T<ValueType>& operator+=(const Vector2T<ValueType>& rhs) {
			addToXY(rhs);
			return *this;
		}

		/**
		 * Adds a scalar value to both of the instance's coordinates.
		 * @param rhs Scalar value to add to the instance's coordinates.
		 * @return Reference to the modified instance.
		 */
		Vector2T<ValueType>& operator+=(ValueType rhs) {
			addToXY(rhs);
			return *this;
		}

		/**
		 * Subtracts a vector from the instance. Subtracts the right-hand
		 * side vector's x and y coordinates from the instance's x and y
		 * coordinates respectively.
		 * @param rhs Vector to subtract from the instance.
		 * @return Reference to the modified instance.
		 */
		Vector2T<ValueType>& operator-=(const Vector2T<ValueType>& rhs) {
			subtractFromXY(rhs);
			return *this;
		}

		/**
		 * Subtracts a scalar value from both of the instance's coordinates.
		 * @param rhs Scalar value to subtract from the instance's coordinates.
		 * @return Reference to the modified instance.
		 */
		Vector2T<ValueType>& operator-=(ValueType rhs) {
			subtractFromXY(rhs);
			return *this;
		}

		/**
		 * Multplies the instance's coordinates by a scalar factor.
		 * @param rhs Scalar factor to multiply by the instance's coordinates.
		 * @return Reference to the modified instance.
		 */
		Vector2T<ValueType>& operator*=(ValueType rhs) {
			scalarMultiplication(rhs);
			return *this;
		}

		/**
		 * Divides the instance's coordinates by the right-hand side divisor.
		 * @param rhs Scalar divisor to divide the instance's coordinates with.
		 * @return Reference to the modified instance.
		 */
		Vector2T<ValueType>& operator/=(ValueType rhs) {
			scalarDivision(rhs);
			return *this;
		}

		/**
		 * Does a scalar division to the instance's coordinates by using the
		 * right-hand side's coordinates as the divisiors.
		 * @param rhs Vector containing the coordinates to be used as the
		 * divisors.
		 * @return Reference to the modified insance.
		 */
		Vector2T<ValueType>& operator/=(const Vector2T<ValueType> &rhs) {
			scalarDivision(rhs);
			return *this;
		}

		/**
		 * Adds to vectors's coordinates together.
		 * @param other Vector to add to the instance's copy.
		 * @return Sum of the instance's copy and the recieved vector.
		 */
		const Vector2T<ValueType> operator+(const Vector2T<ValueType>& other) const {
			return Vector2T<ValueType>(*this) += other;
		}

		/**
		 * Adds a vector and a scalar value together.
		 * @param other Scalar value to add to the instance's copy.
		 * @return Sum of the instance's copy and the recieved scalar value.
		 */
		const Vector2T<ValueType> operator+(ValueType other) const {
			return Vector2T<ValueType>(*this) += other;
		}

		/**
		 * Subtracts a vector from another vector.
		 * @param other Vector representing the subtraction's subtrahend.
		 * @return Difference between the instance's copy and the recieved
		 * vector.
		 */
		const Vector2T<ValueType> operator-(const Vector2T<ValueType>& other) const {
			return Vector2T<ValueType>(*this) -= other;
		}

		/**
		 * Substracts a scalar value from a vector's coordinates.
		 * @param other Scalar value representing the subtraction's subtrahend.
		 * @return Difference between the instance's copy and the recieved
		 * scalar value.
		 */
		const Vector2T<ValueType> operator-(ValueType other) const {
			return Vector2T<ValueType>(*this) -= other;
		}

		/**
		 * Multiplies a vector's coordinates with a scalar value.
		 * @param other Scalar value to multiply the copy of the instance's
		 * coordinates with.
		 * @return Product of the copy of the instance and the recieved
		 * scalar value.
		 */
		const Vector2T<ValueType> operator*(ValueType other) const {
			return Vector2T<ValueType>(*this) *= other;
		}

		/**
		 * Calculates the dot product between two vectors (V1 ∙ V2).
		 * @param other Vector to use as the right factor.
		 * @result Dot product between the instance and the recieved vector.
		 */
		ValueType operator*(const Vector2T<ValueType>& other) const {
			return getDotProduct(other);
		}

		/**
		 * Divides a vector's coordinates by a scalar value.
		 * @param other Scalar value to divide the copy of the instance's
		 * coordinates by.
		 * @return Quotient of the copy of the instance and the recieved
		 * scalar value.
		 */
		const Vector2T<ValueType> operator/(ValueType other) const {
			return Vector2T<ValueType>(*this) /= other;
		}

		/**
		 * Divides a vector's coordinates by another vector's coordinates.
		 * @param other Vector containing the coordinates to use as the
		 * divisors.
		 * @return Quotient of the copy of the instance and the recieved
		 * vector.
		 */
		const Vector2T<ValueType> operator/(const Vector2T<ValueType> &other) const {
			return Vector2T<ValueType>(*this) /= other;
		}

		/**
		 * Checks if the instance has the same coordinates as another vector.
		 * @param other Vector to check equality with.
		 * @return True if the instance has the same coordinate values as the
		 * recieved vector, false if not.
		 */
		bool operator==(const Vector2T<ValueType>& other) const {
			return getX() == other.getX() && getY() == other.getY();
		}

		/**
		 * Checks if the instance's coordinates are different from another
		 * vector.
		 * @param other Vector to check inequality with.
		 * @return True if the instance's coordinates are different from the
		 * recieved vector, false if they are equal.
		 */
		bool operator!=(const Vector2T<ValueType>& other) const {
			return !(*this == other);
		}

		/**
		 * Gets the instance's x coordinate.
		 * @return Instance's x coordinate.
		 * @see RedBox::Vector2T<T>::x
		 */
		ValueType getX() const {
			return x;
		}

		/**
		 * Gets the instance's y coordinate.
		 * @return Instance's y coordinate.
		 * @see RedBox::Vector2T<T>::y
		 */
		ValueType getY() const {
			return y;
		}

		/**
		 * Sets the instance's x coordinate.
		 * @param newX New x coordinate's value.
		 * @see RedBox::Vector2T<T>::x
		 */
		void setX(ValueType newX) {
			x = newX;
		}

		/**
		 * Sets the instance's y coordinate.
		 * @param newY New y coordinate's value.
		 * @see RedBox::Vector2T<T>::y
		 */
		void setY(ValueType newY) {
			y = newY;
		}

		/**
		 * Sets the instance's x and y coordinates.
		 * @param newX New x coordinate's value.
		 * @param newY New y coordinate's value.
		 * @see RedBox::Vector2T<T>::x
		 * @see RedBox::Vector2T<T>::y
		 */
		void setXY(ValueType newX, ValueType newY) {
			setX(newX);
			setY(newY);
		}

		/**
		 * Adds a value to the instance's x coordinate.
		 * @param xDelta Value to add to the instance's x coordinate.
		 */
		void addToX(ValueType xDelta) {
			setX(getX() + xDelta);
		}

		/**
		 * Adds a value to the instance's y coordinate.
		 * @param yDelta Value to add to the instance's y coordinate.
		 */
		void addToY(ValueType yDelta) {
			setY(getY() + yDelta);
		}

		/**
		 * Adds values to the instance's y and y coordinates.
		 * @param xDelta Value to add to the instance's x coordinate.
		 * @param yDelta Value to add to the instance's y coordinate.
		 */
		void addToXY(ValueType xDelta, ValueType yDelta) {
			addToX(xDelta);
			addToY(yDelta);
		}

		/**
		 * Adds a vector's x and y coordinates to the instance's x and y
		 * coordinates respectively.
		 * @param delta Vector to add to the instance.
		 */
		void addToXY(const Vector2T<ValueType>& delta) {
			addToXY(delta.x, delta.y);
		}

		/**
		 * Adds a value to both of the instance's coordinates.
		 * @param delta Value to add to the instance's coordinates.
		 */
		void addToXY(ValueType delta) {
			addToXY(delta, delta);
		}

		/**
		 * Subtracts a value from the instance's x coordinate.
		 * @param xDelta Value to subtract from the instance's x coordinate.
		 */
		void subtractFromX(ValueType xDelta) {
			setX(getX() - xDelta);
		}

		/**
		 * Subtracts a value from the instance's y coordinate.
		 * @param yDelta Value to subtract from the instance's y coordinate.
		 */
		void subtractFromY(ValueType yDelta) {
			setY(getY() - yDelta);
		}

		/**
		 * Subtracts values from the instance's x and y coordinates.
		 * @param xDelta Value to subtract from the instance's x coordinate.
		 * @param yDelta Value to subtract from the instance's y coordinate.
		 */
		void subtractFromXY(ValueType xDelta, ValueType yDelta) {
			subtractFromX(xDelta);
			subtractFromY(yDelta);
		}

		/**
		 * Subtracts a vector's x and y coordinates from the instance's x and y
		 * coordinates respectively.
		 * @param delta Vector to subtract from the instance.
		 */
		void subtractFromXY(const Vector2T<ValueType>& delta) {
			subtractFromXY(delta.x, delta.y);
		}

		/**
		 * Subtracts a value from both of the instance's coordinates.
		 * @param delta Value to subtract from the instance's coordinates.
		 */
		void subtractFromXY(ValueType delta) {
			subtractFromXY(delta, delta);
		}

		/**
		 * Multiplies the instance's coordinates by given factors.
		 * @param xFactor X factor to multiply the instance's x coordinate by.
		 * @param yFactor Y factor to multiply the instance's x coordinate by.
		 */
		void scalarMultiplication(ValueType xFactor, ValueType yFactor) {
			setXY(getX() * xFactor, getY() * yFactor);
		}

		/**
		 * Mulitplies the instance's coordinates by another vector's
		 * coordinates.
		 * @param factor Vector containing the coordinates to mulitply the
		 * instance's coordinates by.
		 */
		void scalarMultiplication(const Vector2T<ValueType>& factor) {
			scalarMultiplication(factor.getX(), factor.getY());
		}

		/**
		 * Multiplies the instance's coordinates by a given factor.
		 * @param factor Factor to multiply the instance's coordinates by.
		 */
		void scalarMultiplication(ValueType factor) {
			scalarMultiplication(factor, factor);
		}

		/**
		 * Divides the instance's coordinates by given divisors.
		 * @param xDivisor X divisor to divide the instance's x coordinate by.
		 * @param yDivisor Y divisor to divide the instance's x coordinate by.
		 */
		void scalarDivision(ValueType xDivisor, ValueType yDivisor) {
			setXY(getX() / xDivisor, getY() / yDivisor);
		}

		/**
		 * Divides the instance's coordinates by another vector's coordinates.
		 * @param divisor Vector containing the coordinates to use as the
		 * divisors.
		 */
		void scalarDivision(const Vector2T<ValueType> &divisor) {
			scalarDivision(divisor.getX(), divisor.getY());
		}

		/**
		 * Divides the instance's coordinates by a given divisor.
		 * @param divisor Divisor to divide the instance's coordinates by.
		 */
		void scalarDivision(ValueType divisor) {
			scalarDivision(divisor, divisor);
		}

		/**
		 * Calculates the dot product between the instance and another vector.
		 * @param other Other vector used to calculate the dot product.
		 * @return Resulting dot product.
		 */
		ValueType getDotProduct(const Vector2T<ValueType>& other) const {
			return getX() * other.getX() + getY() * other.getY();
		}

		/**
		 * Calculates the instance's length. Also known as the magnitude or the
		 * norm.
		 * @return Instance's length.
		 */
		ValueType getLength() const {
			return sqrt(getDotProduct(*this));
		}

		/**
		 * Changes the vector's length.
		 * @param newLength New length to set to the vector.
		 */
		void setLength(ValueType newLength) {
			normalize();
			scalarMultiplication(newLength);
		}

		/**
		 * Normalizes the instance. Makes the instance have a length of 1, but
		 * keeps the same angle.
		 */
		void normalize() {
			scalarDivision(getLength());
		}

		/**
		 * Calculates the angle between the instance and another vector.
		 * @param other Other vector to calculate the angle between.
		 * @return Angle between the two vectors.
		 */
		ValueType getAngleBetween(const Vector2T<ValueType>& other) const {
			return MathHelper::radiansToDegrees(acos(getDotProduct(other) / (getLength() * other.getLength())));
		}

		/**
		 * Gets the angle relative to the UP vector (in degrees).
		 * @return Angle between -180 and 180. Angle increases as it goes
		 * clockwise.
		 */
		ValueType getAngle() const {
			return (getX() < DEFAULT_VALUE) ? (-getAngleBetween(UP)) : (getAngleBetween(UP));
		}

		/**
		 * Rotates the instance.
		 * @param angle Angle to rotate the instance (in degrees). Positive
		 * values make the instance rotate clockwise, while negative values make
		 * the instance rotate counter clockwise.
		 */
		void rotate(ValueType angle) {
			float radians = MathHelper::degreesToRadians(angle);
			setXY(getX() * cosf(radians) + getY() * sinf(radians),
			      getY() * cosf(radians) - getX() * sinf(radians));
		}

		/**
		 * Projects the instance on a vector.
		 * @param other Vector to project the instance onto.
		 */
		void project(const Vector2T<ValueType>& other) {
			*this = other * (*this * other) / (other * other);
		}

		/**
		 * Reflects the instance about another vector.
		 * @param other Vector to reflect the the instance about.
		 */
		void reflect(const Vector2T<ValueType>& other) {
			Vector2T<ValueType> original(*this);
			project(other);
			*this += *this - original;
		}
	private:
		/**
		 * X coordinate. Positive values inscrease towards the right, while
		 * negative values decrease towards the left.
		 */
		ValueType x;

		/**
		 * Y coordinate. Positive values increase towards the bottom, while
		 * negative values decrease towards the top.
		 */
		ValueType y;

		// Used to make sure the vector is templated with floating point
		// numbers.
		typedef typename StaticAssert<IsFloatingPointNumber<ValueType>::RESULT>::Result Test;
	};
#pragma pack()

	template <typename T>
	std::ostream &operator<<(std::ostream &output, const Vector2T<T>& v) {
		output << "{x: " << v.x << ", y: " << v.y << "}";
		return output;
	}

	/// Used as the basic 2D vectors for RedBox.
	typedef Vector2T<float> Vector2;
}

#endif
