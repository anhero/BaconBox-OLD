/**
 * @file
 * @ingroup Serialization
 */
#ifndef RB_JSON_BOX_SERIALIZER_H
#define RB_JSON_BOX_SERIALIZER_H

#include "Serializer.h"

namespace BaconBox {
	/**
	 * Class used to serialize values to JSON or to deserialize from JSON.
	 * @see BaconBox::Value
	 * @see BaconBox::Serializable
	 * @ingroup Serialization
	 */
	class JsonBoxSerializer : public Serializer {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param newIndent Set this parameter to true if you want the output
		 * of the serializer to be indented. Set to true by default.
		 * @param newEscapeAll Set this parameter to true if you want the output
		 * to escape solidus ('/') characters in strings. Set to false by
		 * default
		 */
		explicit JsonBoxSerializer(bool newIndent = true, bool newEscapeSolidus = false);

		/**
		 * Copy constructor.
		 * @param src JSON serializer to make a copy of.
		 */
		JsonBoxSerializer(const JsonBoxSerializer &src);

		/**
		 * Destructor.
		 */
		~JsonBoxSerializer();

		/**
		 * Assignment operator overload.
		 * @param src JSON serializer to copy.
		 * @return Reference to the modified JSON serializer.
		 */
		JsonBoxSerializer &operator=(const JsonBoxSerializer &src);

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

		/**
		 * Checks whether or not the serializer indents the output.
		 * @return True if the output is indented, false if not.
		 * @see BaconBox::JsonBoxSerializer::indent
		 */
		bool isIndent() const;

		/**
		 * Sets whether or not the output is to be indented.
		 * @param newIndent Set this parameter to true to make the serializer
		 * output indented.
		 * @see BaconBox::JsonBoxSerializer::indent
		 */
		void setIndent(bool newIndent);

		/**
		 * Checks whether or not the serializer escapes the '/' character in
		 * strings when serializing.
		 * @return True if the '/' character is escaped in strings, false if
		 * not.
		 * @see BaconBox::JsonBoxSerializer::escapeSolidus
		 */
		bool isEscapeSolidus() const;

		/**
		 * Sets wether or not the '/' character is escaped when serializing
		 * string values.
		 * @param newEscapeSolidus Set this parameter to true to make the '/'
		 * character escaped when serializing string values.
		 */
		void setEscapeSolidus(bool newEscapeSolidus);
	private:
		/// True to indent the output, false to compress it.
		bool indent;

		/// True to escape the '/' character, false to let it be (in strings).
		bool escapeSolidus;
	};
}

#endif
