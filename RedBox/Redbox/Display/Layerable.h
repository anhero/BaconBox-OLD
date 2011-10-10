/**
 * @file
 * @ingroup Display
 */
#ifndef RB_LAYERED_BODY_H
#define RB_LAYERED_BODY_H

#include "Disableable.h"
#include "Manageable.h"
#include "Orderable.h"
#include "Scrollable.h"

namespace RedBox {
	/**
	 * Represents the class a State contains.
	 * @ingroup Display
	 */
	class Layerable : public Disableable, public Manageable, public Orderable,
		public Scrollable {
	public:
		/**
		 * Custom compare class for the layered bodies multiset in the state.
		 */
		class LessCompare {
		public:
			/**
			 * Compares which layer is closer to the camera. It first compares
			 * the z coordinate. If they are the same, it compares their
			 * scrolling factor. A lower z means its closer to the camera and
			 * a higher scrolling factor means it's closer to the camera on
			 * that specific z coordinate.
			 * @param l1 First Layerable to compare.
			 * @param l2 Second Layerable to compare.
			 * @return True if the first Layerable is closer to the camera
			 * than the second.
			 */
			bool operator() (const Layerable *l1, const Layerable *l2);
		};

		/**
		 * Default constructor.
		 */
		Layerable();

		/**
		 * Copy constructor.
		 * @param src Layerable to make a copy of.
		 */
		Layerable(const Layerable &src);

		/**
		 * Destructor.
		 */
		virtual ~Layerable();

		/**
		 * Assignment operator.
		 * @param src Layerable to make a copy of.
		 * @return Reference to the modified Layerable.
		 */
		Layerable &operator=(const Layerable &src);

		/**
		 * Sets the body's z coordinate.
		 * @param newZ New z coordinate. The higher the value closer the body
		 * will be to the camera.
		 * @see RedBox::Orderable::z
		 */
		void setZ(int newZ);

		/**
		 * Sets the body's scroll factor.
		 * @param newXScrollFactor New horizontal scroll factor. A value higher
		 * than 1 means the body will move faster as if it were closer to the
		 * camera and between 1 and 0 means it will move as if it were far from
		 * the camera.
		 * @param newYScrollFactor New vertical scroll factor. A value higher
		 * than 1 means the body will move faster as if it were closer to the
		 * camera and between 1 and 0 means it will move as if it were far from
		 * the camera.
		 * @see RedBox::Scrollable::scrollFactor
		 */
		void setScrollFactor(float newXScrollFactor, float newYScrollFactor);
	};

}

#endif
