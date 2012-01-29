/**
 * @file
 * @ingroup Serialization
 */
#ifndef RB_VALUE_H
#define RB_VALUE_H

#include <iostream>

#include "Object.h"
#include "Array.h"

namespace RedBox {
	class Serializer;

	/**
	 * Represents a serializable value. Can be a string, an integer, a floating
	 * point number, an object, an array, a boolean value or a null value. To
	 * put it simply, it acts a lot like a variant. Objects are actually a map
	 * of strings and values while an array is a deque of values.
	 * @see RedBox::Array
	 * @see RedBox::Object
	 * @ingroup Serialization
	 */
	class Value {
	public:
		/**
		 * Represents the different types a value can be. A value can only be
		 * one of these types at a time.
		 */
		enum Type {
		    STRING,
		    INTEGER,
		    DOUBLE,
		    OBJECT,
		    ARRAY,
		    BOOLEAN,
		    NULL_VALUE
		};

		/**
		 * Default constructor. Sets the value as a null value.
		 */
		Value();

		/**
		 * Constructs the value from a string.
		 * @param newString String to use as the value.
		 */
		Value(const std::string &newString);

		/**
		 * Constructs the value from a C-style string.
		 * @param newCString C-style string to use as the value.
		 */
		Value(const char *newCString);

		/**
		 * Constructs the value from an integer.
		 * @param newInt Integer to use as the value.
		 */
		Value(int newInt);

		/**
		 * Constructs the value from a double.
		 * @param newDouble Double to use as the value.
		 */
		Value(double newDouble);

		/**
		 * Constructs the value from an object.
		 * @param newObject Object to use as the value.
		 */
		Value(const Object &newObject);

		/**
		 * Constructs the value from an array.
		 * @param newArray Array to use as the value.
		 */
		Value(const Array &newArray);

		/**
		 * Constructs the value from a boolean.
		 * @param newBool Boolean to use as the value.
		 */
		Value(bool newBool);

		/**
		 * Copy constructor.
		 * @param src Value to make a copy of.
		 */
		Value(const Value &src);

		/**
		 * Destructor. Frees up the memory used by the value's allocated
		 * pointer.
		 */
		~Value();

		/**
		 * Assignment operator overload.
		 * @param src Value to copy.
		 * @return Reference to the modified value.
		 */
		Value &operator=(const Value &src);

		/**
		 * Bracket operator overload. If the value doesn't represent an object,
		 * it is changed to do so and accesses the object's member value. If
		 * the object's member doesn't exist, it is created.
		 * @param key Key identifier of the object's value to get.
		 * @return Reference to the object's member's value.
		 */
		Value &operator[](const Object::key_type &key);

		/**
		 * Bracket operator overload. If the value doesn't represent an object,
		 * it is changed to do so and accesses the object's member value. If
		 * the object's member doesn't exist, it is created.
		 * @param key Key identifier of the object's value to get.
		 * @return Reference to the object's member's value.
		 */
		Value &operator[](const Array::size_type index);

		/**
		 * Gets the value's type.
		 * @return Value's type, does not return Type::UNKOWN, would return
		 * NULL_VALUE if no type has been given to the value yet.
		 * @see RedBox::Value::Type
		 */
		Type getType() const;

		/**
		 * Checks if the value is a string.
		 * @return True if the value contains a string, false if not.
		 */
		bool isString() const;

		/**
		 * Checks if the value can be a string.
		 * @return True if the value is either a string, an integer or a double.
		 */
		bool isStringable() const;

		/**
		 * Checks if the value is an integer.
		 * @return True if the value contains an integer, false if not.
		 */
		bool isInteger() const;

		/**
		 * Checks if the value is a double.
		 * @return True if the value contains a double, false if not.
		 */
		bool isDouble() const;

		/**
		 * Checks if the value is either an integer or a double.
		 * @return True if the value contains a double or an integer, false if
		 * not.
		 */
		bool isNumeric() const;

