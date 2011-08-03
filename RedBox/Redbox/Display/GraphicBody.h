/**
 * @file
 * @ingroup Display
 */
#ifndef RB_GraphicBody_H
#define RB_GraphicBody_H

#include <list>

#include "Body.h"
#include "Vec2.h"
#include "Side.h"
#include "FlagSet.h"
#include "CollisionData.h"
#include "Layer.h"
#include "AABB.h"

namespace RedBox {
	/**
	 * Represents a GraphicBody object assiociated with its layer. This is the
	 * type that the state contains. Classes like GraphicString, Sprite and
	 * IEmitter are derived from this class. To use a graphic body, you have
	 * to initialize it and then add it to a state. The state will take care of
	 * its destruction when needed. The same graphic body cannot be in two
	 * different states. If you want to remove a graphic body from a state, you
	 * call setToBeDeleted(true) on the graphic body.
	 * @ingroup Display
	 * @see RedBox::State
	 */
	class GraphicBody : public Body {
		friend class State;
	public:
		/// Value used to represent an infinite maximum velocity.
		static const float NO_MAX_VELOCITY = -1.0f;

		static const FlagSet<Side> ALL_SIDES;

		/**
		 * The default constructor.
		 */
		GraphicBody(const Vec2& newPosition = Vec2());

		/**
		 * The copy constructor.
		 * @param src The GraphicBody to make a copy of.
		 */
		GraphicBody(const GraphicBody& src);

		/**
		 * The destructor.
		 */
		virtual ~GraphicBody();

		/**
		 * The assignment operator overload.
		 * @param src The GraphicBody to make a copy of.
		 * @return Reference to the modified graphic body.
		 */
		GraphicBody& operator=(const GraphicBody& src);

		/**
		 * Updates the GraphicBody.
		 */
		virtual void update();

		/**
		 * Renders the GraphicBody.
		 */
		virtual void render() = 0;

		/**
		 * Gets the graphic body's current layer.
		 * @return Current layer.
		 * @see RedBox::GraphicBody::layer
		 */
		const Layer& getLayer() const;

		/**
		 * Sets the graphic body's current layer.
		 * @param newLayer New layer.
		 * @see RedBox::GraphicBody::layer
		 */
		void setLayer(const Layer& newLayer);

		/**
		 * Gets the graphic body's z coordinate.
		 * @return Z coordinate. The higher the value the closer the graphic
		 * body will be.
		 * @see RedBox::GraphicBody::layer
		 * @see RedBox::Layer::z
		 */
		int getZ() const;

		/**
		 * Sets the graphic body's coordinate.
		 * @param newZ New z coordinate. The higher the value closer the graphic
		 * body will be.
		 * @see RedBox::GraphicBody::layer
		 * @see RedBox::Layer::z
		 */
		void setZ(int newZ);

		/**
		 * Gets the graphic body's scroll factor.
		 * @return Horizontal and vertical scroll factor. A value higher than 1
		 * means the graphic body will move faster as if it were closer to the
		 * camera, between 1 and 0 means it will move as if it were far from the
		 * camera.
		 * @see RedBox::GraphicBody::layer
		 * @see RedBox::Layer::scrollFactor
		 */
		const Vec2& getScrollFactor() const;

		/**
		 * Sets the graphic body's scroll factor.
		 * @param newScrollFactor New horizontal and vertical scroll factor. A
		 * value higher than 1 means the graphic body will move faster as if it
		 * were closer to the camera and between 1 and 0 means it will move as
		 * if it were far from the camera.
		 * @see RedBox::GraphicBody::layer
		 * @see RedBox::Layer::scrollFactor
		 */
		void setScrollFactor(const Vec2& newScrollFactor);

		/**
		 * Sets the graphic body's scroll factor.
		 * @param newXScrollFactor New horizontal scroll factor. A value higher
		 * than 1 means the graphic body will move faster as if it were closer
		 * to the camera and between 1 and 0 means it will move as if it were
		 * far from the camera.
		 * @param newYScrollFactor New vertical scroll factor. A value higher
		 * than 1 means the graphic body will move faster as if it were closer
		 * to the camera and between 1 and 0 means it will move as if it were
		 * far from the camera.
		 * @see RedBox::GraphicBody::layer
		 * @see RedBox::Layer::scrollFactor
		 */
		void setScrollFactor(float newXScrollFactor, float newYScrollFactor);

		/**
		 * Gets the graphic body's horizontal scroll factor.
		 * @return Horizontal scroll factor. A value higher than 1 means the
		 * graphic body will move faster as if it were closer to the camera,
		 * between 1 and 0 means it will move as if it were far from the camera.
		 * @see RedBox::GraphicBody::layer
		 * @see RedBox::Layer::scrollFactor
		 */
		float getXScrollFactor() const;

