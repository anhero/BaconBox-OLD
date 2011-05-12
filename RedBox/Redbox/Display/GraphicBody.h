/**
 * @file
 * @ingroup Display
 */
#ifndef RB_GraphicBody_H
#define RB_GraphicBody_H

#include <list>

#include "Object.h"
#include "Vec2.h"
#include "Side.h"
#include "CollisionData.h"
#include "Layer.h"
#include "AABB.h"

namespace RedBox {
	/**
	 * Represents a GraphicBody object assiociated with its layer.
	 * @ingroup Display
	 */
	class GraphicBody : public Object {
		friend class State;
	public:
		static const float NO_MAX_VELOCITY = -1.0f;
		/**
		 * The default constructor.
		 */
		GraphicBody();
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
		 * Gets the layer.
		 */
		const Layer& getLayer() const;
		/**
		 * Sets the layer.
		 */
		void setLayer(const Layer& newLayer);

		/**
		 * Sets the graphic body's coordinate.
		 * @param newZ New z coordinate. The higher the value closer the graphic
		 * body will be.
		 */
		void setZ(int newZ);

		/**
		 * Sets the graphic body's scroll factor.
		 * @param newScrollFactor New horizontal and vertical scroll factor. A
		 * value higher than 1 means the graphic body will move faster as if it
		 * were closer to the camera and between 1 and 0 means it will move as
		 * if it were far from the camera.
		 */
		void setScrollFactor(const Vec2& newScrollFactor);

		/**
		 * Sets the graphic body's horizontal scroll factor.
		 * @param newXScrollFactor New horizontal scroll factor. A value higher
		 * than 1 means the graphic body will move faster as if it were closer
		 * to the camera and between 1 and 0 means it will move as if it were
		 * far from the camera.
		 */
		void setXScrollFactor(float newXScrollFactor);

		/**
		 * Sets the graphic body's vertical scroll factor.
		 * @param newYScrollFactor New vertical scroll factor. A value higher
		 * than 1 means the graphic body will move faster as if it were closer
		 * to the camera and between 1 and 0 means it will move as if it were
		 * far from the camera.
		 */
		void setYScrollFactor(float newYScrollFactor);

		/**
		 * Gets the graphic body's z coordinate.
		 * @return Z coordinate. The higher the value the closer the graphic
		 * body will be.
		 */
		int getZ() const;

		/**
		 * Gets the graphic body's scroll factor.
		 * @return Horizontal and vertical scroll factor. A value higher than 1
		 * means the graphic body will move faster as if it were closer to the
		 * camera, between 1 and 0 means it will move as if it were far from the
		 * camera.
		 */
		const Vec2& getScrollFactor() const;

		/**
		 * Gets the graphic body's horizontal scroll factor.
		 * @return Horizontal scroll factor. A value higher than 1 means the
		 * graphic body will move faster as if it were closer to the camera,
		 * between 1 and 0 means it will move as if it were far from the camera.
		 */
		float getXScrollFactor() const;

		/**
		 * Gets the graphic body's vertical scroll factor.
		 * @return Vertical scroll factor. A value higher than 1 means the
		 * graphic body will move faster as if it were closer to the camera,
		 * between 1 and 0 means it will move as if it were far from the camera.
		 */
		float getYScrollFactor() const;

		/**
		 * Checks if the GraphicBody needs to be deleted.
		 * @return True if the GraphicBody needs to be deleted false if not.
		 */
		bool isToBeDeleted() const;

		/**
		 * Checks if the layer has recently been changed and not yet updated.
		 * @return True if the layer has recently been changed, false if not.
		 */
		bool isLayerChanged() const;

		/**
		 * Sets the GraphicBody to be deleted or not.
		 * @param newToBeDeleted New value to be deleted.
		 */
		void setToBeDeleted(bool newToBeDeleted);

		/**
		 * Resets the layer changed status.
		 */
		void resetLayerChanged();

		/**
		 * Set the velocity vector
		 */
		void setVelocity(const Vec2& velocity);

		/**
		 * Set the x factor of the velocity vector.
		 */
		void setVelocityX(float xVelocity);

		/**
		 * Set the y factor of the velocity vector.
		 */
		void setVelocityY(float yVelocity);

		/**
		 * Return the velocity vector
		 */
		const Vec2& getVelocity();

