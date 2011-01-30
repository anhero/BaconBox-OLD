/**
 * @file
 * @ingroup Display
 */

#ifndef RB_RENDERABLE_H
#define RB_RENDERABLE_H

namespace RedBox {
	/**
	 * Represents a renderable object assiociated with its z coordinate.
     * @ingroup Display
	 */
	class Renderable {
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
		virtual void update()=0;
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
	private:
		/// The z coordinate.
		int z;
		/// Used to know if the renderable needs to be deleted.
		bool toBeDeleted;
		/// Used to know if the z changed.
		bool zChanged;
		/**
		 * Copies another renderable.
		 * Makes the current instance a copy of the renderable received.
		 * @param src The renderable to make a copy of.
		 */
		void copyFrom(const Renderable& src);
	};
}

#endif