		/**
		 * Sets the graphic body's horizontal scroll factor.
		 * @param newXScrollFactor New horizontal scroll factor. A value higher
		 * than 1 means the graphic body will move faster as if it were closer
		 * to the camera and between 1 and 0 means it will move as if it were
		 * far from the camera.
		 * @see RedBox::GraphicBody::layer
		 * @see RedBox::Layer::scrollFactor
		 */
		void setXScrollFactor(float newXScrollFactor);

		/**
		 * Gets the graphic body's vertical scroll factor.
		 * @return Vertical scroll factor. A value higher than 1 means the
		 * graphic body will move faster as if it were closer to the camera,
		 * between 1 and 0 means it will move as if it were far from the camera.
		 * @see RedBox::GraphicBody::layer
		 * @see RedBox::Layer::scrollFactor
		 */
		float getYScrollFactor() const;

		/**
		 * Sets the graphic body's vertical scroll factor.
		 * @param newYScrollFactor New vertical scroll factor. A value higher
		 * than 1 means the graphic body will move faster as if it were closer
		 * to the camera and between 1 and 0 means it will move as if it were
		 * far from the camera.
		 * @see RedBox::GraphicBody::layer
		 * @see RedBox::Layer::scrollFactor
		 */
		void setYScrollFactor(float newYScrollFactor);

		/**
		 * Checks if the GraphicBody needs to be deleted.
		 * @return True if the GraphicBody needs to be deleted, false if not.
		 * @see RedBox::GraphicBody::toBeDeleted
		 */
		bool isToBeDeleted() const;

		/**
		 * Sets the GraphicBody to be deleted or not.
		 * @param newToBeDeleted New value to be deleted.
		 * @see RedBox::GraphicBody::toBeDeleted
		 */
		void setToBeDeleted(bool newToBeDeleted);

		/**
		 * Checks if the layer has recently been changed and not yet updated.
		 * @return True if the layer has recently been changed, false if not.
		 * @see RedBox::GraphicBody::layerChanged
		 */
		bool isLayerChanged() const;

		/**
		 * Gets the horizontal and vertical velocity.
		 * @return 2D vector containing the graphic body's horizontal and
		 * vertical velocity.
		 * @see RedBox::GraphicBody::velocity
		 */
		const Vec2& getVelocity() const;

		/**
		 * Sets the graphic body's velocity.
		 * @param newVelocity New horizontal and vertical velocity.
		 * @see RedBox::GraphicBody::velocity
		 */
		void setVelocity(const Vec2& newVelocity);

		/**
		 * Sets the graphic body's horizontal and vertical velocity.
		 * @param newXVelocity New horizontal velocity (in pixels per second).
		 * @param newYVelocity New vertical velocity (in pixels per second).
		 * @see RedBox::GraphicBody::velocity
		 */
		void setVelocity(float newXVelocity, float newYVelocity);

		/**
		 * Gets the graphic body's horizontal velocity.
		 * @return Horizontal velocity (in pixels per second).
		 * @see RedBox::GraphicBody::velocity
		 */
		float getXVelocity() const;

		/**
		 * Sets the horizontal velocity.
		 * @param newXVelocity New horizontal velocity (in pixels per second).
		 * @see RedBox::GraphicBody::velocity
		 */
		void setXVelocity(float newXVelocity);

		/**
		 * Gets the graphic body's vertical velocity.
		 * @return Vertical velocity (in pixels per second).
		 * @see RedBox::GraphicBody::velocity
		 */
		float getYVelocity() const;

		/**
		 * Sets the vertical velocity.
		 * @param newYVelocity New vertical velocity (in pixels per second).
		 * @see RedBox::GraphicBody::velocity
		 */
		void setYVelocity(float newYVelocity);

		/**
		 * Gets the graphic body's horizontal and vertical acceleration.
		 * @return 2D vector containing the graphic body's horizontal and
		 * vertical acceleration.
		 * @see RedBox::GraphicBody::acceleration
		 */
		const Vec2& getAcceleration() const;

		/**
		 * Sets the graphic body's horizontal and vertical acceleration.
		 * @param newAcceleration New horizontal and vertical acceleration.
		 * @see RedBox::GraphicBody::setAcceleration(float newXAcceleration,
		 * float newYAcceleration)
		 * @see RedBox::GraphicBody::acceleration
		 */
		void setAcceleration(const Vec2& newAcceleration);

		/**
		 * Sets the graphic body's horizontal and vertical acceleration.
		 * @param newXAcceleration New horizontal acceleration.
		 * @param newYAcceleration New vertical acceleration.
		 * @see RedBox::GraphicBody::setAcceleration(const Vec2&
		 * newAcceleration)
		 * @see RedBox::GraphicBody::acceleration
		 */
		void setAcceleration(float newXAcceleration, float newYAcceleration);