		/**
		 * Return the x factor of the velocity vector
		 */
		float getVelocityX();

		/**
		 * Return the y factor of the velocity vector
		 */
		float getVelocityY();

		/**
		 * Set the acceleration vector
		 */
		void setAcceleration(const Vec2& acceleration);

		/**
		 * Set the x factor of the accelaration vector.
		 */
		void setAccelerationX(float xAccelaration);

		/**
		 * Set the y factor of the accelaration vector.
		 */
		void setAccelerationY(float yAccelaration);

		/**
		 * Return the acceleration vector
		 */
		const Vec2& getAcceleration();

		/**
		 * Return the x factor of the acceleration vector
		 */
		float getAccelerationX();

		/**
		 * Return the y factor of the acceleration vector
		 */
		float getAccelerationY();

		/**
		 * Gets the GraphicBody's horizontal position.
		 * @return Horizontal position (in pixels). Lower value means more to
		 * the left.
		 */
		virtual float getXPosition() const;
		/**
		 * Gets the GraphicBody's vertical position.
		 * @return Vertical position (in pixels). Lower value means more at the
		 * top.
		 */
		virtual float getYPosition() const;

		virtual const Vec2& getPosition() const;

		/**
		 * Sets the GraphicBody's horizontal position.
		 * @param x New horizontal position (in pixels). Lower value means more
		 * to the left.
		 */
		virtual void setXPosition(float x);
		/**
		 * Sets the GraphicBody's horizontal position.
		 * @param y New vertical position (in pixels). Lower value means more at
		 * the top.
		 */
		virtual void setYPosition(float y);
		/**
		 * Sets the GraphicBody's horizontal and vertical position.
		 * @param x New horizontal position (in pixels). Lower value means more
		 * to the left.
		 * @param y New vertical position (in pixels). Lower value means more at
		 * the top.
		 */
		virtual void setPosition(float x, float y);

		/**
		 * Sets the GraphicBody's horizontal and vertical position.
		 * @param newPosition New horizontal and vertical position.
		 * @see GraphicBody::setPosition(float x, float y)
		 */
		void setPosition(const Vec2& newPosition);

		/**
		 * Return x position before any movement was applied (at the start of the update)
		 */
		float getOldXPosition();

		/**
		 * Return y position before any movement was applied (at the start of the update)
		 */
		float getOldYPosition();

		/**
		 * Moves the GraphicBody horizontally.
		 * @param deltaX Value to add to the GraphicBody's horizontal position (in
		 * pixels). Positive value moves the GraphicBody to the right and a negative
		 * value moves the GraphicBody to the left.
		 */
		virtual void moveX(float deltaX);

		/**
		 * Moves the GraphicBody vertically.
		 * @param deltaY Value to add to the GraphicBody's vertical position (in
		 * pixels). Positive value moves the GraphicBody down and a negative value
		 * moves the GraphicBody up.
		 */
		virtual void moveY(float deltaY);

		/**
		 * Moves the GraphicBody horizontally and vertically.
		 * @param deltaX Value to add to the GraphicBody's horizontal position (in
		 * pixels). Positive value moves the GraphicBody to the right and a negative
		 * value moves the GraphicBody to the left.
		 * @param deltaY Value to add to the GraphicBody's vertical position (in
		 * pixels). Positive value moves the GraphicBody down and a negative value
		 * moves the GraphicBody up.
		 */
		virtual void move(float deltaX, float deltaY);


		///Set the absolute maxmimum velocity in x (Maximum velocity in both x direction)
		void setMaxVelocityX(float xVelocity);

		///Set the absolute maxmimum velocity in y (Maximum velocity in both y direction)
		void setMaxVelocityY(float yVelocity);

		///Set the absolute maxmimum velocity in x and y (Maximum velocity in both direction for both axis)
		void setMaxVelocity(float xVelocity, float yVelocity);

		///Return the absolute maximum velocity in x (Maximum velocity in both x direction)
		float getMaxVelocityX();

		///Return the absolute maximum velocity in y (Maximum velocity in both y direction)
		float getMaxVelocityY();

		/**
		 * return GraphicBody's width.
		 */
		virtual float getWidth() const = 0;

		/**
		 * return GraphicBody's height.
		 */
		virtual float getHeight() const = 0;


