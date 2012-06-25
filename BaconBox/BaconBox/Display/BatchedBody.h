/**
 * @file
 */
#ifndef RB_BATCHED_BODY_H
#define RB_BATCHED_BODY_H

#include "Deactivable.h"
#include "ManageableByKey.h"
#include "Orderable.h"

namespace BaconBox {
	class BatchedBody : public Deactivable, public ManageableByKey, public Orderable {
	public:
		/**
		 * Default constructor.
		 */
		BatchedBody();

		/**
		 * Copy constructor.
		 * @param src BatchedBody to make a copy of.
		 */
		BatchedBody(const BatchedBody &src);

		/**
		 * Destructor.
		 */
		virtual ~BatchedBody();

		/**
		 * Assignment operator.
		 * @param src BatchedBody to make a copy of.
		 * @return Reference to the modified BatchedBody.
		 */
		BatchedBody &operator=(const BatchedBody &src);

		/**
		 * Sets the body's z coordinate.
		 * @param newZ New z coordinate. The higher the value closer the body
		 * will be to the camera.
		 * @see BaconBox::Orderable::z
		 */
		void setZ(int newZ);
	};

}

#endif // RB_BATCHED_BODY_H
