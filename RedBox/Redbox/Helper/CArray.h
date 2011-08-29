/**
 * @file
 * @ingroup Group
 */

#ifndef RB_CARRAY_H
#define RB_CARRAY_H

namespace RedBox{
	/** 
	 * Struct used to easily pass around C arrays. It contain a pointer to the first 
     * element of the array and the number of element in the array.
     * @ingroup Group
     */
	template <typename T>
    struct CArray{
        
        CArray(T * array, int elementCount): array(array), elementCount(elementCount){}
        ///Number of element in the C array
        unsigned int elementCount;
        
        ///Pointer to the first element (C array)
        T * array;
	};
}

#endif
