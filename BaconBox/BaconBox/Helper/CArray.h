/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_CARRAY_H
#define RB_CARRAY_H

namespace BaconBox{
	/** 
	 * Struct used to easily pass around C arrays. It contain a pointer to the first 
     * element of the array and the number of element in the array.
     * @ingroup Helper
     */
	template <typename T>
    class CArray{
        
        template <typename U>  friend std::ostream& operator<<(std::ostream& output,
		                                const CArray<U>& aCArray);
        public:

		CArray() : array(NULL), elementCount(0) {
		}
        
        CArray(T* newArray, int newElementCount): array(newArray),
		    elementCount(newElementCount) {
		}

		CArray(const CArray<T>& src) : array(src.array),
		    elementCount(src.elementCount) {
		}
        
        T & operator[](unsigned int iterator) const{ return array[iterator];}

		/// Pointer to the first element (C array)
        T* array;

        /// Number of element in the C array
        unsigned int elementCount;
	};
    

    template <typename U>
    std::ostream& operator<<(std::ostream& output, const CArray<U>& aCArray) {
		output << "{CArray: [";
        
        for(unsigned int i = 0; i < aCArray.elementCount; i++) {
			if(i != 0) {
				output << ", ";
			}
            
			output << aCArray[i];
		}
        
		output << "]}";
		return output;
	}
}

#endif
