/**
 * @file
 * @ingroup Physics
 */
#ifndef RB_COLLIDABLE_H
#define RB_COLLIDABLE_H

#include <utility>
#include <list>

#include "Transformable.h"
#include "Updateable.h"
#include "FlagSet.h"
#include "Side.h"
#include "AxisAlignedBoundingBox.h"
#include "CollisionDetails.h"

namespace RedBox {
	class Collidable : virtual public Updateable, public Transformable {
	public:
		/// Value used to represent an infinite maximum velocity.
		static const float NO_MAX_VELOCITY;

		/// Flag set will all flags raised.
		static const FlagSet<Side> ALL_SIDES;

		/**
		 * Default constructor.
		 */
		Collidable();

		/**
		 * Parameterized constructor.
		 * @param newPosition Starting position.
		 * @see RedBox::Positionable::position
		 */
		explicit Collidable(const Vector2 &newPosition);

		/**
		 * Copy constructor.
		 * @param src Collidable to make a copy of.
		 */
		Collidable(const Collidable &src);

		/**
		 * Destructor.
		 */
		virtual ~Collidable();

		/**
		 * Assignment operator.
		 * @param src Collidable to make a copy of.
		 * @return Reference to the modified Collidable.
		 */
		Collidable &operator=(const Collidable &src);

		/**
		 * Updates the body.
		 */
		virtual void update();

		/**
		 * Gets the body's horizontal and vertical old position.
		 * @return 2D vector containing the last position calculated.
		 * @see RedBox::Collidable::oldPosition
		 */
		const Vector2 &getOldPosition() const;

		/**
		 * Gets the horizontal position before any movement was applied (at the
		 * start of the update).
		 * @return Last horizontal position calculated.
		 * @see RedBox::Collidable::oldPosition
		 */
		float getOldXPosition() const;

		/**
		 * Gets the vertical position before any movement was applied (at the
		 * start of the update).
		 * @return Last vertical position calculated.
		 * @see RedBox::Collidable::oldPosition
		 */
		float getOldYPosition() const;

		/**
		 * Gets the horizontal and vertical velocity.
		 * @return 2D vector containing the body's horizontal and
		 * vertical velocity.
		 * @see RedBox::Collidable::velocity
		 */
		const Vector2 &getVelocity() const;

		/**
		 * Sets the body's velocity.
		 * @param newVelocity New horizontal and vertical velocity.
		 * @see RedBox::Collidable::velocity
		 */
		void setVelocity(const Vector2 &newVelocity);

		/**
		 * Sets the body's horizontal and vertical velocity.
		 * @param newXVelocity New horizontal velocity (in pixels per second).
		 * @param newYVelocity New vertical velocity (in pixels per second).
		 * @see RedBox::Collidable::velocity
		 */
		void setVelocity(float newXVelocity, float newYVelocity);

		/**
		 * Gets the body's horizontal velocity.
		 * @return Horizontal velocity (in pixels per second).
		 * @see RedBox::Collidable::velocity
		 */
		float getXVelocity() const;

		/**
		 * Sets the horizontal velocity.
		 * @param newXVelocity New horizontal velocity (in pixels per second).
		 * @see RedBox::Collidable::velocity
		 */
		void setXVelocity(float newXVelocity);

		/**
		 * Gets the body's vertical velocity.
		 * @return Vertical velocity (in pixels per second).
		 * @see RedBox::Collidable::velocity
		 */
		float getYVelocity() const;

		/**
		 * Sets the vertical velocity.
		 * @param newYVelocity New vertical velocity (in pixels per second).
		 * @see RedBox::Collidable::velocity
		 */
		void setYVelocity(float newYVelocity);

		/**
		 * Gets the body's horizontal and vertical maximum velocity.
		 * @return 2D vector containing the horizontal and vertical maximum
		 * velocity.
		 * @see RedBox::Collidable::maximumVelocity
		 */
		const Vector2 &getMaximumVelocity() const;

