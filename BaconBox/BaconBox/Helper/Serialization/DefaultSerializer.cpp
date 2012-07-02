#include "BaconBox/Helper/Serialization/DefaultSerializer.h"

#include <cassert>

#include "BaconBox/Helper/Serialization/Serializer.h"
#include "BaconBox/Helper/Serialization/JsonSerializer.h"
#include "BaconBox/Console.h"

namespace BaconBox {
	Serializer &DefaultSerializer::getDefaultSerializer() {
		assert(getInstance().defaultSerializer);
		return *getInstance().defaultSerializer;
	}

	void DefaultSerializer::setDefaultSerializer(Serializer *newDefaultSerializer) {
		DefaultSerializer &instance = getInstance();
		if (newDefaultSerializer) {
			assert(instance.defaultSerializer);
			delete instance.defaultSerializer;
			instance.defaultSerializer = newDefaultSerializer;
		} else {
			Console::println("Tried to set the default serializer to NULL.");
		}
	}

	DefaultSerializer &DefaultSerializer::getInstance() {
		static DefaultSerializer instance;
		return instance;
	}

	DefaultSerializer::DefaultSerializer() : defaultSerializer(new JsonSerializer()) {
	}

	DefaultSerializer::~DefaultSerializer() {
		assert(defaultSerializer);
		delete defaultSerializer;
	}
}
