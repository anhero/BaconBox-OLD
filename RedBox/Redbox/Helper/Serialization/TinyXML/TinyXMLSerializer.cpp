#include "TinyXMLSerializer.h"

#include <tinyxml.h>
#include "Value.h"
#include "Console.h"

namespace RedBox {
	void elementToValue(const TiXmlElement &element, Value &value);

	void valueToElement(const Value &value, TiXmlElement &element);

	void attributeToValue(const TiXmlAttribute &attribute, Value &value);

	void valueToAttribute(const Value &value, TiXmlAttribute &attribute);

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
			valueToXml(value, *root);

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
			// We convert the root element into a value.
			xmlToValue(*root, value);

		} else {
			result = false;
		}

		return result;
	}

	void elementToValue(const TiXmlElement &element, Value &value) {
		// We make sure to set that the value is not an attribute.
		value.setAttribute(false);

		// We first check if we have to make the value an array or an object.
		bool isArray = element.FirstAttribute() != NULL && element.FirstChild() != NULL;

		// We start by converting the attributes.
		const TiXmlAttribute *attribute = element.FirstAttribute();

		while (attribute) {
			attributeToValue(*attribute, value[attribute->Name()]);
			attribute = attribute->Next();
		}
	}

	void valueToElement(const Value &value, TiXmlElement &element) {
	}

	void attributeToValue(const TiXmlAttribute &attribute, Value &value) {
		value.setAttribute(true);
	}

	void valueToAttribute(const Value &value, TiXmlAttribute &attribute) {
	}
}
