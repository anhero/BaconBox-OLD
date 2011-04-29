/**
 * @file
 * @ingroup Display
 */

#include "Vec2.h"
#ifndef RB_RENDERABLE_H
#define RB_RENDERABLE_H

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
		
	private:
		///Position vector
		Vec2 position;
		
		///last position vector
		Vec2 oldPosition;
		
		///Velocity vector
		Vec2 velocity;
		
		///acceleration vector
		Vec2 acceleration;
		
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