#include "Value.h"

#include <sstream>

#include "DefaultSerializer.h"
#include "Serializer.h"

namespace RedBox {
	const std::string Value::EMPTY_STRING = std::string();
	const double Value::EMPTY_DOUBLE = 0.0;
	const Object Value::EMPTY_OBJECT = Object();
	const Array Value::EMPTY_ARRAY = Array();

	Value::Value() : type(NULL_VALUE), data(), attribute(false), name(),
		arrayOfSameTypes(false) {
	}

	Value::Value(const std::string &newString) : type(STRING),
		data(new std::string(newString)), attribute(false), name(),
		arrayOfSameTypes(false) {
	}

	Value::Value(const char *newCString) : type(STRING),
		data(new std::string(newCString)), attribute(false), name(),
		arrayOfSameTypes(false) {
	}

	Value::Value(int newInt) : type(INTEGER), data(new int(newInt)),
		attribute(false), name(), arrayOfSameTypes(false) {
	}

	Value::Value(double newDouble) : type(DOUBLE), data(new double(newDouble)),
		attribute(false), name(), arrayOfSameTypes(false) {
	}

	Value::Value(const Object &newObject) : type(OBJECT),
		data(new Object(newObject)), attribute(false), name(),
		arrayOfSameTypes(false) {
	}

	Value::Value(const Array &newArray) : type(ARRAY),
		data(new Array(newArray)), attribute(false), name(),
		arrayOfSameTypes(false) {
	}

	Value::Value(bool newBool) : type(BOOLEAN), data(new bool(newBool)),
		attribute(false), name(), arrayOfSameTypes(false) {
	}

	Value::Value(const Value &src) : type(src.type), data(),
		attribute(src.attribute), name(src.name),
		arrayOfSameTypes(src.arrayOfSameTypes) {
		switch (type) {
		case STRING:
			data.stringValue = new std::string(*src.data.stringValue);
			break;

		case INTEGER:
			data.intValue = new int(*src.data.intValue);
			break;

		case DOUBLE:
			data.doubleValue = new double(*src.data.doubleValue);
			break;

		case OBJECT:
			data.objectValue = new Object(*src.data.objectValue);
			break;

		case ARRAY:
			data.arrayValue = new Array(*src.data.arrayValue);
			break;

		case BOOLEAN:
			data.boolValue = new bool(*src.data.boolValue);
			break;

		default:
			type = NULL_VALUE;
			break;
		}
	}

	Value::~Value() {
		free();
	}

	Value &Value::operator=(const Value &src) {
		if (this != &src) {
			free();
			type = src.type;

			switch (type) {
			case STRING:
				data.stringValue = new std::string(*src.data.stringValue);
				break;

			case INTEGER:
				data.intValue = new int(*src.data.intValue);
				break;

			case DOUBLE:
				data.doubleValue = new double(*src.data.doubleValue);
				break;

			case OBJECT:
				data.objectValue = new Object(*src.data.objectValue);
				break;

			case ARRAY:
				data.arrayValue = new Array(*src.data.arrayValue);
				break;

			case BOOLEAN:
				data.boolValue = new bool(*src.data.boolValue);
				break;

			default:
				type = NULL_VALUE;
				data.stringValue = NULL;
				break;
			}

			attribute = src.attribute;
			name = src.name;
			arrayOfSameTypes = src.arrayOfSameTypes;
		}

		return *this;
	}

	Value &Value::operator[](const Object::key_type &key) {
		if (type != OBJECT) {
			clear();
			type = OBJECT;
			data.objectValue = new Object();
		}

		return (*data.objectValue)[key];
	}

	Value &Value::operator[](Array::size_type index) {
		if (type != ARRAY) {
			clear();
			type = ARRAY;
			data.arrayValue = new Array(index + 1);
		}

		return (*data.arrayValue)[index];
	}

	Value::Type Value::getType() const {
		return type;
	}

	bool Value::isString() const {
		return type == STRING;
	}

	bool Value::isStringable() const {
		return type != ARRAY && type != OBJECT;
	}

	bool Value::isInteger() const {
		return type == INTEGER;
	}

	bool Value::isDouble() const {
		return type == DOUBLE;
	}

	bool Value::isNumeric() const {
		return type == INTEGER || type == DOUBLE;
	}

	bool Value::isObject() const {
		return type == OBJECT;
	}

	bool Value::isArray() const {
		return type == ARRAY;
	}

	bool Value::isBoolean() const {
		return type == BOOLEAN;
	}

	bool Value::isNull() const {
		return type == NULL_VALUE;
	}

	const std::string &Value::getString() const {
		return (type == STRING) ? (*data.stringValue) : (EMPTY_STRING);
	}

	const std::string Value::getToString() const {

		if (type == STRING) {
			return *data.stringValue;

		} else {
			std::stringstream ss;

			switch (type) {
			case INTEGER:
				ss << *data.intValue;
				break;

			case DOUBLE:
				ss << *data.doubleValue;
				break;

			case BOOLEAN:
				ss << ((*data.boolValue) ? ("true") : ("false"));
				break;

			case NULL_VALUE:
				ss << "null";
				break;

			default:
				break;
			}

			return ss.str();
		}
	}

