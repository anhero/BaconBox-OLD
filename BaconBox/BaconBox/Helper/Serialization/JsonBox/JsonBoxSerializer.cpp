#include "JsonBoxSerializer.h"

#include <JsonBox.h>

#include "Value.h"
#include "Array.h"
#include "Object.h"

namespace BaconBox {
	void valueToJsonBoxValue(const Value &input, JsonBox::Value &output);
	void jsonBoxValueToValue(const JsonBox::Value &input, Value &output);

	JsonBoxSerializer::JsonBoxSerializer(bool newIndent, bool newEscapeSolidus) :
		Serializer(), indent(newIndent), escapeSolidus(newEscapeSolidus) {
	}

	JsonBoxSerializer::JsonBoxSerializer(const JsonBoxSerializer &src) :
		Serializer(src), indent(src.indent), escapeSolidus(src.escapeSolidus) {
	}

	JsonBoxSerializer::~JsonBoxSerializer() {
	}

	JsonBoxSerializer &JsonBoxSerializer::operator=(const JsonBoxSerializer &src) {
		if (this != &src) {
			indent = src.indent;
			escapeSolidus = src.escapeSolidus;
		}

		return *this;
	}

	void JsonBoxSerializer::writeToStream(std::ostream &output, const Value &value) {
		JsonBox::Value tmpValue;
		valueToJsonBoxValue(value, tmpValue);

		tmpValue.writeToStream(output, indent, escapeSolidus);
	}

	bool JsonBoxSerializer::readFromStream(std::istream &input, Value &value) {
		JsonBox::Value tmpValue(input);

		jsonBoxValueToValue(tmpValue, value);

		return true;
	}

	void valueToJsonBoxValue(const Value &input, JsonBox::Value &output) {
		switch (input.getType()) {
		case Value::STRING:
			output.setString(input.getString());
			break;

		case Value::INTEGER:
			output.setInt(input.getInt());
			break;

		case Value::DOUBLE:
			output.setDouble(input.getDouble());
			break;

		case Value::OBJECT:
			for (Object::const_iterator i = input.getObject().begin();
			     i != input.getObject().end(); ++i) {
				valueToJsonBoxValue(i->second, output[i->first]);
			}

			break;

		case Value::ARRAY:
			output.setArray(JsonBox::Array(input.getArray().size()));

			for (Array::size_type i = 0; i < input.getArray().size(); ++i) {
				valueToJsonBoxValue(input.getArray()[i], output[i]);
			}

			break;

		case Value::BOOLEAN:
			output.setBoolean(input.getBool());
			break;

		default:
			output.setNull();
			break;
		}
	}

	void jsonBoxValueToValue(const JsonBox::Value &input, Value &output) {
		switch (input.getType()) {
		case JsonBox::Value::STRING:
			output.setString(input.getString());
			break;

		case JsonBox::Value::INTEGER:
			output.setInt(input.getInt());
			break;

		case JsonBox::Value::DOUBLE:
			output.setDouble(input.getDouble());
			break;

		case JsonBox::Value::OBJECT:
			for (JsonBox::Object::const_iterator i = input.getObject().begin();
			     i != input.getObject().end(); ++i) {
				jsonBoxValueToValue(i->second, output[i->first]);
			}

			break;

		case JsonBox::Value::ARRAY:
			output.setArray(Array(input.getArray().size()));

			for (Array::size_type i = 0; i < input.getArray().size(); ++i) {
				jsonBoxValueToValue(input.getArray()[i], output[i]);
			}

			break;

		case JsonBox::Value::BOOLEAN:
			output.setBool(input.getBoolean());
			break;

		default:
			output.setNull();
			break;
		}
	}

	bool JsonBoxSerializer::isIndent() const {
		return indent;
	}

	void JsonBoxSerializer::setIndent(bool newIndent) {
		indent = newIndent;
	}

	bool JsonBoxSerializer::isEscapeSolidus() const {
		return escapeSolidus;
	}

	void JsonBoxSerializer::setEscapeSolidus(bool newEscapeSolidus) {
		escapeSolidus = newEscapeSolidus;
	}
}
