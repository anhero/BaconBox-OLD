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