		/**
		 * Use to set the collidableSides flag.
		 * Used to set which side of a sprite should collide and which should not.
		 * @param collidableSides Correct value are LEFT | RIGHT | TOP | BOTTOM | ALL
		 */
		void setCollidableSides(Side::Enum collidableSides);

		/**
		 * Getter for the collidableSides flag.
		 * Used to get which side of a sprite should collide and which should not.
		 * @return Possible return flag : LEFT | RIGHT | TOP | BOTTOM
		 */
		Side::Enum getCollidableSides();

		/**
		 * Return true if the given sides are collidable sides.
		 * @param sides Correct value are LEFT | RIGHT | TOP | BOTTOM | ALL
		 */
		bool IsCollidingSide(Side::Enum sides);

		/**
		* Return if the GraphicBody is a static one.
		* A static object won't react to collision. (wall, floor, moving platform, etc.)
		*/
		bool getIsStatic();

		/**
		* Set if the GraphicBody is a static one.
		* A static object won't react to collision. (wall, floor, moving platform, etc.)
		*/
		void setIsStatic(bool isStatic);

		/**
		* Return the elasticity factor of the GraphicBody.
		* Elasticity  will determine how should it bounce in a collision. Default value is 0 (Solid object)
		*/
		float getElasticity();
		/**
		* Set the elasticity factor of the GraphicBody.
		* Elasticity  will determine how should it bounce in a collision. Default value is 0 (Solid object)
		*/
		void setElasticity(float elasticity);

		/**
		 * Use this function to collide the current GraphicBody against another one.
		 * It will test if they are colliding, and return a pair containing collision information.
		 * @param aGraphicBody A GraphicBody object against which you want to collide the current object.
		 * @return This function return a pair, the first value is a boolean (true if the objects are colliding),
		 * the second value is a structure containing information about the collision. See CollisionData.
		 */
		std::pair<bool, CollisionData> collide(GraphicBody* aGraphicBody);


		/**
		 * Use this function to collide the current GraphicBody against a list of other GraphicBodys.
		 * It will test if they are colliding, and return a pair containing collision information.
		 * @param GraphicBodys A list of GraphicBody objects against which you want to collide the current object.
		 * @return This function return a pair, the first value is a boolean (true if the objects are colliding),
		 * the second value is a list of structure containing information about the collision. See CollisionData.
		 */
		std::pair<bool, std::list<CollisionData> > collide(std::list<GraphicBody*> GraphicBodys);

		/**
		 * Use this function to collide a list of other GraphicBodys against another.
		 * It will test if they are colliding, and return a pair containing collision information.
		 * @param GraphicBodys1 A list of GraphicBody objects against which you want to collide the GraphicBodys2 list of objects.
		 * @param GraphicBodys2 A list of GraphicBody objects against which you want to collide the GraphicBodys1 list of objects.
		 * @return This function return a pair, the first value is a boolean (true if the objects are colliding),
		 * the second value is a list of structure containing information about the collision. See CollisionData.
		 */
		static std::pair<bool, std::list<CollisionData> > collide(std::list<GraphicBody*> GraphicBodys1, std::list<GraphicBody*> GraphicBodys2);

		/**
		 * Use this function to collide  two GraphicBody against each other.
		 * It will test if they are colliding, and return a pair containing collision information.
		 * @param object1 A GraphicBody object you want to collide to object2.
		 * @param object2 A GraphicBody object you want to collide to object1
		 * @return This function return a pair, the first value is a boolean (true if the objects are colliding),
		 * the second value is a structure containing information about the collision. See CollisionData.
		 */
		static std::pair<bool, CollisionData> collide(GraphicBody* object1,
													  GraphicBody* object2);
		
