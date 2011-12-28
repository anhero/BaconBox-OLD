/**
 * @file
 * @ingroup Display
 */
#ifndef RB_ORDERABLE_H
#define RB_ORDERABLE_H

namespace RedBox {
	/**
	 * A body that can be ordered by a manager will be derived from this class.
	 * @ingroup Display
	 */
	class Orderable {
	public:

		/**
		 * Custom compare class for the orderable bodies multiset in the sprite
		 * batch.
		 */
		class LessCompare {
		public:
			/**
			 * Compares the z coordinate. A lower z means it is closer to the
			 * camera.
			 * @param o1 First Orderable to compare.
			 * @param o2 Second Orderable to compare.
			 * @return True if the first Orderable is closer to the camera
			 * than the second.
			 */
			bool operator() (const Orderable *o1, const Orderable *o2);
		};

		/**
		 * Default constructor.
		 */
		Orderable();

		/**
		 * Copy constructor.
		 * @param src Orderable to make a copy of.
		 */
		Orderable(const Orderable &src);

		/**
		 * Destructor.
		 */
		virtual ~Orderable();

		/**
		 * Assignment operator.
		 * @param src Orderable to make a copy of.
		 * @return Reference to the modified Orderable.
		 */
		Orderable &operator=(const Orderable &src);

		/**
		 * Gets the body's z coordinate.
		 * @return Z coordinate. The higher the value the closer the body will
		 * be to the camera.
		 * @see RedBox::Orderable::z
		 */
		int getZ() const;

		/**
		 * Sets the body's z coordinate.
		 * @param newZ New z coordinate. The higher the value closer the body
		 * will be to the camera.
		 * @see RedBox::Orderable::z
		 */
		virtual void setZ(int newZ);
	private:
		/// Z coordinate. Higher value means more to the front of the camera.
		int z;
	};

}

#endif
