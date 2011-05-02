/**
 * @file
 * @ingroup Display
 */

#include "Vec2.h"
#include "Side.h"
#include "CollisionData.h"
#include "AABB.h"
#include <list>
#ifndef RB_RENDERABLE_H
#define RB_RENDERABLE_H
#define NO_MAX_VELOCITY -1


namespace RedBox {
	/**
	 * Represents a renderable object assiociated with its z coordinate.
     * @ingroup Display
	 */
	class Renderable {
		friend class State;
	public:
		/**
		 * The default constructor.
		 */
		Renderable();
		/**
		 * The copy constructor.
		 * @param src The renderable to make a copy of.
		 */
		Renderable(const Renderable& src);
		/**
		 * The destructor.
		 */
		virtual ~Renderable();
		/**
		 * The assignment operator overload.
		 * @param src The renderable to make a copy of.
		 */
		Renderable& operator=(const Renderable& src);
		/**
		 * Updates the renderable.
		 */
		virtual void update();
		/**
		 * Renders the renderable.
		 */
		virtual void render()=0;
		/**
		 * Gets the z coordinate.
		 */
		int getZ() const;
		/**
		 * Sets the z coordinate.
		 */
		void setZ(int z);
		/**
		 * Checks if the renderable needs to be deleted.
		 * @return True if the renderable needs to be deleted false if not.
		 */
		bool isToBeDeleted() const;
		/**
		 * Checks if the z has recently been changed and not yet updated.
		 * @return True if the z has recently been changed, false if not.
		 */
		bool isZChanged() const;
		/**
		 * Sets the renderable to be deleted or not.
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
		 * Gets the renderable's horizontal position.
		 * @return Horizontal position (in pixels). Lower value means more to
		 * the left.
		 */
		virtual float getXPosition() const;
		/**
		 * Gets the renderable's vertical position.
		 * @return Vertical position (in pixels). Lower value means more at the
		 * top.
		 */
		virtual float getYPosition() const;
		
		/**
		 * Sets the renderable's horizontal position.
		 * @param x New horizontal position (in pixels). Lower value means more
		 * to the left.
		 */
		virtual void setXPosition(float x);
		/**
		 * Sets the renderable's horizontal position.
		 * @param y New vertical position (in pixels). Lower value means more at
		 * the top.
		 */
		virtual void setYPosition(float y);
		/**
		 * Sets the renderable's horizontal and vertical position.
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
		 * Moves the renderable horizontally.
		 * @param deltaX Value to add to the renderable's horizontal position (in
		 * pixels). Positive value moves the renderable to the right and a negative
		 * value moves the renderable to the left.
		 */
		virtual void moveX(float deltaX);
		/**
		 * Moves the renderable vertically.
		 * @param deltaY Value to add to the renderable's vertical position (in
		 * pixels). Positive value moves the renderable down and a negative value
		 * moves the renderable up.
		 */
		virtual void moveY(float deltaY);
		/**
		 * Moves the renderable horizontally and vertically.
		 * @param deltaX Value to add to the renderable's horizontal position (in
		 * pixels). Positive value moves the renderable to the right and a negative
		 * value moves the renderable to the left.
		 * @param deltaY Value to add to the renderable's vertical position (in
		 * pixels). Positive value moves the renderable down and a negative value
		 * moves the renderable up.
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
		 * return renderable's width.
		 */
		virtual float getWidth() const = 0;
		
		/**
		 * return renderable's height.
		 */
		virtual float getHeight() const = 0;
		

		/**
		 * Use to set the collidableSides flag. 
		 * Used to set which side of a sprite should collide and which should not.
		 * @param collidableSides Correct value are LEFT | RIGHT | TOP | BOTTOM | ALL
		 */
		 void setCollidableSides(RB_SIDE collidableSides);
		
		/**
		 * Getter for the collidableSides flag. 
		 * Used to get which side of a sprite should collide and which should not.
		 * @return Possible return flag : LEFT | RIGHT | TOP | BOTTOM 
		 */
		RB_SIDE getCollidableSides();
		
		/**
		 * Return true if the given sides are collidable sides.
		 * @param sides Correct value are LEFT | RIGHT | TOP | BOTTOM | ALL
		 */
		bool IsCollidingSide(RB_SIDE sides);

		/**
		* Return if the renderable is a static one.
		* A static object won't react to collision. (wall, floor, moving platform, etc.)
		*/
		bool getIsStatic();

		/**
		* Set if the renderable is a static one.
		* A static object won't react to collision. (wall, floor, moving platform, etc.)
		*/
		void setIsStatic(bool isStatic);