		/**
		 * Collide the current GraphicBody against the given horizontal line. The line must be a flat 
		 * line parallel to the X axis (cutting the Y axis at position indicated by linePosition.
		 * @param linePosition Position of the line on the Y axis. (If the line have no boundaries, 
		 * it will cut the Y axis at this position.
		 * @param lowerXboundary Lower boundary of the line (a AABB with a maxX lower than 
		 * this value won't collide with the line). If the value is higher than higherXBoundary, the line is infinite.
		 * @param higherXboundary Higher boundary of the line (a AABB with a minX higher than 
		 * this value won't collide with the line). If the value is lower than lowerXBoundary, the line is infinite.
		 * @return return true if the GraphicBody was colliding
		 */
		bool horizLineCollide(float linePosition, float lowerXBoundary = 1.0f,
							  float higherXBoundary = -1.0f);
		/**
		 * Collide the current GraphicBody against the given vertical line. The line must be a flat 
		 * line parallel to the Y axis (cutting the X axis at position indicated by linePosition.
		 * @param linePosition Position of the line on the X axis. (If the line have no boundaries, 
		 * it will cut the X axis at this position.
		 * @param lowerYboundary Lower boundary of the line (a AABB with a maxY lower than 
		 * this value won't collide with the line). If the value is higher than higherYBoundary, the line is infinite.
		 * @param higherYboundary Higher boundary of the line (a AABB with a minY higher than 
		 * this value won't collide with the line). If the value is lower than lowerYBoundary, the line is infinite.
		 * @return return true if the GraphicBody was colliding
		 */
		bool vertLineCollide(float linePosition, float lowerYBoundary = 1.0f,
							 float higherYBoundary = -1.0f);

		/**
		 * Collide the given GraphicBody against the given horizontal line. The line must be a flat 
		 * line parallel to the X axis (cutting the Y axis at position indicated by linePosition.
		 * @param aGraphicBody The graphic body you want to collide.
		 * @param linePosition Position of the line on the Y axis. (If the line have no boundaries, 
		 * it will cut the Y axis at this position.
		 * @param lowerXboundary Lower boundary of the line (a AABB with a maxX lower than 
		 * this value won't collide with the line). If the value is higher than higherXBoundary, the line is infinite.
		 * @param higherXboundary Higher boundary of the line (a AABB with a minX higher than 
		 * this value won't collide with the line). If the value is lower than lowerXBoundary, the line is infinite.
		 * @return return true if the GraphicBody was colliding
		 */
		static bool horizLineCollide(GraphicBody * aGraphicBody,
									 float linePosition,
									 float lowerXBoundary = 1.0f,
									 float higherXBoundary = -1.0f);
	
		/**
		 * Collide the given GraphicBody against the given vertical line. The line must be a flat 
		 * line parallel to the Y axis (cutting the X axis at position indicated by linePosition.
		 * @param aGraphicBody The graphic body you want to collide.
		 * @param linePosition Position of the line on the X axis. (If the line have no boundaries, 
		 * it will cut the X axis at this position.
		 * @param lowerYboundary Lower boundary of the line (a AABB with a maxY lower than 
		 * this value won't collide with the line). If the value is higher than higherYBoundary, the line is infinite.
		 * @param higherYboundary Higher boundary of the line (a AABB with a minY higher than 
		 * this value won't collide with the line). If the value is lower than lowerYBoundary, the line is infinite.
		 * @return return true if the GraphicBody was colliding
		 */
		static bool vertLineCollide(GraphicBody * aGraphicBody,
									float linePosition,
									float lowerYBoundary = 1.0f,
									float higherYBoundary = -1.0f);

		/**
		 * Gets an AABB from the graphic body.
		 */
		AABB getAABB();

		/**
		 * Sets the drag.
		 * @param newDrag New drag. Deceleration applied when there is no
		 * acceleration until velocity reaches 0.
		 */
		void setDrag(const Vec2& newDrag);

		/**
		 * Gets the drag.
		 * @return Vec2 containing the deceleration applied when there is no
		 * acceleration until velocity reaches 0.
		 */
		const Vec2& getDrag() const;
		
		/**
		 * Change the sprite's scaling.
		 * @param newScaling New scaling to apply.
		 */
		void setScaling(const Vec2& newScaling);

		/**
		 * Change the sprite's scaling.
		 * @param xScaling New horizontal scaling to apply.
		 * @param yScaling New vertical scaling to apply.
		 */
		virtual void setScaling(float xScaling, float yScaling);

		/**
		 * Adds some scaling to the current scaling applied.
		 * @param scalingToAdd 2D vector containing the horizontal and vertical
		 * scaling to add. For example, if you pass a Vec2(0.2f, 0.0f) to a
		 * GraphicBody that already has a scaling of Vec2(1.3f, 1.0f), the
		 * scaling will become Vec2(1.5f, 0.0f).
		 */
		void addToScaling(const Vec2& scalingToAdd);
		/**
		 * Adds some scaling to the current scaling applied.
		 * @param xScaling Horizontal scaling to add.
		 * @param yScaling Vertical scaling to add.
		 * @see RedBox::GraphicBody::addToScaling(const Vec2& scalingToAdd)
		 */
		void addToScaling(float xScaling, float yScaling);