		/**
		 * Sets the body's horizontal and vertical maximum velocity.
		 * @param newMaximumVelocity 2D vector containing the horizontal and
		 * vertical maximum velocity. Maximum velocity should always be
		 * positive, except for infinite maximum velocity, in which case it
		 * would be -1.0f.
		 * @see RedBox::Collidable::maximumVelocity
		 */
		void setMaximumVelocity(const Vector2 &newMaximumVelocity);

		/**
		 * Sets the body's horizontal and vertical maximum velocity.
		 * @param newMaximumXVelocity New horizontal maximum velocity.
		 * @param newMaximumYVelocity New vertical maximum velocity.
		 * @see RedBox::Collidable::setMaximumVelocity(const Vector2& newMaximumVelocity)
		 * @see RedBox::Collidable::maximumVelocity
		 */
		void setMaximumVelocity(float newMaximumXVelocity,
		                        float newMaximumYVelocity);

		/**
		 * Gets the body's horizontal maximum velocity.
		 * @return Horinzontal maximum velocity.
		 * @see RedBox::Collidable::maximumVelocity
		 */
		float getMaximumXVelocity() const;

		/**
		 * Sets the body's horizontal maximum velocity.
		 * @param newMaximumXVelocity New maximum horizontal velocity. Negative
		 * value for no maximum velocity.
		 * @see RedBox::Collidable::maximumVelocity
		 */
		void setMaximumXVelocity(float newMaximumXVelocity);

		/**
		 * Gets the body's vertical maximum velocity.
		 * @return Horinzontal maximum velocity.
		 * @see RedBox::Collidable::maximumVelocity
		 */
		float getMaximumYVelocity() const;

		/**
		 * Sets the body's vertical maximum velocity.
		 * @param newMaximumYVelocity New vertical maximum velocity. Negative
		 * value for no maximum velocity.
		 * @see RedBox::Collidable::maximumVelocity
		 */
		void setMaximumYVelocity(float newMaximumYVelocity);

		/**
		 * Gets the body's horizontal and vertical acceleration.
		 * @return 2D vector containing the body's horizontal and
		 * vertical acceleration.
		 * @see RedBox::Collidable::acceleration
		 */
		const Vector2 &getAcceleration() const;

		/**
		 * Sets the body's horizontal and vertical acceleration.
		 * @param newAcceleration New horizontal and vertical acceleration.
		 * @see RedBox::Collidable::setAcceleration(float newXAcceleration,
		 * float newYAcceleration)
		 * @see RedBox::Collidable::acceleration
		 */
		void setAcceleration(const Vector2 &newAcceleration);

		/**
		 * Sets the body's horizontal and vertical acceleration.
		 * @param newXAcceleration New horizontal acceleration.
		 * @param newYAcceleration New vertical acceleration.
		 * @see RedBox::Collidable::setAcceleration(const Vector2&
		 * newAcceleration)
		 * @see RedBox::Collidable::acceleration
		 */
		void setAcceleration(float newXAcceleration, float newYAcceleration);

		/**
		 * Gets the body's horizontal acceleration.
		 * @return Horizontal acceleration.
		 * @see RedBox::Collidable::acceleration
		 */
		float getXAcceleration() const;

		/**
		 * Sets the body's horizontal acceleration.
		 * @param newXAcceleration New horizontal acceleration.
		 * @see RedBox::Collidable::acceleration
		 */
		void setXAcceleration(float newXAcceleration);

		/**
		 * Gets the body's vertical acceleration.
		 * @return Vertical acceleration.
		 * @see RedBox::Collidable::acceleration
		 */
		float getYAcceleration() const;

		/**
		 * Sets the body's vertical acceleration.
		 * @param newYAcceleration New vertical acceleration.
		 * @see RedBox::Collidable::acceleration
		 */
		void setYAcceleration(float newYAcceleration);

		/**
		 * Gets the drag applied on the velocity's direction when there is no
		 * acceleration.
		 * @return Current global drag.
		 * @see RedBox::Collidable::globalDrag
		 */
		float getGlobalDrag() const;

