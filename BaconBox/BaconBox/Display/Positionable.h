/**
 * @file
 * @ingroup Display
 */
#ifndef RB_POSITIONABLE_H
#define RB_POSITIONABLE_H

#include "BaconBox/Vector2.h"

namespace BaconBox {
	/**
	 * Represents a body that has a position and a size. All bodies that have
	 * a position and a size are derived from this class.
	 * @ingroup Display
	 */
	class Positionable {
	public:
		/**
		 * Default constructor.
		 */
		Positionable();

		/**
		 * Parameterized constructor.
		 * @param newPosition Starting position.
		 * @see BaconBox::Positionable::position
		 */
		explicit Positionable(const Vector2 &newPosition);

		/**
		 * Copy constructor.
		 * @param src Positionable to make a copy of.
		 */
		Positionable(const Positionable &src);

		/**
		 * Destructor.
		 */
		virtual ~Positionable();

		/**
		 * Assignment operator.
		 * @param src Positionable to make a copy of.
		 * @return Reference to the modified Positionable.
		 */
		Positionable &operator=(const Positionable &src);

		/**
		 * Gets the body's horizontal and vertical position.
		 * @return 2D vector containing the horizontal and vertical position.
		 * @see BaconBox::Positionable::position
		 */
		const Vector2& getPosition() const;

		/**
		 * Sets the Positionable's horizontal and vertical position.
		 * @param newPosition New horizontal and vertical position.
		 * @see Positionable::setPosition(float x, float y)
		 * @see BaconBox::Positionable::position
		 */
		void setPosition(const Vector2& newPosition);

		/**
		 * Sets the Positionable's horizontal and vertical position.
		 * @param newXPosition New horizontal position (in pixels). Lower value
		 * means more to the left.
		 * @param newYPosition New vertical position (in pixels). Lower value
		 * means more at the top.
		 * @see BaconBox::Positionable::position
		 */
		void setPosition(float newXPosition, float newYPosition);

		/**
		 * Moves the Positionable horizontally and vertically.
		 * @param delta 2D vector to add to the Positionable's position (in
		 * pixels).
		 * @see BaconBox::Positionable::move(float deltaX, float deltaY)
		 * @see BaconBox::Positionable::position
		 */
		void move(const Vector2& delta);

		/**
		 * Moves the Positionable horizontally and vertically.
		 * @param xDelta Value to add to the Positionable's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the Positionable to the left.
		 * @param yDelta Value to add to the Positionable's vertical position (in
		 * pixels). Positive value moves the Positionable down and a negative
		 * value moves the Positionable up.
		 * @see BaconBox::Positionable::move(const Vector2& delta);
		 * @see BaconBox::Positionable::position
		 */
		virtual void move(float xDelta, float yDelta);

		/**
		 * Gets the Positionable's horizontal position.
		 * @return Horizontal position (in pixels). Lower value means more to
		 * the left.
		 * @see BaconBox::Positionable::position
		 */
		float getXPosition() const;

		/**
		 * Sets the Positionable's horizontal position.
		 * @param newXPosition New horizontal position (in pixels). Lower value
		 * means more to the left.
		 * @see BaconBox::Positionable::position
		 */
		void setXPosition(float newXPosition);

		/**
		 * Moves the body horizontally.
		 * @param xDelta Value to add to the Positionable's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the Positionable to the left.
		 * @see BaconBox::Positionable::position
		 */
		void moveX(float xDelta);

		/**
		 * Gets the body's vertical position.
		 * @return Vertical position (in pixels). Lower value means more at the
		 * top.
		 * @see BaconBox::Positionable::position
		 */
		float getYPosition() const;

		/**
		 * Sets the body's horizontal position.
		 * @param newYPosition New vertical position (in pixels). Lower value
		 * means more at the top.
		 * @see BaconBox::Positionable::position
		 */
		void setYPosition(float newYPosition);

		/**
		 * Moves the Positionable vertically.
		 * @param yDelta Value to add to the Positionable's vertical position (in
		 * pixels). Positive value moves the Positionable down and a negative
		 * value moves the body up.
		 * @see BaconBox::Positionable::position
		 */
		void moveY(float yDelta);

		/**
		 * Gets the body's center's position.
		 * @return 2D vector containing the body's center's position.
		 */
		virtual const Vector2 getPositionCenter() const;

		/**
		 * Gets the body's center's horizontal position.
		 * @return Body's center's horizontal position.
		 */
		float getXPositionCenter() const;

		/**
		 * Gets the body's center's vertical position.
		 * @return Body's center vertical position.
		 */
		float getYPositionCenter() const;

		/**
		 * Gets the geometric center of the body. Same as the position center
		 * in symmetrical polygons, but must be overloaded for classes that
		 * support irregular polygons.
		 * @return Geometric center of the body (barycenter).
		 */
		virtual const Vector2 getCentroid() const;

		/**
		 * Gets the horizontal geometric center of the body. Same as the
		 * horizontal center position in symmetrical polygons, but different for
		 * other polygons.
		 * @return Horizontal geometric center of the body (barycenter).
		 */
		float getXCentroid() const;

		/**
		 * Gets the vertical geometric center of the body. Same as the vertical
		 * center position in symmetrical polygons, but different for other
		 * polygons.
		 * @return Vertical geometric center of the body (barycenter).
		 */
		float getYCentroid() const;

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		virtual const Vector2 getSize() const;

		/**
		 * Gets the body's width.
		 * @return Width in pixels (by default).
		 */
		virtual float getWidth() const = 0;

		/**
		 * Gets the body's height.
		 * @return Height in pixels (by default).
		 */
		virtual float getHeight() const = 0;
	private:
		/**
		 * Horizontal and vertical position. Position (0, 0) is at the upper
		 * left corner. The higher the horizontal value, the more to the right
		 * the body is. The higher the vertical value, the more to the bottom
		 * the body is.
		 */
		Vector2 position;
	};

}

#endif
