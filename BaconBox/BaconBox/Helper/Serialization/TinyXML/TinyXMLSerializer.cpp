#include "BaconBox/Helper/Serialization/TinyXML/TinyXMLSerializer.h"

#include <cstring>

#include <set>
#include <sstream>
#include <algorithm>
#include <string>
#include <functional>
#include <locale>

#include <tinyxml.h>
#include "BaconBox/Helper/Serialization/Value.h"
#include "BaconBox/Helper/Serialization/Array.h"
#include "BaconBox/Helper/Serialization/Object.h"
#include "BaconBox/Console.h"

namespace BaconBox {
	const std::string FALSE_STRING = std::string("false");
	const std::string TRUE_STRING = std::string("true");

	void elementToValue(const TiXmlElement &element, Value &value);

	void valueToElement(const Value &value, TiXmlElement &element);

	void attributeToValue(const TiXmlAttribute &attribute, Value &value);

	void valueToAttribute(const Value &value, TiXmlAttribute &attribute);

	void textToValue(const std::string &text, Value &value);

	void arrayToElement(const Array &array, TiXmlElement &element);

	void objectToElement(const Object &object, TiXmlElement &element);

	TinyXMLSerializer::TinyXMLSerializer() : Serializer() {
	}

	TinyXMLSerializer::TinyXMLSerializer(const TinyXMLSerializer &src) :
		Serializer(src) {
	}

	TinyXMLSerializer::~TinyXMLSerializer() {
	}

	TinyXMLSerializer &TinyXMLSerializer::operator=(const TinyXMLSerializer &) {
		return *this;
	}

	void TinyXMLSerializer::writeToStream(std::ostream &output,
	                                      const Value &value) {
		// We make sure the root element as a name.
		if (!value.getName().empty()) {
			// We create the document.
			TiXmlDocument doc;
			doc.LinkEndChild(new TiXmlDeclaration("1.0", "UTF-8", ""));

			// We create the root element.
			TiXmlElement *root = new TiXmlElement(value.getName());

			// We convert the value into the root element.
			valueToElement(value, *root);
			// We add the root element to the document.
			doc.LinkEndChild(root);

			// We write the document to the output stream.
			output << doc;

		} else {
			Console::println("Failed to write the value to XML because the root value doesn't have a name.");
		}
	}

	bool TinyXMLSerializer::readFromStream(std::istream &input, Value &value) {
		bool result = true;
		// We initialize the document.
		TiXmlDocument doc;
		// We read the document from the stream.
		input >> doc;
		// We get the root element.
		TiXmlElement *root = doc.RootElement();

		// We make sure the document has a root element.
		if (root) {
			value.setName(root->Value());
			// We convert the root element into a value.
			elementToValue(*root, value);

		} else {
			result = false;
		}

		return result;
	}

	void elementToValue(const TiXmlElement &element, Value &value) {
		// We make sure to set that the value is not an attribute.
		value.setAttribute(false);

		// We check if we have to make an array out of the value.
		bool isArray = false;
		const TiXmlNode *child = NULL;

		while (!isArray && (child = element.IterateChildren(child))) {
			if (child->ToText()) {
				isArray = true;

			}
		}


		const TiXmlAttribute *attribute = element.FirstAttribute();

		if (isArray) {
			// We start by converting the attributes.
			while (attribute) {
				value.pushBackArray();
				attributeToValue(*attribute, value[value.getArray().size() - 1][attribute->Name()]);
				attribute = attribute->Next();
			}

			// We then convert the child elements.
			child = NULL;

			while ((child = element.IterateChildren(child))) {
				if (child->ToElement()) {
					value.pushBackArray();
					elementToValue(*child->ToElement(), value[value.getArray().size() - 1][child->ToElement()->Value()]);

				} else if (child->ToText()) {
					value.pushBackArray();
					textToValue(child->ToText()->Value(), value[value.getArray().size() - 1]);
				}
			}

		} else {
			// We start by converting the attributes.
			while (attribute) {
				attributeToValue(*attribute, value[attribute->Name()]);
				attribute = attribute->Next();
			}

			// We then convert the child elements.
			child = NULL;
			Object::const_iterator itFound;

			while ((child = element.IterateChildren(child))) {
				// We only read the child elements (we already know there are no
				// text children.
				if (child->ToElement()) {
					// We check if the value already contains a member with
					// that name.
					itFound = value.getObject().find(child->ToElement()->Value());

					if (itFound != value.getObject().end()) {
						Value &found = value[child->ToElement()->Value()];

						if (!found.isArray()) {
							Value tmp(found);
							found.setArray(Array(1, tmp));
							found.setArrayOfSameTypes(true);
						}

						found.pushBackArray();
						elementToValue(*child->ToElement(), found[found.getArray().size() - 1]);

					} else {
						// If it's a new member name, we simply add it to the value.
						elementToValue(*child->ToElement(), value[child->ToElement()->Value()]);
					}
				}
			}
		}
	}

