/**
 * @file
 */
#ifndef RB_RESOURCE_POINTER_H
#define RB_RESOURCE_POINTER_H

#include <string>

namespace BaconBox {
	/**
	 * Represents a pointer to a resource. All bodies and graphics use this
	 * to initialize from a string or directly from the pointer. To be used
	 * with typedef for more ease.
	 * @tparam T Type to use as the pointer.
	 * @tparam POINTER Pointer to the function to use to find the pointer using
	 * a std::string.
	 * @see BaconBox::ResourceManager
	 */
	template <typename T, T * (*POINTER)(const std::string &)>
	struct ResourcePointer {
		/**
		 * Default constructor.
		 */
		ResourcePointer() : pointer(NULL) {
		}

		/**
		 * Parameterized constructor.
		 * @param newPointer Constructs the resource pointer directly from
		 * the received pointer.
		 * @see BaconBox::ResourcePointer::pointer
		 */
		ResourcePointer(T *newPointer) : pointer(newPointer) {
		}

		/**
		 * Parameterized constructor.
		 * @param newKey Key to use to get the pointer to the resource.
		 * @see BaconBox::ResourcePointer::pointer
		 */
		ResourcePointer(const std::string &newKey) : pointer((*POINTER)(newKey)) {
		}

		/**
		 * Parameterized constructor.
		 * @param newKey Key to use to get the pointer to the resource.
		 * @see BaconBox::ResourcePointer::pointer
		 */
		ResourcePointer(const char *newKey) : pointer((*POINTER)(std::string(newKey))) {
		}

		/**
		 * Copy constructor.
		 * @param src ResourcePoiner to make a copy of.
		 */
		ResourcePointer(const ResourcePointer<T, POINTER> &src) :
			pointer(src.pointer) {
		}

		/**
		 * Assignment operator.
		 * @param src ResourcePoiner to make a copy of.
		 * @return Reference to the modified ResourcePoiner.
		 */
		ResourcePointer<T, POINTER> &operator=(const ResourcePointer<T, POINTER> &src) {
			if (this != &src) {
				pointer = src.pointer;
			}

			return *this;
		}

		/// Pointer to the resource.
		T *pointer;
	};

}

#endif // RB_RESOURCE_POINTER_H