		/**
		 * Gets the graphic body's horizontal acceleration.
		 * @return Horizontal acceleration.
		 * @see RedBox::GraphicBody::acceleration
		 */
		float getXAcceleration() const;

		/**
		 * Sets the graphic body's horizontal acceleration.
		 * @param newXAcceleration New horizontal acceleration.
		 * @see RedBox::GraphicBody::acceleration
		 */
		void setXAcceleration(float newXAcceleration);

		/**
		 * Gets the graphic body's vertical acceleration.
		 * @return Vertical acceleration.
		 * @see RedBox::GraphicBody::acceleration
		 */
		float getYAcceleration() const;

		/**
		 * Sets the graphic body's vertical acceleration.
		 * @param newYAcceleration New vertical acceleration.
		 * @see RedBox::GraphicBody::acceleration
		 */
		void setYAcceleration(float newYAcceleration);

		/**
		 * Gets the graphic body's horizontal and vertical position.
		 * @return 2D vector containing the horizontal and vertical position.
		 * @see RedBox::GraphicBody::position
		 */
		const Vec2& getPosition() const;

		/**
		 * Sets the GraphicBody's horizontal and vertical position.
		 * @param newPosition New horizontal and vertical position.
		 * @see GraphicBody::setPosition(float x, float y)
		 * @see RedBox::GraphicBody::position
		 */
		void setPosition(const Vec2& newPosition);

		/**
		 * Sets the GraphicBody's horizontal and vertical position.
		 * @param newXPosition New horizontal position (in pixels). Lower value
		 * means more to the left.
		 * @param newYPosition New vertical position (in pixels). Lower value
		 * means more at the top.
		 * @see RedBox::GraphicBody::position
		 */
		virtual void setPosition(float newXPosition, float newYPosition);

		/**
		 * Moves the GraphicBody horizontally and vertically.
		 * @param delta 2D vector to add to the GraphicBody's position (in
		 * pixels).
		 * @see RedBox::GraphicBody::move(float deltaX, float deltaY)
		 * @see RedBox::GraphicBody::position
		 */
		void move(const Vec2& delta);

		/**
		 * Moves the GraphicBody horizontally and vertically.
		 * @param deltaX Value to add to the GraphicBody's horizontal position
		 * (in pixels). Positive value moves the GraphicBody to the right and a
		 * negative value moves the GraphicBody to the left.
		 * @param deltaY Value to add to the GraphicBody's vertical position (in
		 * pixels). Positive value moves the GraphicBody down and a negative
		 * value moves the GraphicBody up.
		 * @see RedBox::GraphicBody::move(const Vec2& delta);
		 * @see RedBox::GraphicBody::position
		 */
		void move(float deltaX, float deltaY);

		/**
		 * Gets the GraphicBody's horizontal position.
		 * @return Horizontal position (in pixels). Lower value means more to
		 * the left.
		 * @see RedBox::GraphicBody::position
		 */
		float getXPosition() const;

		/**
		 * Sets the GraphicBody's horizontal position.
		 * @param newXPosition New horizontal position (in pixels). Lower value
		 * means more to the left.
		 * @see RedBox::GraphicBody::position
		 */
		void setXPosition(float newXPosition);

		/**
		 * Moves the graphic body horizontally.
		 * @param deltaX Value to add to the GraphicBody's horizontal position
		 * (in pixels). Positive value moves the GraphicBody to the right and a
		 * negative value moves the GraphicBody to the left.
		 * @see RedBox::GraphicBody::position
		 */
		void moveX(float deltaX);

		/**
		 * Gets the graphic body's vertical position.
		 * @return Vertical position (in pixels). Lower value means more at the
		 * top.
		 * @see RedBox::GraphicBody::position
		 */
		float getYPosition() const;

		/**
		 * Sets the graphic body's horizontal position.
		 * @param newYPosition New vertical position (in pixels). Lower value
		 * means more at the top.
		 * @see RedBox::GraphicBody::position
		 */
		void setYPosition(float newYPosition);

		/**
		 * Moves the GraphicBody vertically.
		 * @param deltaY Value to add to the GraphicBody's vertical position (in
		 * pixels). Positive value moves the GraphicBody down and a negative
		 * value moves the graphic body up.
		 * @see RedBox::GraphicBody::position
		 */
		void moveY(float deltaY);

		/**
		 * Gets the graphic body's horizontal and vertical old position.
		 * @return 2D vector containing the last position calculated.
		 * @see RedBox::GraphicBody::oldPosition
		 */
		const Vec2& getOldPosition() const;

		/**
		 * Gets the horizontal position before any movement was applied (at the
		 * start of the update).
		 * @return Last horizontal position calculated.
		 * @see RedBox::GraphicBody::oldPosition
		 */
		float getOldXPosition() const;

