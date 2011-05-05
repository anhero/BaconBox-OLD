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
#include "AABB.h"

namespace RedBox {
	/**
	 * Represents a GraphicBody object assiociated with its z coordinate.
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
		 * Gets the z coordinate.
		 */
		int getZ() const;
		/**
		 * Sets the z coordinate.
		 */
		void setZ(int z);
		/**
		 * Checks if the GraphicBody needs to be deleted.
		 * @return True if the GraphicBody needs to be deleted false if not.
		 */
		bool isToBeDeleted() const;
		/**
		 * Checks if the z has recently been changed and not yet updated.
		 * @return True if the z has recently been changed, false if not.
		 */
		bool isZChanged() const;
		/**
		 * Sets the GraphicBody to be deleted or not.
		 * @param newToBeDeleted New value to be deleted.
		 */
		void setToBeDeleted(bool newToBeDeleted);
		/**
		 * Resets the z changed status.
		 */
		void resetZChanged();
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
		static std::pair<bool, CollisionData> collide(GraphicBody* object1, GraphicBody* object2);

		
		static bool lineXCollide(GraphicBody * aGraphicBody, float linePosition, float lowerXBoundary = 1.0f, float higherXBoundary = -1.0f);
		static bool lineYCollide(GraphicBody * aGraphicBody, float linePosition, float lowerYBoundary = 1.0f, float higherYBoundary = -1.0f);

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
		
	private:
		/**
		 * This function will solve the collision on the x axis. It will separate the objects and
		 * return information about the collision by return value and by seting the collisionInfo structure (passed
		 * as a parameter.
		 * @param object1 object1 A GraphicBody object you want to collide to object2.
		 * @param object2 A GraphicBody object you want to collide to object1
		 * @oaram collisionData Structure containing information about the collision (see CollisionData)
		 * @return Return true if the two objects were colliding, false in the other case.
		 */
		static bool solveXCollision(GraphicBody* object1, GraphicBody* object2, CollisionData* collisionInfo);
		/**
		 * This function will solve the collision on the y axis. It will separate the objects and
		 * return information about the collision by return value and by seting the collisionInfo structure (passed
		 * as a parameter.
		 * @param object1 object1 A GraphicBody object you want to collide to object2.
		 * @param object2 A GraphicBody object you want to collide to object1
		 * @oaram collisionData Structure containing information about the collision (see CollisionData)
		 * @return Return true if the two objects were colliding, false in the other case.
		 */
		static bool solveYCollision(GraphicBody* object1, GraphicBody* object2, CollisionData* collisionInfo);


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
		/// The z coordinate.
		int z;
		/// Used to know if the GraphicBody needs to be deleted.
		bool toBeDeleted;
		/// Used to know if the z changed.
		bool zChanged;
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
