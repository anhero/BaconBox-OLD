/**
 * @file
 * @ingroup Display
 */

#ifndef __RENDERABLE_H
#define __RENDERABLE_H

namespace RedBox {
	/**
	 * Represents a renderable object assiociated with its z coordinate.
     * @ingroup Display
	 */
	class Renderable {
	private:
		/**
		 * The z coordinate.
		 */
		int z;
		/**
		 * Copies another renderable.
		 * Makes the current instance a copy of the renderable received.
		 * @param src The renderable to make a copy of.
		 */
		void copyFrom(const Renderable& src);
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
	};
}

#endif