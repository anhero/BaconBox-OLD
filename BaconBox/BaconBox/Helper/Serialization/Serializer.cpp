#include "BaconBox/Helper/Serialization/Serializer.h"

#include <fstream>

#include "BaconBox/Console.h"
#include "BaconBox/Helper/Serialization/Value.h"

namespace BaconBox {
	Serializer::~Serializer() {
	}

	void Serializer::writeToConsole(const Value &value) {
		// We simply write the value to the cout stream.
		this->writeToStream(std::cout, value);
	}

	bool Serializer::writeToFile(const std::string &filePath,
	                             const Value &value) {
		std::ofstream outputFile;
		// We open the file.
		outputFile.open(filePath.c_str());

		// We make sure the file is open.
		if (outputFile.is_open()) {
			// We write the value to the stream.
			this->writeToStream(outputFile, value);

			// We close the file.
			outputFile.close();

			return true;

		} else {
			// If the file failed to open, we print an error message and we
			// return false.
			Console::print("Cannot open the file \"");
			Console::print(filePath);
			Console::println("\".");

			return false;
		}
	}

	bool Serializer::readFromFile(const std::string &filePath, Value &value) {
		std::ifstream inputFile;
		// We open the file.
		inputFile.open(filePath.c_str());

		// We make sure the file is open.
		if (inputFile.is_open()) {
			// We read the value from the stream and check if it succeeded or
			// not.
			bool result = this->readFromStream(inputFile, value);

			inputFile.close();

			return result;

		} else {
			// If the file failed to open, we print an error message and we
			// return false.
			Console::print("Cannot open the file \"");
			Console::print(filePath);
			Console::println("\".");

			return false;
		}
	}
}
