/**
 * @file
 * @ingroup Display
 */
#ifndef RB_TRANSFORMABLE_H
#define RB_TRANSFORMABLE_H

#include "Positionable.h"

namespace RedBox {
	/**
	 * Bodies that can be rotated and scaled are derived from this class.
	 * @ingroup Display
	 */
	class Transformable : public Positionable {
	public:
		/**
		 * Default constructor.
		 */
		Transformable();

		/**
		 * Parameterized constructor.
		 * @param newPosition Starting position.
		 * @param newScaling Starting scaling.
		 * @param newAngle Starting angle.
		 * @see RedBox::Positionable::position
		 * @see RedBox::Transformable::scaling
		 * @see RedBox::Transformable::angle
		 */
		explicit Transformable(const Vector2 &newPosition,
		                       const Vector2 &newScaling = Vector2(1.0f, 1.0f),
		                       float newAngle = 0.0f);

		/**
		 * Copy constructor.
		 * @param src Transformable to make a copy of.
		 */
		Transformable(const Transformable &src);

		/**
		 * Destructor.
		 */
		virtual ~Transformable();

		/**
		 * Assignment operator.
		 * @param src Transformable to make a copy of.
		 * @return Reference to the modified Transformable.
		 */
		Transformable &operator=(const Transformable &src);

		/**
		 * Gets the body's scaling.
		 * @return 2D vector containing the body's scaling.
		 * @see RedBox::Transformable::scaling
		 */
		const Vector2 &getScaling() const;

		/**
		 * Changes the body's scaling.
		 * @param newScaling New scaling to apply.
		 * @see RedBox::Transformable::scaling
		 */
		void setScaling(const Vector2 &newScaling);

		/**
		 * Changes the body's scaling.
		 * @param newXScaling New horizontal scaling to apply.
		 * @param newYScaling New vertical scaling to apply.
		 * @see RedBox::Transformable::scaling
		 */
		void setScaling(float newXScaling, float newYScaling);

		/**
		 * Scales the body horizontally and vertically.
		 * @param scalingToApply Horizontal and vertical scaling to apply.
		 * Simply does a scalar multiplication to the scaling with the recieved
		 * scaling to apply. So if a body has a scaling of (2.0, 1.5) and this
		 * method recieves (2.0, 2.0), the body's scaling will become
		 * (4.0, 3.0).
		 * @see RedBox::Transformable::scaling
		 */
		void scale(const Vector2 &scalingToApply);

		/**
		 * Scales the body horizontally and vertically.
		 * @param xScaling Horizontal scaling to apply. Simply does a scalar
		 * multiplication to the horizontal scaling with the recieved scaling
		 * to apply. So if a body has a horizontal scaling of 2.0 and this
		 * method recieves 1.5, the body's new horizontal scaling will become
		 * 3.0.
		 * @param yScaling Vertical scaling to apply. Same thing as the
		 * xScaling parameter, but for the body's height.
		 * @see RedBox::Transformable::scaling
		 */
		void scale(float xScaling, float yScaling);

		/**
		 * Adds some scaling to the current scaling applied.
		 * @param scalingToAdd 2D vector containing the horizontal and vertical
		 * scaling to add. For example, if you pass a Vector2(0.2f, 0.0f) to a
		 * body that already has a scaling of Vector2(1.3f, 1.0f), the
		 * scaling will become Vector2(1.5f, 0.0f).
		 * @see RedBox::Transformable::scaling
		 */
		void addToScaling(const Vector2 &scalingToAdd);

		/**
		 * Adds some scaling to the body.
		 * @param xScaling Horizontal scaling to add.
		 * @param yScaling Vertical scaling to add.
		 * @see RedBox::Transformable::addToScaling(const Vector2 &scalingToAdd)
		 * @see RedBox::Transformable::scaling
		 */
		void addToScaling(float xScaling, float yScaling);

		/**
		 * Scales the body from a specific point.
		 * @param scalingToApply Horizontal and vertical scaling to apply.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::Transformable::scaling
		 * @see RedBox::Transformable::scaleFromPoint(float xScaling, float yScaling, const Vector2 &fromPoint)
		 */
		void scaleFromPoint(const Vector2 &scalingToApply,
		                    const Vector2 &fromPoint);

		/**
		 * Scales the body from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the body will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the body will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::Transformable::scaling
		 */
		virtual void scaleFromPoint(float xScaling, float yScaling,
		                            const Vector2 &fromPoint);

		/**
		 * Gets the body's horizontal scaling.
		 * @return Horizontal scaling.
		 * @see RedBox::Transformable::scaling
		 */
		float getXScaling() const;

		/**
		 * Changes the body's horizonal scaling.
		 * @param newXScaling New horizontal scaling to apply.
		 * @see RedBox::Transformable::scaling
		 */
		void setXScaling(float newXScaling);

		/**
		 * Scales the body horizontally.
		 * @param xScaling Horizontal scaling to apply. Simply does a scalar
		 * multiplication to the horizontal scaling with the recieved scaling
		 * to apply. So if a body has a horizontal scaling of 2.0 and this
		 * method recieves 1.5, the body's new horizontal scaling will become
		 * 3.0.
		 * @see RedBox::Transformable::scaling
		 */
		void scaleX(float xScaling);

		/**
		 * Scales the body horizontally from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the body will be twice as wide.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::Transformable::scaling
		 */
		void scaleXFromPoint(float xScaling, const Vector2 &fromPoint);

		/**
		 * Gets the body's vertical scaling.
		 * @return Vertical scaling.
		 * @see RedBox::Transformable::scaling
		 */
		float getYScaling() const;

		/**
		 * Changes the body's scaling.
		 * @param newYScaling New vertical scaling to apply.
		 * @see RedBox::Transformable::scaling
		 */
		void setYScaling(float newYScaling);

		/**
		 * Scales the body vertically.
		 * @param yScaling Vertical scaling to apply. Simply does a scalar
		 * multiplication to the vertical scaling with the recieved scaling
		 * to apply. So if a body has a vertical scaling of 2.0 and this
		 * method recieves 1.5, the body's new vertical scaling will become
		 * 3.0.
		 * @see RedBox::Transformable::scaling
		 */
		void scaleY(float yScaling);

		/**
		 * Scales the body vertically from a specific point.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the body will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::Transformable::scaling
		 */
		void scaleYFromPoint(float yScaling, const Vector2 &fromPoint);

		/**
		 * Gets the body's current angle.
		 * @return Current angle.
		 * @see RedBox::Transformable::angle
		 */
		float getAngle() const;

		/**
		 * Sets the body's angle. Uses the body's center as rotation's anchor
		 * point.
		 * @param newAngle New angle.
		 * @see RedBox::Transformable::angle
		 */
		void setAngle(float newAngle);

		/**
		 * Adds a value to the sprite's rotation angle.
		 * @param angleToAdd Angle to add to the sprite's current rotation
		 * angle. If the angle goes over 360 or under 0, it is automatically
		 * wrapped around.
		 * @see RedBox::Transformable::angle
		 */
		void rotate(float angleToAdd);

		/**
		 * Rotates the graphic body from a point.
		 * @param rotationAngle Angle to rotate the graphic body.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::Transformable::angle
		 */
		virtual void rotateFromPoint(float rotationAngle,
		                             const Vector2 &rotationPoint);
	private:
		/// Scaling applied on the horizontal and vertical axes.
		Vector2 scaling;

		/**
		 * Rotation applied to the body (in degrees, between -180 and 180). 0
		 * degrees is the default angle, it rotates counter-clockwise as the
		 * angle increments.
		 */
		float angle;
	};

}

#endif
