/**
 * @file
 * @ingroup Math
 * @ingroup Display
 * @ingroup Physics
 */
#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

#include <cmath>
#include <iostream>

#include "Debug.h"
namespace RedBox{
	/**
	 * Two-dimensional vector. Vector represented in two dimensions.
	 * @ingroup Math
	 * @ingroup Display
	 * @ingroup Physics
	 */
	class Vec2 {
        /**
         * Outputs the vector's content.
         * @param output The ostream in which Vec2 is output.
         * @param v Vec2 to output in the ostream.
         * @return Resulting ostream.
         */
        friend std::ostream& operator<<(std::ostream& output, const Vec2& v);
	public:
		/**
		 * Default constructor. By default, the vector doesn't use pointers.
		 */
		Vec2();
		/**
		 * Parametrized vector with direct values.
		 * @param pX Vector's horizontal value.
		 * @param pY Vector's vertical value.
		 */
		Vec2(float pX, float pY);
		/**
		 * Parametrized vector with pointers. In OpenGL's case, the pointers
		 * point to the values in the array used by OpenGL's functions.
		 * @param pX Vector's pointer to its horizontal value.
		 * @param pY Vector's pointer to its vertical value.
		 */
		Vec2(float* pX, float* pY);
		/**
		 * Copy constructor. Makes the instance a copy of the recieved vector.
		 * @param src Vector to make a copy of.
		 */
		Vec2(const Vec2& src);
		/**
		 * The destructor.
		 */
		~Vec2();
		/**
		 * Gets the vector's horizonal value. It reads either the pointer or
		 * the direct value in the union depending on the boolean isPtr.
		 * @return Vector's horizontal value.
		 */
		float getX() const;
		/**
		 * Gets the vector's vertical value. It reads either the pointer or
		 * the direct value in the union depending on the boolean isPtr.
		 * @return Vector's vertical value.
		 */
		float getY() const;
		/**
		 * Gets 2D vector's pointer to the x value.
		 * @return Pointer to the x value, if the 2D vector doesn't keep
		 * pointers, returns NULL.
		 */
		float* getXPtr();
		/**
		 * Gets 2D vector's pointer to the y value.
		 * @return Pointer to the y value, if the 2D vector doesn't keep
		 * pointers, returns NULL.
		 */
		float* getYPtr();
		/**
		 * Sets the pointer to the vector's horizontal value. If isPtr is set to
		 * false, this function does nothing whatever is recieved as a
		 * parameter.
		 * @param newXPtr New pointer to the vector's horizontal value.
		 */
		void setXPtr(float* newXPtr);
		/**
		 * Sets the pointer to the vector's vertical value. If isPtr is set to
		 * false, this function does nothing whatever is recieved as a
		 * parameter.
		 * @param newYPtr New pointer to the vector's vertical value.
		 */
		void setYPtr(float* newYPtr);
		/**
		 * Sets the vector's horizontal value. If isPtr is set to true, the 
		 * pointed value will be changed.
		 * @param newX New vector's horizontal value.
		 */
		void setX(float newX);
		/**
		 * Sets the vector's vertical value. If isPtr is set to true, the 
		 * pointed value will be changed.
		 * @param newX New vector's vertical value.
		 */
		void setY(float newY);
		/**
		 * Does the vector store pointers? If not, it means it directly stores
		 * the values.
		 * @return True if the vector stores pointers, false if it stores the
		 * direct values.
		 */
		bool getIsPtr() const;
		/**
		 * Sets if the vector stores pointers or direct values.
		 * @param newIsPtr True makes the vector read its values as pointers,
		 * else as direct values.
		 */
		void setIsPtr(bool newIsPtr);
		
		/**
		 * Does a multiplication of the vector and a scalar.
		 * @param scalar Scalar value to multiply the vector by.
		 * @return Vector resulting from the multiplication with a scalar.
		 */
		const Vec2 operator*( float scalar ) const;
		/**
		 * Does a scalar division on the vector.
		 * @param scalar Scalar value to divide the vector by.
		 * @return Vector resulting from the scalar division.
		 */
		const Vec2 operator/( float scalar ) const;
		/**
		 * Adds two vectors.
		 * @param b Vector to add.
		 * @result Vector resulting from the addition of b and the object's
		 * instance.
		 */
		const Vec2 operator+( Vec2 b ) const;
		/**
		 * Substract the vector with another vector.
		 * @param b Vector to substract.
		 * @result Vector resulting from the substraction of object's instance
		 * by b.
		 */
		const Vec2 operator-( Vec2 b ) const;
		/**
		 * Calculate the inverse vector. Changes the vector's value's sign.
		 * @return Vector with its horizontal and vertical value's sign
		 * inversed.
		 */
		const Vec2 operator-() const;
		/**
		 * Scalar multiplication of two vectors. Multiplies the instance's
		 * vector with the vector recieved.
		 * @param b Vector to multiply with the instance's.
		 * @return Scalar resulting from the multiplication of the two vectors.
		 */
		const float operator*( Vec2 b ) const;
		/**
		 * Makes the instance's vector have the same values as the one recieved.
		 * @param b Vector with the values to be copied into the instance's
		 * vector.
		 * @return Vector resulting from the assignation.
		 */
		Vec2& operator=(const Vec2& b );
		/**
		 * Adds a vector to the instance.
		 * @param b Vector to add to the instance.
		 * @return Vector resulting from the addition.
		 */
		Vec2& operator+=( const Vec2& b );
		/**
		 * Substracts a vector from the instance.
		 * @param b Vector to substract from the instance.
		 * @return Vector resulting from the substraction.
		 */
		Vec2& operator-=( const Vec2& b );
		/**
		 * Multiplicate the vector with a scalar.
		 * @param scalar Scalar value to multiply the vector by.
		 * @return Vector resulting from the multiplication.
		 */
		Vec2& operator*=( float scalar );
		/**
		 * Divides the vector by a scalar.
		 * @param scalar Scalar value to divide the vector by.
		 * @return Vector resulting from the division.
		 */
		Vec2& operator/=( float scalar );
		/**
		 * Checks if two vectors have the same values.
		 * @param b Vector to do the comparison with.
		 * @return True if the vectors have the same values, false if not.
		 */
		bool operator==( const Vec2& b );
		/**
		 * Checks if the two vectors have different values.
		 * @param b Vector to do the comparison with.
		 * @return True if the vectors have different values, false if not.
		 */
		bool operator!=( const Vec2& b );
		
		/**
		 * Calculates the vector's length.
		 * @return Length of the vector.
		 */
		float length() const;
		/**
		 * Calculates the vector's length squared.
		 */
		float lengthSq() const;
		/**
		 * Normalizes the vector. It changes the vector's values to make the 
		 * vector have a length of one. If the vector initially has a length of 
		 * zero, it will instead print an error message. 
		 */
		void normalize();
	private:
		/**
		 * Uses pointers or not depending on the necessities. If the vector is
		 * to be used with OpenGL, the pointers will point to values in the 
		 * vertex's array that OpenGL uses. If it is only used for physics (for
		 * example), it will only use the direct values.
		 */
		union {
			struct {
				float x;
				float y;
			} coordsVal;
			struct {
				float* x;
				float* y;
			} coordsPtr;
		};
		/// If vector is to access x and y using pointers.
		bool isPtr;
		/**
		 * Makes the instance a copy of the recieved vector. The resulting copy
         * will always be using direct values and not pointers.
		 * @param src Vector to make a copy of.
		 */
		void copyFrom(const Vec2& src);
	};
}

#endif
