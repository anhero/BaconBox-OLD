/**
 * @file
 * @ingroup Serialization
 */
#ifndef RB_ARRAY_H
#define RB_ARRAY_H

#include <cstddef>

namespace BaconBox {
	class Value;

	/**
	 * Represents a dynamic array containing Values used for serialization and
	 * deserialization.
	 * @see BaconBox::Value
	 */
	class Array {
	public:
		/// Type used to keep track of the array's size.
		typedef size_t SizeType;

		/**
		 * Default constructor. Initializes an empty array.
		 */
		Array();

		/**
		 * Parameterized constructor.
		 * @param startingSize Starting size of the dynamic array. All values
		 * are initialized with their default constructor.
		 */
		Array(SizeType startingSize);

		/**
		 * Parameterized constructor.
		 * @param startingSize Starting size of the dynamic array. All values
		 * are initialized with the given default value.
		 * @param defaultValue Default value to use to initialize the values.
		 */
		Array(SizeType startingSize, const Value &defaultValue);

		/**
		 * Copy constructor.
		 * @param src Dynamic array to make a copy of.
		 */
		Array(const Array &src);

		/**
		 * Destructor. Unallocates the dynamic memory used by the array if
		 * necessary.
		 */
		~Array();

		/**
		 * Assignment operator overloading.
		 * @param src Array to copy.
		 * @return Reference to the modified instance.
		 */
		Array &operator=(const Array &src);

		/**
		 * Gets the value specified at the given index. No bound checking is
		 * done.
		 * @param index Index of the value to get.
		 * @return Reference to the Value at the given index.
		 */
		Value &operator[](SizeType index);

		/**
		 * Gets the value specified at the given index. No bound checking is
		 * done.
		 * @param index Index of the value to get.
		 * @return Reference to the Value at the given index.
		 */
		const Value &operator[](SizeType index) const;

		/**
		 * Gets the number of values in the array.
		 * @return Number of values in the dynamic array.
		 */
		SizeType getSize() const;

		/**
		 * Resizes the dynamic array. If the new size is bigger, the values in
		 * the existing array are kept and stay at the start of the array and
		 * the new values are initialized with their default constructor. If the
		 * new size is smaller, the values at the end are truncated.
		 * @param newSize New size of the dynamic array.
		 */
		void setSize(SizeType newSize);

		/**
		 * Resizes the dynamic array. If the new size is bigger, the values in
		 * the existing array are kept and stay at the start of the array and
		 * the new values are initialized with the given default value. If the
		 * new size is smaller, the values at the end are truncated and the
		 * given default value is ignored.
		 * @param newSize New size of the dynamic array.
		 * @param defaultValue Default value to set to the new elements at the
		 * end of the array if the new size is bigger. Ignored if the new size
		 * is smaller.
		 */
		void setSize(SizeType newSize, const Value &defaultValue);
	private:
		/// Pointer to the dynamic array of values.
		Value *values;

		/// Number of values in the dynamic array.
		SizeType nbValues;
	};
}

#endif
