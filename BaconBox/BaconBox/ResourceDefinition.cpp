#include "BaconBox/ResourceDefinition.h"

#include "BaconBox/Helper/Serialization/Value.h"
#include "BaconBox/Helper/Serialization/DefaultSerializer.h"
#include "BaconBox/Helper/Serialization/Serializer.h"
#include "BaconBox/Helper/Serialization/Object.h"

namespace BaconBox {
	bool ResourceDefinition::isValidValue(const Value &node) {
		Object::const_iterator itKey = node.getObject().find("key");
		Object::const_iterator itFilePath = node.getObject().find("filePath");

		return itKey != node.getObject().end() &&
		       itFilePath != node.getObject().end() &&
		       itKey->second.isStringable() &&
		       itFilePath->second.isStringable();
	}

	ResourceDefinition::ResourceDefinition() : key(), filePath() {
	}

	ResourceDefinition::ResourceDefinition(const std::string &newKey,
	                                       const std::string &newFilePath) :
		key(newKey), filePath(newFilePath) {
	}

	ResourceDefinition::ResourceDefinition(const ResourceDefinition &src) :
		key(src.key), filePath(src.filePath) {
	}

	ResourceDefinition &ResourceDefinition::operator=(const ResourceDefinition &src) {
		if (this != &src) {
			key = src.key;
			filePath = src.filePath;
		}

		return *this;
	}

	void ResourceDefinition::serialize(Value &node, bool setName) const {
		if (setName) {
			node.setName("ResourceDefinition");
		}
		node["key"] = key;
		node["key"].setAttribute(true);
		node["filePath"] = filePath;
		node["filePath"].setAttribute(true);
	}

	bool ResourceDefinition::deserialize(const Value &node) {
		bool result = true;
		Object::const_iterator itKey = node.getObject().find("key");
		Object::const_iterator itFilePath = node.getObject().find("filePath");

		if (itKey != node.getObject().end() &&
		    itFilePath != node.getObject().end() &&
		    itKey->second.isStringable() &&
		    itFilePath->second.isStringable()) {
			key = itKey->second.getToString();
			filePath = itFilePath->second.getToString();

		} else {
			result = false;
		}

		return result;
	}

	std::ostream &operator<<(std::ostream &output, const ResourceDefinition &rd) {
		Value tmpValue;
		DefaultSerializer::serialize(rd, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}
}