		/**
		 * Gets the vertical position before any movement was applied (at the
		 * start of the update).
		 * @return Last vertical position calculated.
		 * @see RedBox::GraphicBody::oldPosition
		 */
		float getOldYPosition() const;

		/**
		 * Gets the graphic body's horizontal and vertical maximum velocity.
		 * @return 2D vector containing the horizontal and vertical maximum
		 * velocity.
		 * @see RedBox::GraphicBody::maxVelocity
		 */
		const Vec2& getMaxVelocity() const;

		/**
		 * Sets the graphic body's horizontal and vertical maximum velocity.
		 * @param newMaxVelocity 2D vector containing the horizontal and
		 * vertical maximum velocity. Maximum velocity should always be
		 * positive, except for infinite maximum velocity, in which case it
		 * would be -1.0f.
		 * @see RedBox::GraphicBody::maxVelocity
		 */
		void setMaxVelocity(const Vec2& newMaxVelocity);

		/**
		 * Sets the graphic body's horizontal and vertical maximum velocity.
		 * @param newMaxXVelocity New horizontal maximum velocity.
		 * @param newMaxYVelocity New vertical maximum velocity.
		 * @see RedBox::GraphicBody::setMaxVelocity(const Vec2& newMaxVelocity)
		 * @see RedBox::GraphicBody::maxVelocity
		 */
		void setMaxVelocity(float newMaxXVelocity, float newMaxYVelocity);

		/**
		 * Gets the graphic body's horizontal maximum velocity.
		 * @return Horinzontal maximum velocity.
		 * @see RedBox::GraphicBody::maxVelocity
		 */
		float getMaxXVelocity() const;

		/**
		 * Sets the graphic body's horizontal maximum velocity.
		 * @param newMaxXVelocity New maximum horizontal velocity. -1.0f for no
		 * maximum velocity.
		 * @see RedBox::GraphicBody::maxVelocity
		 */
		void setMaxXVelocity(float newMaxXVelocity);

		/**
		 * Gets the graphic body's vertical maximum velocity.
		 * @return Horinzontal maximum velocity.
		 * @see RedBox::GraphicBody::maxVelocity
		 */
		float getMaxYVelocity() const;

		/**
		 * Sets the graphic body's vertical maximum velocity.
		 * @param newMaxYVelocity New vertical maximum velocity. -1.0f for no
		 * maximum velocity.
		 * @see RedBox::GraphicBody::maxVelocity
		 */
		void setMaxYVelocity(float newMaxYVelocity);

		/**
		 * Gets the graphic body's width.
		 * @return Width in pixels (by default).
		 */
		virtual float getWidth() const = 0;

		/**
		 * Gets the graphic body's height.
		 * @return Height in pixels (by default).
		 */
		virtual float getHeight() const = 0;

		/**
		 * Getter for the collidableSides flag.
		 * Used to get which side of a sprite should collide and which should
		 * not.
		 * @return Possible return flag : LEFT | RIGHT | TOP | BOTTOM
		 * @see RedBox::GraphicBody::collidableSides
		 */
		FlagSet<Side>& getCollidableSides();

		/**
		 * Checks if the graphic body is static or not.
		 * @return True if the graphic body is static, false if not.
		 * @see RedBox::GraphicBody::staticBody
		 */
		bool isStaticBody() const;

		/**
		 * Set if the GraphicBody is a static one. A static object won't react
		 * to collisions. (wall, floor, moving platform, etc.)
		 * @param newStaticBody True if the body is to be static, false if not.
		 * @see RedBox::GraphicBody::staticBody
		 */
		void setStaticBody(bool newStaticBody);

		/**
		 * Return the elasticity factor of the GraphicBody. Elasticity will
		 * determine how should it bounce in a collision.
		 * @return Current elasticity.
		 * @see RedBox::GraphicBody::elasticity
		 */
		float getElasticity() const;

		/**
		 * Set the elasticity factor of the GraphicBody. Elasticity will
		 * determine how should it bounce in a collision.
		 * @param newElasticity New elasticity.
		 * @see RedBox::GraphicBody::elasticity
		 */
		void setElasticity(float newElasticity);

		/**
		 * Use this function to collide the current GraphicBody against another
		 * one. It will test if they are colliding, and return a pair containing
		 * collision information.
		 * @param other A GraphicBody object against which you want to collide
		 * the current object.
		 * @return This function return a pair, the first value is a boolean
		 * (true if the objects are colliding), the second value is a structure
		 * containing information about the collision.
		 * @see RedBox::CollisionData
		 */
		std::pair<bool, CollisionData> collide(GraphicBody* other);