		/**
		 * Sets the drag applied on the velocity's direction when there is no
		 * acceleration.
		 * @param newGlobalDrag New global drag to set.
		 * @see RedBox::Collidable::globalDrag
		 */
		void setGlobalDrag(float newGlobalDrag);

		/**
		 * Gets the horizontal drag applied on the horizontal velocity when
		 * there is no horizontal acceleration (there could be a vertical
		 * acceleration while the horizontal drag is being applied).
		 * @return Current horizontal drag.
		 */
		float getHorizontalDrag() const;

		/**
		 * Sets the horizontal drag applied on the horizontal velocity when
		 * there is no horizontal acceleration (there could be a vertical
		 * acceleration while the horizontal drag is being applied).
		 * @param newHorizontalDrag New horizontal drag.
		 */
		void setHorizontalDrag(float newHorizontalDrag);

		/**
		 * Gets the vertical drag applied on the vertical velocity when there is
		 * vertical acceleration (there could be a horizontal acceleration while
		 * the vertical drag is being applied).
		 * @return Current vertical drag.
		 */
		float getVerticalDrag() const;

		/**
		 * Sets the vertical drag applied on the vertical velocity when there is
		 * no vertical acceleration (there could be a horizontal acceleration
		 * while the vertical drag is being applied).
		 * @param newVerticalDrag New vertical drag.
		 */
		void setVerticalDrag(float newVerticalDrag);

		/**
		 * Gets the flag set of collidable sides. Used to get which side of the
		 * body should collide and which should not.
		 * @return Flag set of which sides are collidable.
		 * @see RedBox::Collidable::collidableSides
		 */
		FlagSet<Side>& getCollidableSides();

		/**
		 * Gets the body's elasticity factor. Elasticity determines how it
		 * bounces when colliding.
		 * @return Current elasticity.
		 * @see RedBox::Collidable::elasticity
		 */
		float getElasticity() const;

		/**
		 * Sets the body's elasticity factor. Elasticity determines how it
		 * bounces when colliding.
		 * @param newElasticity New elasticity.
		 * @see RedBox::Collidable::elasticity
		 */
		void setElasticity(float newElasticity);

		/**
		 * Checks if the body is static or not.
		 * @return True if the body is static, false if not.
		 * @see RedBox::Collidable::staticBody
		 */
		bool isStaticBody() const;

		/**
		 * Set if the body is static or not. A static body won't react to
		 * collisions (used for walls, floors, moving platforms, etc.)
		 * @param newStaticBody True if the body is to be static, false if not.
		 * @see RedBox::Collidable::staticBody
		 */
		void setStaticBody(bool newStaticBody);

		/**
		 * Gets the body's colliding box's offset.
		 * @return 2D Vector containing the horizontal and vertical offset.
		 * @see RedBox::Collidable::offset
		 */
		const Vector2 &getOffset() const;

		/**
		 * Sets the body's colliding box's offset.
		 * @param newOffset New offset to add to the position when detecting
		 * collisions.
		 * @see RedBox::Collidable::offset
		 */
		void setOffset(const Vector2 &newOffset);

		/**
		 * Sets the body's colliding box's horizontal and vertical offset.
		 * @param newXOffset New horizontal offset to add to the position when
		 * detecting collisions.
		 * @param newYOffset New vertical offset to add to the position when
		 * detecting collisions.
		 * @see RedBox::Collidable::offset
		 */
		void setOffset(float newXOffset, float newYOffset);

		/**
		 * Gets the body's colliding box's horizontal offset.
		 * @return Current horizontal offset.
		 * @see RedBox::Collidable::offset
		 */
		float getXOffset() const;

		/**
		 * Sets the body's colliding box's horizontal offset.
		 * @param newXOffset New vertical offset to add to the position when
		 * detecting collisions.
		 * @see RedBox::Collidable::offset
		 */
		void setXOffset(float newXOffset);

