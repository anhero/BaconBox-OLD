/**
 * @file
 * @ingroup Serialization
 */
#ifndef RB_SERIALIZER_H
#define RB_SERIALIZER_H

#include <iostream>

#include "Value.h"

namespace RedBox {
	/**
	 * Abstract base class for all formats of serializers.
	 * @ingroup Serialization
	 */
	class Serializer {
	public:
		/**
		 * Destructor.
		 */
		virtual ~Serializer();

		/**
		 * Writes the content of the value to a stream.
		 * @param output Output stream to output to.
		 * @param value Value to output in the stream.
		 */
		virtual void writeToStream(std::ostream &output, const Value &value) = 0;

		/**
		 * Reads the content of a value from a stream.
		 * @param input Input stream to read the value from.
		 * @param value Value to read the data to.
		 * @return True on success, false on error.
		 */
		virtual bool readFromStream(std::istream &input, Value &value) = 0;

		/**
		 * Writes the value to the console.
		 * @param value Value to output to the console.
		 */
		void writeToConsole(const Value &value);

		/**
		 * Writes the value to a file.
		 * @param filePath Path to the file to output the value.
		 * @param value Value to write to the file.
		 * @return True if the file opened correctly, false if not.
		 */
		bool writeToFile(const std::string &filePath, const Value &value);

		/**
		 * Reads the value from a file.
		 * @param filePath Path to the file to read the value from.
		 * @param value Value to read the data to.
		 * @return True on success, false if the file couldn't be opened or if
		 * there were errors in it.
		 */
		bool readFromFile(const std::string &filePath, Value &value);
	};
}

#endif