		/**
		 * Checks if the value is an object.
		 * @return True if the value contains an object, false if not.
		 */
		bool isObject() const;

		/**
		 * Checks if the value is an array.
		 * @return True if the value contains an array, false if not.
		 */
		bool isArray() const;

		/**
		 * Checks if the value is a boolean.
		 * @return True if the value contains a boolean, false if not.
		 */
		bool isBoolean() const;

		/**
		 * Checks if the value is null.
		 * @return True if the value contains nothing.
		 */
		bool isNull() const;

		/**
		 * Gets the value's string value.
		 * @return Value's string value, or an empty string if the value doesn't
		 * contain a string.
		 */
		const std::string &getString() const;

		/**
		 * Gets the value's string value or converts its numeric value to a
		 * string.
		 * @return Value's string value. If the value contains an integer or a
		 * double, converts it to a string and returns the result.
		 */
		const std::string getToString() const;

		/**
		 * Sets the value as a string.
		 * @param newString New string value that the Value will contain. If the
		 * value's type is changed if necessary to contain the integer.
		 */
		void setString(const std::string &newString);

		/**
		 * Gets the value's integer value.
		 * @return Value's integer value, or the double value casted to an
		 * integer if the value contains a double. 0 if the value doesn't
		 * contain a numeric value.
		 */
		int getInt() const;

		/**
		 * Sets the value as an integer.
		 * @param newInt New integer value that the Value will contain. The
		 * value's type is changed if necessary to contain the integer.
		 */
		void setInt(int newInt);

		/**
		 * Gets the value's double value.
		 * @return Value's double value, or the integer value casted to a double
		 * if the value contains an integer. 0.0 if the value doesn't contain a
		 * numeric value.
		 */
		double getDouble() const;

		/**
		 * Sets the value as a double.
		 * @param newDouble New double value that the Value will contain. The
		 * value's type is changed if necessary to contain the double.
		 */
		void setDouble(double newDouble);

		/**
		 * Gets the value's object value.
		 * @return Value's object value, or an empty object if the value doesn't
		 * contain an object.
		 */
		const Object &getObject() const;

		/**
		 * Sets the value as a JSON object.
		 * @param newObject New object value that the Value will contain. The
		 * value's type is changed if necessary to contain the object.
		 */
		void setObject(const Object &newObject);

		/**
		 * Gets the value's array value.
		 * @return Value's array value, or an empty Array if the value doesn't
		 * contain an array.
		 */
		const Array &getArray() const;

		/**
		 * Sets the value as a JSON array.
		 * @param newArray New array value that the Value will contain. The
		 * value's type is changed if necessary to contain the array.
		 */
		void setArray(const Array &newArray);

		/**
		 * Resizes the array. If it isn't an array, it will change the value to
		 * be an array.
		 * @param newSize New size of the array.
		 * @param defaultValue If the new size is bigger, this value will be
		 * used as the value to insert.
		 */
		void resizeArray(Array::size_type newSize,
						 const Value defaultValue = Value());

		/**
		 * Adds a value to the end of the array. If the value is not an array,
		 * it will change to value to an array that will contain one value.
		 * @param newValue New value to insert.
		 */
		void pushBackArray(const Value &newValue = Value());

		/**
		 * Gets the value's boolean value.
		 * @return Value's boolean value, or false if the value doesn't contain
		 * a boolean.
		 */
		bool getBool() const;

		/**
		 * Sets the value as a boolean.
		 * @param newBoolean New boolean value that the Value will contain. The
		 * value's type is changed if necessary to contain the boolean.
		 */
		void setBool(bool newBool);

		/**
		 * Sets the value as a null value.
		 */
		void setNull();

		/**
		 * Checks wether or not the value is an attribute. Used mainly by XML
		 * serializers. Ignored by the JSON serializers.
		 * @return True if the value is an attribute.
		 * @see RedBox::Value::attribute
		 */
		bool isAttribute() const;