	void valueToElement(const Value &value, TiXmlElement &element) {
		// If the value to convert is an array.
		if (value.isArray()) {
			arrayToElement(value.getArray(), element);

			// If the value to convert is an object.

		} else if (value.isObject()) {
			objectToElement(value.getObject(), element);

			// If it's a numeric, a string, a boolean or a null value.

		} else {
			TiXmlText *newChildText = new TiXmlText(value.getToString());
			element.LinkEndChild(newChildText);
		}
	}

	void arrayToElement(const Array &array, TiXmlElement &element) {
		TiXmlText *newChildText;

		// We check each element of the array.
		for (Array::size_type i = 0; i < array.size(); ++i) {
			// If the element in the array is an object.
			if (array[i].isObject()) {
				objectToElement(array[i].getObject(), element);

			} else if (array[i].isArray()) {
				arrayToElement(array[i].getArray(), element);

			} else if (array[i].isStringable()) {
				newChildText = new TiXmlText(array[i].getToString());
				element.LinkEndChild(newChildText);
			}
		}
	}

	void objectToElement(const Object &object, TiXmlElement &element) {
		TiXmlElement *newChild;

		// We check each values in the object.
		for (Object::const_iterator i = object.begin();
		     i != object.end(); ++i) {
			// If the value is an attribute.
			if (i->second.isAttribute()) {
				// We check if it can be converted to a string, if
				// not, we'll make it a normal element.
				if (i->second.isStringable()) {
					// We set the attribute.
					element.SetAttribute(i->first, i->second.getToString());

				} else {
					// We create a new element and add it to the
					// current element.
					newChild = new TiXmlElement(i->first);
					valueToElement(i->second, *newChild);
					element.LinkEndChild(newChild);
				}

			} else {
				if (i->second.isArrayOfSameTypes()) {
					const Array &tmpArray = i->second.getArray();

					for (Array::size_type j = 0; j < tmpArray.size(); ++j) {
						newChild = new TiXmlElement(i->first);
						valueToElement(tmpArray[j], *newChild);
						element.LinkEndChild(newChild);
					}

				} else {
					// We create a new element and add it to the current
					// element.
					newChild = new TiXmlElement(i->first);
					valueToElement(i->second, *newChild);
					element.LinkEndChild(newChild);
				}
			}
		}
	}

	void attributeToValue(const TiXmlAttribute &attribute, Value &value) {
		value.setAttribute(true);
		textToValue(attribute.Value(), value);
	}

	void valueToAttribute(const Value &value, TiXmlAttribute &attribute) {
		if (value.isStringable()) {
			attribute.SetValue(value.getToString());
		}
	}

	void textToValue(const std::string &text, Value &value) {
		if (text.empty()) {
			// If the text is empty, it's a null value.
			value.setNull();

		} else {
			std::istringstream ss(text);

			int intValue;

			// We check if the value is an integer or not.
			if (!(ss >> intValue)) {
				// It's not an integer, so let's check if it's a double.
				double doubleValue;

				ss.str(text);

				if (!(ss >> doubleValue)) {
					// It's neither an integer nor a floating point number, so let's
					// check if it's a boolean value.
					std::string tmpString(text);
					std::transform(tmpString.begin(),
					               tmpString.end(),
					               tmpString.begin(),
					               ::tolower);
					bool isBoolean = true;
					std::string::const_iterator i = tmpString.begin();
					std::locale loc;

					while (isBoolean && i != tmpString.end()) {
						// There can be white spaces before and after the
						// "false" or "true" values.
						if (!std::isspace(*i, loc)) {
							// If we've already found the bool value and we've
							// found another non-whitespace character, it means
							// it's only a string that starts with the "false"
							// or "true" value.
							if (value.isBoolean()) {
								isBoolean = false;

							} else {
								// We check that it contains the "false" or
								// "true" value.
								if (std::equal(FALSE_STRING.begin(), FALSE_STRING.end(), i)) {
									value.setBool(false);
									std::advance(i, FALSE_STRING.size());

								} else if (std::equal(TRUE_STRING.begin(), TRUE_STRING.end(), i)) {
									value.setBool(true);
									std::advance(i, TRUE_STRING.size());

								} else {
									// If not, it means it's not a boolean
									// either.
									isBoolean = false;
								}
							}

						} else {
							++i;
						}
					}

					// If it's not a boolean, it can only be a string.
					if (!isBoolean) {
						value.setString(text);
					}

				} else {
					value.setDouble(doubleValue);
				}

			} else {
				// No errors? Therefore, it's an integer.
				value.setInt(intValue);
			}
		}
	}
}
