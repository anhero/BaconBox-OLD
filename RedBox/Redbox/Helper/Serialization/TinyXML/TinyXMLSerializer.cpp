#include "TinyXMLSerializer.h"

#include <tinyxml.h>
#include "Value.h"

namespace RedBox {
	TinyXMLSerializer::TinyXMLSerializer() : Serializer() {
	}

	TinyXMLSerializer::TinyXMLSerializer(const TinyXMLSerializer &src) :
		Serializer(src) {
	}

	TinyXMLSerializer::~TinyXMLSerializer() {
	}

	TinyXMLSerializer &TinyXMLSerializer::operator=(const TinyXMLSerializer &src) {
		return *this;
	}

	void TinyXMLSerializer::writeToStream(std::ostream &output,
	                                      const Value &value) {
	}

	bool TinyXMLSerializer::readFromStream(std::istream &input, Value &value) {
		return false;
	}
}