		/**
		 * Sets wether or not the value is an attribute. Useful mainly for the
		 * XML serializers.
		 * @param newAttribute Set this parameter to true to make the value an
		 * attribute. Will only be set correctly if the value is neither an
		 * array, a null value nor an object.
		 * @see RedBox::Value::attribute
		 */
		void setAttribute(bool newAttribute);

		/**
		 * Gets the name of the value.
		 * @return Name of the value. If it doesn't have one, the string will be
		 * empty.
		 * @see RedBox::Value::name
		 */
		const std::string &getName() const;

		/**
		 * Sets the name of the value.
		 * @param newName New name of the value.
		 * @see RedBox::Value::name
		 */
		void setName(const std::string &newName);
	private:
		/**
		 * Union used to contain the pointer to the value's data.
		 */
		union ValueDataPointer {
			std::string *stringValue;
			int *intValue;
			double *doubleValue;
			Object *objectValue;
			Array *arrayValue;
			bool *boolValue;

			/**
			 * Default constructor. Puts the pointers at NULL.
			 */
			ValueDataPointer();

			/**
			 * Parameterized constructor.
			 * @param newConstStringValue Pointer to set to the string pointer.
			 */
			ValueDataPointer(std::string *newStringValue);

			/**
			 * Parameterized constructor.
			 * @param newConstIntValue Pointer to set to the int pointer.
			 */
			ValueDataPointer(int *newIntValue);

			/**
			 * Parameterized constructor.
			 * @param newConstDoubleValue Pointer to set to the double pointer.
			 */
			ValueDataPointer(double *newDoubleValue);

			/**
			 * Parameterized constructor.
			 * @param newConstObjectValue Pointer to set to the object pointer.
			 */
			ValueDataPointer(Object *newObjectValue);

			/**
			 * Parameterized constructor.
			 * @param newConstArrayValue Pointer to set to the array pointer.
			 */
			ValueDataPointer(Array *newArrayValue);

			/**
			 * Parameterized constructor.
			 * @param newConstBoolValue Pointer to set to the bool pointer.
			 */
			ValueDataPointer(bool *newBoolValue);
		};


		/**
		 * Empty string returned by getString() when the value doesn't contain a
		 * string.
		 * @see RedBox::Value::getString
		 */
		static const std::string EMPTY_STRING;

		/**
		 * Default int value returned by getInt() when the value doesn't contain
		 * an integer.
		 * @see RedBox::Value::getInt
		 */
		static const int EMPTY_INT = 0;

		/**
		 * Default double value returned by getDouble() when the value doesn't
		 * contain a double.
		 * @see RedBox::Value::getDouble
		 */
		static const double EMPTY_DOUBLE;

		/**
		 * Default empty object value returned by getObject() when the value
		 * doesn't contain an object.
		 * @see RedBox::Value::getObject
		 */
		static const Object EMPTY_OBJECT;

		/**
		 * Default empty array value returned by getArray() when the value
		 * doesn't contain an array.
		 * @see RedBox::Value::getArray
		 */
		static const Array EMPTY_ARRAY;

		/**
		 * Default boolean value returned by getBoolean() when the value doesn't
		 * contain a boolean.
		 * @see RedBox::Value::getBoolean
		 */
		static const bool EMPTY_BOOL = false;

		/**
		 * Frees up the dynamic memory allocated by the value.
		 */
		void clear();

		/// Type of data the value contains.
		Type type;

		/// Pointer to the Value's data.
		ValueDataPointer data;

		/**
		 * True if the value is an attribute (used by XML serialiers). The value
		 * cannot be an array or an object if this member is set to true. False
		 * by default.
		 */
		bool attribute;

		/**
		 * Name of the value. Usually the name of the type. Used by some
		 * serialization formats (like XML) for the root value. Values that are
		 * never a root node do not need to set this.
		 */
		std::string name;
	};

	std::ostream &operator<<(std::ostream &output, const Value &value);
}

#endif