		/**
		 * Change the sprite's scaling.
		 * @param newXScaling New horizontal scaling to apply.
		 */
		void setXScaling(float newXScaling);

		/**
		 * Change the sprite's scaling.
		 * @param newYScaling New vertical scaling to apply.
		 */
		void setYScaling(float newYScaling);

		/**
		 * Get the sprite's scaling.
		 * @return 2D vector containing the sprite's scaling currently applied.
		 */
		const Vec2& getScaling() const;

		/**
		 * Get the sprite's horizontal scaling.
		 * @return Sprite's horizontal scaling currently applied.
		 */
		float getXScaling() const;

		/**
		 * Get the sprite's vertical scaling.
		 * @return Sprite's vertical scaling currently applied.
		 */
		float getYScaling() const;

		/**
		 * Gets the sprite's current rotation angle.
		 * @return Sprite's current rotation angle. As the angle increments, it
		 * rotates counter-clockwise.
		 */
		float getAngle() const;

		/**
		 * Sets the sprite's rotation angle.
		 * @param newAngle Sprite's new rotation angle. As the angle increments,
		 * it makes the sprite rotate counter-clockwise.
		 */
		virtual void setAngle(float newAngle);

		/**
		 * Adds a value to the sprite's rotation angle.
		 * @param angleToAdd Angle to add to the sprite's current rotation
		 * angle. If the angle goes over 360 or under 0, it is automatically
		 * wrapped around.
		 */
		void addToAngle(float angleToAdd);
	private:
		/**
		 * This function will solve the collision on the x axis. It will separate the objects and
		 * return information about the collision by return value and by seting the collisionInfo structure (passed
		 * as a parameter.
		 * @param object1 object1 A GraphicBody object you want to collide to object2.
		 * @param object2 A GraphicBody object you want to collide to object1
		 * @param collisionInfo Structure containing information about the collision (see CollisionData)
		 * @return Return true if the two objects were colliding, false in the other case.
		 */
		static bool solveXCollision(GraphicBody* object1, GraphicBody* object2,
									CollisionData* collisionInfo);

		/**
		 * This function will solve the collision on the y axis. It will separate the objects and
		 * return information about the collision by return value and by seting the collisionInfo structure (passed
		 * as a parameter.
		 * @param object1 object1 A GraphicBody object you want to collide to object2.
		 * @param object2 A GraphicBody object you want to collide to object1
		 * @param collisionInfo Structure containing information about the collision (see CollisionData)
		 * @return Return true if the two objects were colliding, false in the other case.
		 */
		static bool solveYCollision(GraphicBody* object1, GraphicBody* object2,
									CollisionData* collisionInfo);


		/// Position vector
		Vec2 position;

		/// Last position vector
		Vec2 oldPosition;

		/// Velocity vector
		Vec2 velocity;

		/// Acceleration vector
		Vec2 acceleration;

		/**
		 * Deceleration applied when there is no acceleration until velocity
		 * reaches 0.
		 */
		Vec2 drag;

		/// Maximum velocity in X
		float maxVelocityX;

		/// Maximum velocity in Y
		float maxVelocityY;

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
		Side::Enum collidableSides;

		/**
		 * Elasticity factor of the GraphicBody, will determine how should it
		 * bounce in a collision. Default value is 0 (Solid object).
		 */
		float elasticity;

		/**
		 * This GraphicBody won't react to collision if this boolean is set to
		 * true.
		 */
		bool staticObject;

		/// The graphic body's layer.
		Layer layer;

		/// Used to know if the GraphicBody needs to be deleted.
		bool toBeDeleted;

		/// Used to know if the layer changed.
		bool layerChanged;

		/// Used to know if the GraphicBody is in a state's list of GraphicBodys.
		bool isInState;

		/**
		 * Copies another GraphicBody.
		 * Makes the current instance a copy of the GraphicBody received.
		 * @param src The GraphicBody to make a copy of.
		 */
		void copyFrom(const GraphicBody& src);
	};
}

#endif