		/**
		 * Use this function to collide the current GraphicBody against a list
		 * of other graphic bodies. It will test if they are colliding, and
		 * return a pair containing collision information.
		 * @param graphicBodies A list of GraphicBody objects against which you
		 * want to collide the current object.
		 * @return This function return a pair, the first value is a boolean
		 * (true if the objects are colliding), the second value is a list of
		 * structure containing information about the collision.
		 * @see RedBox::CollisionData
		 */
		std::pair<bool, std::list<CollisionData> > collide(std::list<GraphicBody*> graphicBodies);

		/**
		 * Collide the current GraphicBody against the given horizontal line.
		 * The line must be a flat line parallel to the X axis (cutting the Y
		 * axis at position indicated by linePosition.
		 * @param linePosition Position of the line on the Y axis. (If the line
		 * has no boundaries, it will cut the Y axis at this position.
		 * @param lowerXBoundary Lower boundary of the line (a AABB with a maxX
		 * lower than this value won't collide with the line). If the value is
		 * higher than higherXBoundary, the line is infinite.
		 * @param higherXBoundary Higher boundary of the line (a AABB with a
		 * minX higher than this value won't collide with the line). If the
		 * value is lower than lowerXBoundary, the line is infinite.
		 * @return return true if the GraphicBody was colliding
		 */
		bool horizLineCollide(float linePosition, float lowerXBoundary = 1.0f,
		                      float higherXBoundary = -1.0f);

		/**
		 * Collide the current GraphicBody against the given vertical line. The line must be a flat
		 * line parallel to the Y axis (cutting the X axis at position indicated by linePosition.
		 * @param linePosition Position of the line on the X axis. (If the line have no boundaries,
		 * it will cut the X axis at this position.
		 * @param lowerYBoundary Lower boundary of the line (a AABB with a maxY lower than
		 * this value won't collide with the line). If the value is higher than higherYBoundary, the line is infinite.
		 * @param higherYBoundary Higher boundary of the line (a AABB with a minY higher than
		 * this value won't collide with the line). If the value is lower than lowerYBoundary, the line is infinite.
		 * @return return true if the GraphicBody was colliding
		 */
		bool vertLineCollide(float linePosition, float lowerYBoundary = 1.0f,
		                     float higherYBoundary = -1.0f);

		/**
		 * Gets an AABB from the graphic body.
		 * @return Generated bounding box of the sprite's current position.
		 */
		AABB getAABB() const;

		/**
		 * Gets the drag.
		 * @return Vec2 containing the deceleration applied when there is no
		 * acceleration until velocity reaches 0.
		 * @see RedBox::GraphicBody::drag
		 */
		const Vec2& getDrag() const;

		/**
		 * Sets the drag.
		 * @param newDrag New drag. Deceleration applied when there is no
		 * acceleration until velocity reaches 0.
		 * @see RedBox::GraphicBody::drag
		 */
		void setDrag(const Vec2& newDrag);

		/**
		 * Sets the drag.
		 * @param newXDrag New horizontal drag. Deceleration applied when there
		 * is no horizontal acceleration until horizontal velocity reaches 0.
		 * @param newYDrag New vertical drag. Deceleration applied when there is
		 * no vertical acceleration until vertical velocity reaches 0.
		 * @see RedBox::GraphicBody::drag
		 */
		void setDrag(float newXDrag, float newYDrag);

		/**
		 * Gets the horizontal drag.
		 * @return Float containing the horizontal deceleration applied when
		 * there is no horizontal acceleration until horizontal velocity reaches
		 * 0.
		 * @see RedBox::GraphicBody::drag
		 */
		float getXDrag() const;

		/**
		 * Sets the horizontal drag.
		 * @param newXDrag New horizontal drag. Deceleration applied when there
		 * is no horizontal acceleration until horizontal velocity reaches 0.
		 * @see RedBox::GraphicBody::drag
		 */
		void setXDrag(float newXDrag);

		/**
		 * Gets the vertical drag.
		 * @return Float containing the vertical deceleration applied when
		 * there is no vertical acceleration until vertical velocity reaches 0.
		 * @see RedBox::GraphicBody::drag
		 */
		float getYDrag() const;

		/**
		 * Sets the vertical drag.
		 * @param newYDrag New vertical drag. Deceleration applied when there is
		 * no vertical acceleration until vertical velocity reaches 0.
		 * @see RedBox::GraphicBody::drag
		 */
		void setYDrag(float newYDrag);

		/**
		 * Get the graphic body's scaling.
		 * @return 2D vector containing the sprite's scaling currently applied.
		 * @see RedBox::GraphicBody::scaling
		 */
		const Vec2& getScaling() const;

		/**
		 * Change the graphic body's scaling.
		 * @param newScaling New scaling to apply.
		 * @see RedBox::GraphicBody::scaling
		 */
		void setScaling(const Vec2& newScaling);