		/**
		 * Gets the body's colliding box's vertical offset.
		 * @return Current vertical offset.
		 * @see RedBox::Collidable::offset
		 */
		float getYOffset() const;

		/**
		 * Sets the body's colliding box's horizontal offset.
		 * @param newYOffset New vertical offset to add to the position when
		 * detecting collisions.
		 * @see RedBox::Collidable::offset
		 */
		void setYOffset(float newYOffset);

		/**
		 * Gets the horizontal and vertical colliding box ratios.
		 * @return 2D vector containing the horizontal and vertical colliding
		 * box ratios.
		 * @see RedBox::Collidable::collidingBoxRatio;
		 */
		const Vector2 &getCollidingBoxRatio() const;

		/**
		 * Sets the horizontal and vertical colliding box ratios.
		 * @param newCollidingBoxRatio 2D vector containing the horizontal and
		 * vertical colliding box ratios.
		 * @see RedBox::Collidable::collidingBoxRatio
		 */
		void setCollidingBoxRatio(const Vector2 &newCollidingBoxRatio);

		/**
		 * Sets the horizontal and vertical colliding box ratios.
		 * @param newXCollidingBoxRatio New horizontal colliding box ratio.
		 * @param newYCollidingBoxRatio New vertical colliding box ratio.
		 * @see RedBox::Collidable::collidingBoxRatio
		 */
		void setCollidingBoxRatio(float newXCollidingBoxRatio,
		                          float newYCollidingBoxRatio);

		/**
		 * Gets the horizontal colliding box ratios.
		 * @return 2D vector containing the horizontal colliding box ratio.
		 * @see RedBox::Collidable::collidingBoxRatio;
		 */
		float getXCollidingBoxRatio() const;

		/**
		 * Sets the horizontal colliding box ratios.
		 * @param newXCollidingBoxRatio New horizontal colliding box ratio.
		 * @see RedBox::Collidable::collidingBoxRatio
		 */
		void setXCollidingBoxRatio(float newXCollidingBoxRatio);

		/**
		 * Gets the vertical colliding box ratios.
		 * @return 2D vector containing the vertical colliding box ratio.
		 * @see RedBox::Collidable::collidingBoxRatio;
		 */
		float getYCollidingBoxRatio() const;

		/**
		 * Sets the vertical colliding box ratios.
		 * @param newYCollidingBoxRatio New vertical colliding box ratio.
		 * @see RedBox::Collidable::collidingBoxRatio
		 */
		void setYCollidingBoxRatio(float newYCollidingBoxRatio);

		/**
		 * Gets the collidable's size taking into account the colliding box
		 * ratio.
		 * @return Vector2 containing the size with the colliding box ratio
		 * applied.
		 */
		const Vector2 getCollidingSize() const;

		/**
		 * Gets the collidable's width taking into account the colliding box
		 * ratio.
		 * @return Vector2 containing the width with the colliding box ratio
		 * applied.
		 */
		float getCollidingWidth() const;

		/**
		 * Gets the collidable's height taking into account the colliding box
		 * ratio.
		 * @return Vector2 containing the height with the colliding box ratio
		 * applied.
		 */
		float getCollidingHeight() const;

		/**
		 * Checks whether or not the offset is a ratio or is in pixels.
		 * @return True if the offset is a ratio or if it is in pixels.
		 * @see RedBox::Collidable::offsetRatio
		 */
		bool isOffsetRatio() const;

		/**
		 * Sets whether or not the offset is a ratio or is in pixels.
		 * @param newOffsetRatio Set it to true for the offset to be a ratio or
		 * false for it to be in pixels.
		 * @see RedBox::Collidable::offsetRatio
		 */
		void setOffsetRatio(bool newOffsetRatio);

		/**
		 * Gets the axis-aligned bounding box for the collidable.
		 * @return Axis-aligned bounding box for the collidable. Takes into
		 * account its offset and colliding box ratio.
		 */
		const AxisAlignedBoundingBox getAxisAlignedBoundingBox() const;

