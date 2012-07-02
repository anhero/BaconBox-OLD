/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SHAPABLE_H
#define RB_SHAPABLE_H

#include "BaconBox/Display/VertexArray.h"
#include "BaconBox/Helper/IsBaseOf.h"
#include "BaconBox/Helper/StaticAssert.h"

namespace BaconBox {
	/**
	 * All bodies who contain vertices are derived from this class.
	 * @ingroup Display
	 */
	template <typename T>
	class Shapable {
	public:
		/**
		 * Default constructor.
		 */
		Shapable() : vertices() {
		}

		explicit Shapable(const T &newVertices) : vertices(newVertices) {
		}

		/**
		 * Copy constructor.
		 * @param src Shapable to make a copy of.
		 */
		Shapable(const Shapable<T> &src) : vertices(src.vertices) {
		}

		/**
		 * Destructor.
		 */
		virtual ~Shapable() {
		}

		/**
		 * Assignment operator.
		 * @param src Shapable to make a copy of.
		 * @return Reference to the modified Shapable.
		 */
		Shapable<T> &operator=(const Shapable<T> &src) {
			if (this != &src) {
				vertices = src.vertices;
			}

			return *this;
		}

		/**
		 * Gets the array of vertices.
		 * @return Array containing the body's vertices.
		 * @see BaconBox::Shapable<T>::vertices
		 */
		T &getVertices() {
			return vertices;
		}

		/**
		 * Gets the array of vertices.
		 * @return Array containing the body's vertices.
		 * @see BaconBox::Shapable<T>::vertices
		 */
		const T &getVertices() const {
			return vertices;
		}
	private:
		/// Makes sure we are containing an array of vertices.
		typedef typename StaticAssert<IsBaseOf<VertexArray, T>::RESULT>::Result IsVertexArray;

		/// Array containing the body's vertices.
		T vertices;
	};

}

#endif
