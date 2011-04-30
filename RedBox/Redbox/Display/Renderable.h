/**
 * @file
 * @ingroup Display
 */

#include "Vec2.h"
#include "Side.h"
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
		void setVelocity(Vec2 velocity);
		/**
		 * Return the velocity vector
		 */
		Vec2 getVelocity();
		/**
		 * Set the acceleration vector
		 */
		void setAcceleration(Vec2 acceleration);
		/**
		 * Return the acceleration vector
		 */
		Vec2 getAcceleration();
		
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


	private:
		///Position vector
		Vec2 position;
		
		///last position vector
		Vec2 oldPosition;
		
		///Velocity vector
		Vec2 velocity;
		
		///acceleration vector
		Vec2 acceleration;
		
		
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