		/**
		 * Change the graphic body's scaling.
		 * @param xScaling New horizontal scaling to apply.
		 * @param yScaling New vertical scaling to apply.
		 * @see RedBox::GraphicBody::scaling
		 */
		virtual void setScaling(float xScaling, float yScaling);

		/**
		 * Adds some scaling to the current scaling applied.
		 * @param scalingToAdd 2D vector containing the horizontal and vertical
		 * scaling to add. For example, if you pass a Vec2(0.2f, 0.0f) to a
		 * GraphicBody that already has a scaling of Vec2(1.3f, 1.0f), the
		 * scaling will become Vec2(1.5f, 0.0f).
		 * @see RedBox::GraphicBody::scaling
		 */
		void addToScaling(const Vec2& scalingToAdd);

		/**
		 * Adds some scaling to the current scaling applied.
		 * @param xScaling Horizontal scaling to add.
		 * @param yScaling Vertical scaling to add.
		 * @see RedBox::GraphicBody::addToScaling(const Vec2& scalingToAdd)
		 * @see RedBox::GraphicBody::scaling
		 */
		void addToScaling(float xScaling, float yScaling);

		/**
		 * Get the sprite's horizontal scaling.
		 * @return Sprite's horizontal scaling currently applied.
		 * @see RedBox::GraphicBody::scaling
		 */
		float getXScaling() const;

		/**
		 * Change the sprite's scaling.
		 * @param newXScaling New horizontal scaling to apply.
		 * @see RedBox::GraphicBody::scaling
		 */
		void setXScaling(float newXScaling);

		/**
		 * Get the sprite's vertical scaling.
		 * @return Sprite's vertical scaling currently applied.
		 * @see RedBox::GraphicBody::scaling
		 */
		float getYScaling() const;

		/**
		 * Change the sprite's scaling.
		 * @param newYScaling New vertical scaling to apply.
		 * @see RedBox::GraphicBody::scaling
		 */
		void setYScaling(float newYScaling);

		/**
		 * Gets the graphic body's current rotation angle.
		 * @return Graphic body's current rotation angle. As the angle
		 * increments, it rotates counter-clockwise.
		 * @see RedBox::GraphicBody::angle
		 */
		float getAngle() const;

		/**
		 * Sets the graphic body's rotation angle.
		 * @param newAngle Graphic body's new rotation angle. As the angle
		 * increments, it makes the graphic body rotate counter-clockwise.
		 * @see RedBox::GraphicBody::angle
		 */
		virtual void setAngle(float newAngle);

		/**
		 * Adds a value to the sprite's rotation angle.
		 * @param angleToAdd Angle to add to the sprite's current rotation
		 * angle. If the angle goes over 360 or under 0, it is automatically
		 * wrapped around.
		 * @see RedBox::GraphicBody::angle
		 */
		void addToAngle(float angleToAdd);

		/**
		 * Gets the body's colliding box's offset.
		 * @return 2D Vector containing the horizontal and vertical offset.
		 * @see RedBox::GraphicBody::offset
		 */
		const Vec2& getOffset() const;

		/**
		 * Sets the body's colliding box's offset.
		 * @param newOffset New offset to add to the position when detecting
		 * collisions.
		 * @see RedBox::GraphicBody::offset
		 */
		void setOffset(const Vec2& newOffset);

		/**
		 * Sets the body's colliding box's horizontal and vertical offset.
		 * @param newXOffset New horizontal offset to add to the position when
		 * detecting collisions.
		 * @param newYOffset New vertical offset to add to the position when
		 * detecting collisions.
		 * @see RedBox::GraphicBody::offset
		 */
		void setOffset(float newXOffset, float newYOffset);

		/**
		 * Gets the body's colliding box's horizontal offset.
		 * @return Current horizontal offset.
		 * @see RedBox::GraphicBody::offset
		 */
		float getXOffset() const;

		/**
		 * Sets the body's colliding box's horizontal offset.
		 * @param newXOffset New vertical offset to add to the position when
		 * detecting collisions.
		 * @see RedBox::GraphicBody::offset
		 */
		void setXOffset(float newXOffset);

		/**
		 * Gets the body's colliding box's vertical offset.
		 * @return Current vertical offset.
		 * @see RedBox::GraphicBody::offset
		 */
		float getYOffset() const;

		/**
		 * Sets the body's colliding box's horizontal offset.
		 * @param newYOffset New vertical offset to add to the position when
		 * detecting collisions.
		 * @see RedBox::GraphicBody::offset
		 */
		void setYOffset(float newYOffset);

		/**
		 * Gets the horizontal and vertical colliding box ratios.
		 * @return 2D vector containing the horizontal and vertical colliding
		 * box ratios.
		 * @see RedBox::GraphicBody::collidingBoxRatio;
		 */
		const Vec2& getCollidingBoxRatio() const;

