/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_CARRAY_H
#define RB_CARRAY_H

namespace RedBox{
	/** 
	 * Struct used to easily pass around C arrays. It contain a pointer to the first 
     * element of the array and the number of element in the array.
     * @ingroup Helper
     */
	template <typename T>
    struct CArray{

		CArray() : array(NULL), elementCount(0) {
		}
        
        CArray(T* newArray, int newElementCount): array(newArray),
		    elementCount(newElementCount) {
		}

		CArray(const CArray<T>& src) : array(src.array),
		    elementCount(src.elementCount) {
		}

		/// Pointer to the first element (C array)
        T* array;

        /// Number of element in the C array
        unsigned int elementCount;
	};
}

#endif