		/** 
		* Return the elasticity factor of the renderable.
		* Elasticity  will determine how should it bounce in a collision. Default value is 0 (Solid object)
		*/
		float getElasticity();
		/** 
		* Set the elasticity factor of the renderable.
		* Elasticity  will determine how should it bounce in a collision. Default value is 0 (Solid object)
		*/
		void setElasticity(float elasticity);
		
		/**
		 * Use this function to collide the current renderable against another one. 
		 * It will test if they are colliding, and return a pair containing collision information.
		 * @param aRenderable A Renderable object against which you want to collide the current object.
		 * @return This function return a pair, the first value is a boolean (true if the objects are colliding), 
		 * the second value is a structure containing information about the collision. See CollisionData.
		 */
		std::pair<bool, CollisionData> collide(Renderable * aRenderable);
		
		
		/**
		 * Use this function to collide the current renderable against a list of other renderables. 
		 * It will test if they are colliding, and return a pair containing collision information.
		 * @param renderables A list of Renderable objects against which you want to collide the current object.
		 * @return This function return a pair, the first value is a boolean (true if the objects are colliding), 
		 * the second value is a list of structure containing information about the collision. See CollisionData.
		 */
		std::pair<bool, std::list<CollisionData> > collide(std::list<Renderable*> renderables);

		/**
		 * Use this function to collide a list of other renderables against another. 
		 * It will test if they are colliding, and return a pair containing collision information.
		 * @param renderables1 A list of Renderable objects against which you want to collide the renderables2 list of objects.
		 * @param renderables2 A list of Renderable objects against which you want to collide the renderables1 list of objects.
		 * @return This function return a pair, the first value is a boolean (true if the objects are colliding), 
		 * the second value is a list of structure containing information about the collision. See CollisionData.
		 */
		static std::pair<bool, std::list<CollisionData> > collide(std::list<Renderable*> renderables1, std::list<Renderable*> renderables2);

		
		/**
		 * Use this function to collide  two renderable against each other. 
		 * It will test if they are colliding, and return a pair containing collision information.
		 * @param object1 A Renderable object you want to collide to object2.
		 * @param object2 A Renderable object you want to collide to object1
		 * @return This function return a pair, the first value is a boolean (true if the objects are colliding), 
		 * the second value is a structure containing information about the collision. See CollisionData.
		 */
		static std::pair<bool, CollisionData> collide(Renderable * object1, Renderable * object2);
		
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
		 * @param object1 object1 A Renderable object you want to collide to object2.
		 * @param object2 A Renderable object you want to collide to object1
		 * @oaram collisionData Structure containing information about the collision (see CollisionData)
		 * @return Return true if the two objects were colliding, false in the other case.
		 */
		static bool solveXCollision(Renderable * object1, Renderable * object2, CollisionData * collisionInfo);
		/**
		 * This function will solve the collision on the y axis. It will separate the objects and
		 * return information about the collision by return value and by seting the collisionInfo structure (passed
		 * as a parameter. 
		 * @param object1 object1 A Renderable object you want to collide to object2.
		 * @param object2 A Renderable object you want to collide to object1
		 * @oaram collisionData Structure containing information about the collision (see CollisionData)
		 * @return Return true if the two objects were colliding, false in the other case.
		 */
		static bool solveYCollision(Renderable * object1, Renderable * object2, CollisionData * collisionInfo);

		
		///Position vector
		Vec2 position;
		
		///last position vector
		Vec2 oldPosition;
		
		///Velocity vector
		Vec2 velocity;
		
		///acceleration vector
		Vec2 acceleration;

		/**
		 * Deceleration applied when there is no acceleration until velocity
		 * reaches 0.
		 */
		Vec2 drag;
		
		
		///Maximum velocity in X
		float maxVelocityX;
		
		///Maximum velocity in Y
		float maxVelocityY;
		
		/**
		 *Contain "Side" flag (see Side.h). It tells which side can collide. 
		 * A side that can't collide will let a sprite pass through.
		 */
		RB_SIDE collidableSides;
	
		///Elasticity factor of the renderable, will determine how should it bounce in a collision. Default value is 0 (Solid object)
		float elasticity;
		
		///This renderable won't react to collision if this boolean is set to true. 
		bool staticObject;
		/// The z coordinate.
		int z;
		/// Used to know if the renderable needs to be deleted.
		bool toBeDeleted;
		/// Used to know if the z changed.
		bool zChanged;
		/// Used to know if the renderable is in a state's list of renderables.
		bool isInState;
		/**
		 * Copies another renderable.
		 * Makes the current instance a copy of the renderable received.
		 * @param src The renderable to make a copy of.
		 */
		void copyFrom(const Renderable& src);
	};
}

#endif