		/**
		 * Sets the horizontal and vertical colliding box ratios.
		 * @param newCollidingBoxRatio 2D vector containing the horizontal and
		 * vertical colliding box ratios.
		 * @see RedBox::GraphicBody::collidingBoxRatio
		 */
		void setCollidingBoxRatio(const Vec2& newCollidingBoxRatio);

		/**
		 * Sets the horizontal and vertical colliding box ratios.
		 * @param newXCollidingBoxRatio New horizontal colliding box ratio.
		 * @param newYCollidingBoxRatio New vertical colliding box ratio.
		 * @see RedBox::GraphicBody::collidingBoxRatio
		 */
		void setCollidingBoxRatio(float newXCollidingBoxRatio,
								  float newYCollidingBoxRatio);

		/**
		 * Gets the horizontal colliding box ratios.
		 * @return 2D vector containing the horizontal colliding box ratio.
		 * @see RedBox::GraphicBody::collidingBoxRatio;
		 */
		float getXCollidingBoxRatio() const;

		/**
		 * Sets the horizontal colliding box ratios.
		 * @param newXCollidingBoxRatio New horizontal colliding box ratio.
		 * @see RedBox::GraphicBody::collidingBoxRatio
		 */
		void setXCollidingBoxRatio(float newXCollidingBoxRatio);

		/**
		 * Gets the vertical colliding box ratios.
		 * @return 2D vector containing the vertical colliding box ratio.
		 * @see RedBox::GraphicBody::collidingBoxRatio;
		 */
		float getYCollidingBoxRatio() const;

		/**
		 * Sets the vertical colliding box ratios.
		 * @param newYCollidingBoxRatio New vertical colliding box ratio.
		 * @see RedBox::GraphicBody::collidingBoxRatio
		 */
		void setYCollidingBoxRatio(float newYCollidingBoxRatio);

		/**
		 * Use this function to collide  two GraphicBody against each other. It
		 * will test if they are colliding, and return a pair containing
		 * collision information.
		 * @param body1 A GraphicBody object you want to collide to body2.
		 * @param body2 A GraphicBody object you want to collide to body1.
		 * @return This function return a pair, the first value is a boolean
		 * (true if the objects are colliding), the second value is a structure
		 * containing information about the collision.
		 * @see RedBox::CollisionData
		 */
		static std::pair<bool, CollisionData> collide(GraphicBody* body1,
													  GraphicBody* body2);

		/**
		 * Use this function to collide a list of other GraphicBodys against
		 * another. It will test if they are colliding, and return a pair
		 * containing collision information.
		 * @param graphicBodies1 A list of GraphicBody objects against which you
		 * want to collide the graphicBodies2 list of objects.
		 * @param graphicBodies2 A list of GraphicBody objects against which you
		 * want to collide the graphicBodies1 list of objects.
		 * @return A pair, the first value is a boolean (true if the objects are
		 * colliding), the second value is a list of structure containing
		 * information about the collision.
		 * @see RedBox::CollisionData
		 */
		static std::pair<bool, std::list<CollisionData> > collide(std::list<GraphicBody*> graphicBodies1,
																  std::list<GraphicBody*> graphicBodies2);

		/**
		 * Collide the given GraphicBody against the given horizontal line. The
		 * line must be a flat line parallel to the X axis (cutting the Y axis
		 * at position indicated by linePosition.
		 * @param aGraphicBody Pointer to the graphic body you want to check
		 * collisions with.
		 * @param linePosition Position of the line on the Y axis. (If the line
		 * have no boundaries, it will cut the Y axis at this position.
		 * @param lowerXBoundary Lower boundary of the line (a AABB with a maxX
		 * lower than this value won't collide with the line). If the value is
		 * higher than higherXBoundary, the line is infinite.
		 * @param higherXBoundary Higher boundary of the line (a AABB with a
		 * minX higher than this value won't collide with the line). If the
		 * value is lower than lowerXBoundary, the line is infinite.
		 * @return True if the GraphicBody was colliding, false if not.
		 */
		static bool horizLineCollide(GraphicBody* aGraphicBody,
									 float linePosition,
									 float lowerXBoundary = 1.0f,
									 float higherXBoundary = -1.0f);

		/**
		 * Collide the given GraphicBody against the given vertical line. The
		 * line must be a flat line parallel to the Y axis (cutting the X axis
		 * at position indicated by linePosition.
		 * @param aGraphicBody Pointer to the graphic body you want to check
		 * collisions with.
		 * @param linePosition Position of the line on the X axis. (If the line
		 * have no boundaries, it will cut the X axis at this position.
		 * @param lowerYBoundary Lower boundary of the line (a AABB with a maxY
		 * lower than this value won't collide with the line). If the value is
		 * higher than higherYBoundary, the line is infinite.
		 * @param higherYBoundary Higher boundary of the line (a AABB with a
		 * minY higher than this value won't collide with the line). If the
		 * value is lower than lowerYBoundary, the line is infinite.
		 * @return True if the GraphicBody was colliding, false if not.
		 */
		static bool vertLineCollide(GraphicBody* aGraphicBody,
									float linePosition,
									float lowerYBoundary = 1.0f,
									float higherYBoundary = -1.0f);