		/**
		 * Collides two collidables against each other. It tests if they are
		 * colliding and returns a pair containing the collision information.
		 * Applies the elasticity, takes into account if the bodies are static,
		 * etc.
		 * @param other Pointer to the body you want to collide with. Must not
		 * be a pointer to the instance (the functions tests it and ignores
		 * it if needed.).
		 * @return Pair whose first value is a boolean (true if the bodies are
		 * colliding, false if not) and the second value is a structure
		 * containing collision information.
		 * @see RedBox::CollisionDetails
		 */
		std::pair<bool, CollisionDetails> collide(Collidable *other);

		/**
		 * Collides the instance with a list of collidables in the order they
		 * are given. It tests if they are colliding and applies the elasticity,
		 * takes into account if the bodies are static, etc.
		 * @param others List containing pointers to the collidables to collide
		 * with the instance. Pointers to the instance are ignored.
		 * @return Pair whose first value is a boolean (true if the instance
		 * collides with at least one of the list's bodies) and its second
		 * value is a list of structures containing collision information.
		 * @see RedBox::CollisionDetails
		 * @see RedBox::Collidable(Collidable *other)
		 */
		std::pair<bool, std::list<std::pair<bool, CollisionDetails> > > collide(const std::list<Collidable *> &others);

		/**
		 * Collides the collidable with a horizontal line. The line acts as a
		 * static body. If the lower boundary given is higher than the higher
		 * boundary, they will be swapped.
		 * @param yPosition Vertical position of the horizontal line to check
		 * overlapping with.
		 * @param lowerXBoundary Lower horizontal boundary of the line.
		 * @param higherXBoundary Higher horizontal boundary of the line.
		 * @return True if the bounding box overlaps with the horizontal line,
		 * false if not.
		 */
		bool collideHorizonalLine(float yPosition, float lowerXBoundary,
		                          float higherXBoundary);

		/**
		 * Collides the collidable with a horizontal line. The line acts as a
		 * static body.
		 * @param yPosition Vertical position of the horizontal line to check
		 * overlapping with.
		 * @return True if the bounding box overlaps with the horizontal line,
		 * false if not.
		 */
		bool collideHorizonalLine(float yPosition);

		/**
		 * Collides the collidable with a vertical line. The line acts as a
		 * static body. If the lower boundary given is higher than the higher
		 * boundary, they will be swapped.
		 * @param xPosition Horizontal position of the horizontal line to check
		 * overlapping with.
		 * @param lowerYBoundary Lower vertical boundary of the line.
		 * @param higherYBoundary Higher vertical boundary of the line.
		 * @return True if the bounding box overlaps with the vertical line,
		 * false if not.
		 */
		bool collideVerticalLine(float xPosition, float lowerYBoundary,
		                         float higherYBoundary);

		/**
		 * Collides the collidable with a vertical line. The line acts as a
		 * static body.
		 * @param xPosition Horizontal position of the horizontal line to check
		 * overlapping with.
		 * @return True if the bounding box overlaps with the vertical line,
		 * false if not.
		 */
		bool collideVerticalLine(float xPosition);

		/**
		 * Collides collidables from two lists. It tests all possible collision
		 * detections between the two lists, so if the two lists contain 4
		 * collidables, this function will test 16 collisions. If the same
		 * collidable is in the two lists, its collision detection is ignored.
		 * @param collidables1 First list containing pointers to the collidables
		 * to have their collisions checked.
		 * @param collidables2 Second list containing pointers to the
		 * collidables to have their collisions checked.
		 * @return Pair whose first value is a boolean (true if at least one
		 * collision is detected and applied, false if not) and its second value
		 * is a list of structures containing the collision information for all
		 * collisions tested.
		 */
		static std::pair<bool, std::list<std::pair<bool, CollisionDetails> > > collide(const std::list<Collidable *> &collidables1,
		                                                             const std::list<Collidable *> &collidables2);
	private:
		/**
		 * Makes sure the given velocity isn't over the maximum velocity. Only
		 * applies the maximumVelocity if it is over 0.
		 * @param velocity Velocity to check.
		 * @param maximumVelocity Maximum velocity to apply on the velocity.
		 */
		static float checkMaximumVelocity(float *velocity, float maximumVelocity);

