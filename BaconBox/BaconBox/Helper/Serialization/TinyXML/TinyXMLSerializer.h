#ifndef RB_TINY_XML_SERIALIZER_H
#define RB_TINY_XML_SERIALIZER_H

#include "BaconBox/Helper/Serialization/Serializer.h"

namespace BaconBox {
	class TinyXMLSerializer : public Serializer {
	public:
		/**
		 * Default constructor.
		 */
		TinyXMLSerializer();

		/**
		 * Copy constructor.
		 * @param src TinyXML serializer to make a copy of.
		 */
		TinyXMLSerializer(const TinyXMLSerializer &src);

		/**
		 * Destructor.
		 */
		~TinyXMLSerializer();

		/**
		 * Assignment operator overload.
		 * @param src TinyXML serializer to copy.
		 * @return Reference to the modified TinyXML serializer.
		 */
		TinyXMLSerializer &operator=(const TinyXMLSerializer &src);

		/**
		 * Writes the content of the value to a stream.
		 * @param output Output stream to output to.
		 * @param value Value to output in the stream.
		 */
		void writeToStream(std::ostream &output, const Value &value);

		/**
		 * Reads the content of a value from a stream.
		 * @param input Input stream to read the value from.
		 * @param value Value to read the data to.
		 * @return True on success, false on error.
		 */
		bool readFromStream(std::istream &input, Value &value);
	private:
	};
}

#endif