	private:
		static float computeVelocity(float velocity, float acceleration, float drag, float max);
		/**
		 * This function will solve the collision on the x axis. It will
		 * separate the objects and return information about the collision by
		 * return value and by seting the collisionInfo structure (passed as a
		 * parameter.
		 * @param object1 Pointer to the first graphic body that you want to
		 * check collisions with.
		 * @param object2 Pointer to the second graphic body that you want to
		 * check collisions with.
		 * @param collisionInfo Structure containing information about the
		 * collision.
		 * @return True if the two objects were colliding, false not.
		 * @see RedBox::CollisionData
		 */
		static bool solveXCollision(GraphicBody* object1, GraphicBody* object2,
		                            CollisionData* collisionInfo);

		/**
		 * This function will solve the collision on the y axis. It will
		 * separate the objects and return information about the collision by
		 * return value and by seting the collisionInfo structure (passed
		 * as a parameter.
		 * @param object1 Pointer to the first graphic body taht you want to
		 * check collisions with.
		 * @param object2 Pointer to the second graphic body that you want to
		 * check collisions with.
		 * @param collisionInfo Structure containing information about the
		 * collision.
		 * @return True if the two objects were colliding, false if not.
		 * @see RedBox::CollisionData
		 */
		static bool solveYCollision(GraphicBody* object1, GraphicBody* object2,
		                            CollisionData* collisionInfo);

		/**
		 * Horizontal and vertical position. Position (0, 0) is at the upper
		 * left corner. The higher the horizontal value, the more to the right
		 * the body is. The higher the vertical value, the more to the bottom
		 * the body is.
		 */
		Vec2 position;

		/// Position at which the graphic body was at the last update.
		Vec2 oldPosition;

		/**
		 * Velocity vector. Contains the graphic body's horizontal and vertical
		 * speed.
		 */
		Vec2 velocity;

		/**
		 * Horizontal and vertical acceleration. Values are in pixels/sec^2.
		 */
		Vec2 acceleration;

		/**
		 * Deceleration applied when there is no acceleration until velocity
		 * reaches 0.
		 */
		Vec2 drag;

		/// Maximum horizontal and vertical velocity.
		Vec2 maxVelocity;

		/// Sprite scaling currently applied on the X and Y axis.
		Vec2 scaling;

		/**
		 * Rotation currently applied to the sprite (in degrees, between 0 and
		 * 360).
		 */
		float angle;

		/**
		 * Contain "Side" flag (see Side.h). It tells which side can collide. A
		 * side that can't collide will let a sprite pass through.
		 */
		FlagSet<Side> collidableSides;

		/**
		 * Elasticity factor of the GraphicBody, will determine how should it
		 * bounce in a collision. Default value is 0 (Solid object). 0.0f means
		 * the graphic body will not rebound at all when a collision is detected
		 * with another static graphic body. The graphic body must be
		 * non-static for its elasticity to be applied. 1.0f would mean perfect
		 * rebound. So if you set an elasticity of 1.0f to an object falling to
		 * the ground, it will rebound at the same height infinitely.
		 */
		float elasticity;

		/**
		 * This GraphicBody won't react to collision if this boolean is set to
		 * true. It will collide, but it won't be moved or affected by the
		 * collision.
		 */
		bool staticBody;

		/// The graphic body's layer.
		Layer layer;

		/**
		 * Used to know if the GraphicBody needs to be deleted. Used internally
		 * by the state that contains the sprite.
		 */
		bool toBeDeleted;

		/**
		 * Used to know if the layer changed. Used internally by the state that
		 * contains the sprite.
		 */
		bool layerChanged;

		/**
		 * Used to know if the GraphicBody is in a state's list of graphic
		 * bodies.
		 */
		bool isInState;

		/// 2D vector added to the position when detecting collisions.
		Vec2 offset;

		/**
		 * Size of the colliding box compared to the body's actual size. To make
		 * the colliding box half the body's size, this vector would be set at
		 * (0.5f, 0.5f).
		 */
		Vec2 collidingBoxRatio;

		/**
		 * Resets the layer changed status.
		 */
		void resetLayerChanged();

		/**
		 * Copies another GraphicBody.
		 * Makes the current instance a copy of the GraphicBody received.
		 * @param src The GraphicBody to make a copy of.
		 */
		void copyFrom(const GraphicBody& src);
	};
}

#endif