		/**
		 * Makes sure the given velocity isn't over the maximum velocity. Only
		 * applies the maximumVelocity if it is over 0.
		 * @param velocity Velocity to check.
		 * @param maximumVelocity Maximum velocity to apply on the velocity.
		 */
		static float checkMaximumVelocity(float velocity, float maximumVelocity);

		/// Position at which the body was at the last update.
		Vector2 oldPosition;

		/// Velocity vector. Contains the body's horizontal and vertical speed.
		Vector2 velocity;

		/**
		 * Maximum horizontal and vertical velocity. Negative values for no
		 * maximum velocity.
		 */
		Vector2 maximumVelocity;

		/**
		 * Horizontal and vertical acceleration. Values are in pixels/sec^2.
		 */
		Vector2 acceleration;

		/**
		 * Deceleration applied when there is neither a horizontal nor a
		 * vertical accleration until velocity reaches 0.
		 */
		float globalDrag;

		/**
		 * Horizontal deceleration applied when there is no horizontal
		 * acceleration until horizontal velocity reaches 0. So there could be
		 * a vertical acceleration while the horizontal drag is being applied.
		 */
		float horizontalDrag;

		/**
		 * Vertical deceleration applied when there is no vertical acceleration
		 * until vertical velocity reaches 0. So there could be a horizontal
		 * acceleration while the vertical drag is being applied.
		 */
		float verticalDrag;

		/**
		 * Contain "Side" flag (see Side.h). It tells which side can collide. A
		 * side that can't collide will let a collidable pass through.
		 */
		FlagSet<Side> collidableSides;

		/**
		 * Elasticity factor of the collidable, will determine how it should
		 * bounce in a collision. Default value is 0 (Solid object). 0.0f means
		 * the collidable will not rebound at all when a collision is detected
		 * with another static body. The body must be non-static for its
		 * elasticity to be applied. 1.0f would mean perfect rebound. So if you
		 * set an elasticity of 1.0f to an object falling to the ground, it will
		 * rebound at the same height infinitely.
		 */
		float elasticity;

		/**
		 * This body won't react to collision if this boolean is set to true.
		 * It will collide, but it won't be moved or affected by the collision.
		 */
		bool staticBody;

		/// 2D vector added to the position when detecting collisions.
		Vector2 offset;

		/**
		 * Size of the colliding box compared to the body's actual size. To make
		 * the colliding box half the body's size, this vector would be set at
		 * (0.5f, 0.5f).
		 */
		Vector2 collidingBoxRatio;

		/**
		 * True if the offset is a proportion of the collidable's size, false if
		 * it is in pixels.
		 */
		bool offsetRatio;

		/**
		 * Makes sure the velocity is within the maximum velocity's bounds.
		 */
		void checkMaximumVelocity();

		/**
		 * Solves the collision on the horizontal axis. Separates the bodies and
		 * returns information about the collision.
		 * @param other Pointer to the second collidable that you want to
		 * check collisions with.
		 * @param collisionDetails Pointer to the structure containing information
		 * about the collision.
		 * @return True if a collision happened, false if not.
		 * @see RedBox::CollisionDetails
		 */
		bool solveXCollision(Collidable *other, CollisionDetails *collisionDetails);

		/**
		 * Solves the collision on the vertical axis. Separates the bodies and
		 * returns information about the collision.
		 * @param other Pointer to the second collidable that you want to
		 * check collisions with.
		 * @param collisionDetails Pointer to the structure containing information
		 * about the collision.
		 * @return True if a collision happened, false if not.
		 * @see RedBox::CollisionDetails
		 */
		bool solveYCollision(Collidable *other, CollisionDetails *collisionDetails);
	};

}

#endif