	void Value::setString(std::string const &newString) {
		if (type == STRING) {
			*data.stringValue = newString;

		} else {
			clear();
			type = STRING;
			data.stringValue = new std::string(newString);
		}
	}

	int Value::getInt() const {
		return (type == INTEGER) ? (*data.intValue) : ((type == DOUBLE) ? (static_cast<int>(*data.doubleValue)) : (EMPTY_INT));
	}

	void Value::setInt(int newInt) {
		if (type == INTEGER) {
			*data.intValue = newInt;

		} else {
			clear();
			type = INTEGER;
			data.intValue = new int(newInt);
		}
	}

	double Value::getDouble() const {
		return (type == DOUBLE) ? (*data.doubleValue) : ((type == INTEGER) ? (static_cast<double>(*data.intValue)) : (EMPTY_DOUBLE));
	}

	void Value::setDouble(double newDouble) {
		if (type == DOUBLE) {
			*data.doubleValue = newDouble;

		} else {
			clear();
			type = DOUBLE;
			data.doubleValue = new double(newDouble);
		}
	}

	const Object &Value::getObject() const {
		return (type == OBJECT) ? (*data.objectValue) : (EMPTY_OBJECT);
	}

	void Value::setObject(const Object &newObject) {
		if (type == OBJECT) {
			*data.objectValue = newObject;

		} else {
			clear();
			type = OBJECT;
			data.objectValue = new Object(newObject);
		}
	}

	const Array &Value::getArray() const {
		return (type == ARRAY) ? (*data.arrayValue) : (EMPTY_ARRAY);
	}

	void Value::setArray(const Array &newArray) {
		if (type == ARRAY) {
			*data.arrayValue = newArray;

		} else {
			free();
			type = ARRAY;
			data.arrayValue = new Array(newArray);
		}
	}

	void Value::resizeArray(Array::size_type newSize,
	                        const Value defaultValue) {
		if (type == ARRAY) {
			data.arrayValue->resize(newSize, defaultValue);

		} else {
			clear();
			type = ARRAY;
			data.arrayValue = new Array(newSize, defaultValue);
		}
	}

	void Value::pushBackArray(const Value &newValue) {
		if (type == ARRAY) {
			data.arrayValue->push_back(newValue);

		} else {
			clear();
			type = ARRAY;
			data.arrayValue = new Array(1, newValue);
		}
	}

	bool Value::getBool() const {
		return (type == BOOLEAN) ? (*data.boolValue) : (EMPTY_BOOL);
	}

	void Value::setBool(bool newBool) {
		if (type == BOOLEAN) {
			*data.boolValue = newBool;

		} else {
			clear();
			type = BOOLEAN;
			data.boolValue = new bool(newBool);
		}
	}

	void Value::setNull() {
		clear();
		type = NULL_VALUE;
		data.stringValue = NULL;
	}

	bool Value::isAttribute() const {
		return attribute;
	}

	void Value::setAttribute(bool newAttribute) {
		attribute = isStringable() && newAttribute;
	}

	const std::string &Value::getName() const {
		return name;
	}

	void Value::setName(const std::string &newName) {
		name = newName;
	}

	bool Value::isArrayOfSameTypes() const {
		return arrayOfSameTypes;
	}

	void Value::setArrayOfSameTypes(bool newArrayOfSameTypes) {
		arrayOfSameTypes = (type == ARRAY) && newArrayOfSameTypes;
	}

	Value::ValueDataPointer::ValueDataPointer(): stringValue(NULL) {
	}

	Value::ValueDataPointer::ValueDataPointer(std::string *newStringValue) :
		stringValue(newStringValue) {
	}

	Value::ValueDataPointer::ValueDataPointer(int *newIntValue) :
		intValue(newIntValue) {
	}

	Value::ValueDataPointer::ValueDataPointer(double *newDoubleValue) :
		doubleValue(newDoubleValue) {
	}

	Value::ValueDataPointer::ValueDataPointer(Object *newObjectValue) :
		objectValue(newObjectValue) {
	}

	Value::ValueDataPointer::ValueDataPointer(Array *newArrayValue) :
		arrayValue(newArrayValue) {
	}

	Value::ValueDataPointer::ValueDataPointer(bool *newBoolValue) :
		boolValue(newBoolValue) {
	}

	void Value::clear() {
		arrayOfSameTypes = false;
		free();
	}

	void Value::free() {
		switch (type) {
		case STRING:
			delete data.stringValue;
			break;

		case INTEGER:
			delete data.intValue;
			break;

		case DOUBLE:
			delete data.doubleValue;
			break;

		case OBJECT:
			delete data.objectValue;
			break;

		case ARRAY:
			delete data.arrayValue;
			break;

		case BOOLEAN:
			delete data.boolValue;
			break;

		default:
			break;
		}
	}

	std::ostream &operator<<(std::ostream &output, const Value &value) {
		DefaultSerializer::getDefaultSerializer().writeToStream(output, value);
		return output;
	}
}
