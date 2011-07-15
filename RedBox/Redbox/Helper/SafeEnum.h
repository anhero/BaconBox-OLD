/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_SAFE_ENUM_H
#define RB_SAFE_ENUM_H

namespace RedBox {

	/**
	 * Template for type safe enumerators. To define a type safe enumerator, do
	 * it like this:<br>
	 * <code>
	 * struct EnumNameDef {<br>
	 * &nbsp;&nbsp;&nbsp;&nbsp;enum type {<br>
	 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;FIRST,<br>
	 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;SECOND,<br>
	 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;THIRD<br>
	 * &nbsp;&nbsp;&nbsp;&nbsp;};<br>
	 * }<br>
	 * typedef SafeEnum<EnumNameDef> EnumName;<br>
	 * </code>
	 * Then, when you want to use it, you'd use it like this:<br>
	 * <code>
	 * EnumName myEnumValue = EnumName::FIRST;<br>
	 * myEnumValue = EnumName::SECOND;<br>
	 * // ...
	 * </code>
	 */
	template<typename T, typename U = typename T::type>
	class SafeEnum : public T {
	private:
		typedef typename T::type type;
	public:
		/**
		 * Parameterized constructor.
		 * @param newValue Starting value.
		 */
		SafeEnum(type newValue) : value(newValue) {
		}

		/**
		 * Gets the underling real value.
		 * @return Enum value that the type safe enumerator is containing.
		 */
		U underlying() const {
			return value;
		}

		bool operator==(const SafeEnum<T, U>& other) const {
			return value == other.value;
		}

		bool operator!=(const SafeEnum<T, U>& other) const {
			return value != other.value;
		}

		bool operator<(const SafeEnum<T, U>& other) const {
			return value < other.value;
		}

		bool operator<=(const SafeEnum<T, U>& other) const {
			return value <= other.value;
		}

		bool operator>(const SafeEnum<T, U>& other) const {
			return value >  other.value;
		}

		bool operator>=(const SafeEnum<T, U>& other) const {
			return value >= other.value;
		}
	private:
		U value;
	};

}

#endif
