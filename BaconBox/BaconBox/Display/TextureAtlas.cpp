#include "BaconBox/Display/TextureAtlas.h"

#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/Helper/Serialization/Value.h"
#include "BaconBox/Helper/Serialization/DefaultSerializer.h"
#include "BaconBox/Helper/Serialization/Serializer.h"
#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/ResourceManager.h"

namespace BaconBox {
	bool TextureAtlas::isValidValue(const Value &node) {
		bool result = true;
		const Object &tmpObject = node.getObject();
		Object::const_iterator itTextureDefinition = tmpObject.find("textureDefinition");
		Object::const_iterator itSpriteDefinitions = tmpObject.find("spriteDefinitions");

		// We make sure we found the members and that the texture definition is
		// valid.
		if (itTextureDefinition != tmpObject.end() &&
		    itSpriteDefinitions != tmpObject.end() &&
		    TextureDefinition::isValidValue(itTextureDefinition->second)) {

			// We make sure the sprites definitions are valid.
			const Object &tmpSpriteDefinitions = itSpriteDefinitions->second.getObject();
			Object::const_iterator i = tmpSpriteDefinitions.begin();

			while (result && i != tmpSpriteDefinitions.end()) {
				if (SpriteMap::mapped_type::isValidValue(i->second)) {
					++i;

				} else {
					result = false;
				}
			}

		} else {
			result = false;
		}

		return result;
	}

	TextureAtlas::TextureAtlas() : textureDefinition(), spriteDefinitions() {
	}

	TextureAtlas::TextureAtlas(const TextureDefinition &newTextureDefinition) :
		textureDefinition(newTextureDefinition), spriteDefinitions() {
	}

	TextureAtlas::TextureAtlas(const TextureAtlas &src) :
		textureDefinition(src.textureDefinition),
		spriteDefinitions(src.spriteDefinitions) {
	}

	TextureAtlas &TextureAtlas::operator=(const TextureAtlas &src) {
		if (this != &src) {
			textureDefinition = src.textureDefinition;
			spriteDefinitions = src.spriteDefinitions;
		}

		return *this;
	}

	TextureAtlas::SpriteMap::mapped_type &TextureAtlas::operator[](const TextureAtlas::SpriteMap::key_type &name) {
		return spriteDefinitions[name];
	}

	TextureInformation *TextureAtlas::getTextureInformation() const {
		return ResourceManager::loadTextureRelativePath(textureDefinition.key, textureDefinition.filePath);
	}

	void TextureAtlas::serialize(Value &node, bool setName) const {
		if (setName) {
			node.setName("TextureAtlas");
		}
		DefaultSerializer::serialize(textureDefinition, node["textureDefinition"], false);
		Value &tmpSpriteDefinitions = node["spriteDefinitions"];

		for (SpriteMap::const_iterator i = spriteDefinitions.begin();
		     i != spriteDefinitions.end(); ++i) {
			DefaultSerializer::serialize(i->second, tmpSpriteDefinitions[i->first], false);
		}
	}

	bool TextureAtlas::deserialize(const Value &node) {
		bool result = true;
		const Object &tmpObject = node.getObject();
		Object::const_iterator itTextureDefinition = tmpObject.find("textureDefinition");
		Object::const_iterator itSpriteDefinitions = tmpObject.find("spriteDefinitions");

		// We make sure we found the members and that the texture definition is
		// valid.
		if (itTextureDefinition != tmpObject.end() &&
		    itSpriteDefinitions != tmpObject.end()) {

			// We make sure the sprites definitions are valid.
			const Object &tmpSpriteDefinitions = itSpriteDefinitions->second.getObject();
			Object::const_iterator i = tmpSpriteDefinitions.begin();

			while (result && i != tmpSpriteDefinitions.end()) {
				if (SpriteMap::mapped_type::isValidValue(i->second)) {
					++i;

				} else {
					result = false;
				}
			}

			if (result) {
				if (DefaultSerializer::deserialize(itTextureDefinition->second, textureDefinition)) {
					spriteDefinitions.clear();
					i = tmpSpriteDefinitions.begin();

					while (result && i != tmpSpriteDefinitions.end()) {
						if (DefaultSerializer::deserialize(i->second, spriteDefinitions[i->first])) {
							++i;

						} else {
							result = false;
						}
					}

				} else {
					result = false;
				}
			}

		} else {
			result = false;
		}

		return result;
	}

	std::ostream &operator<<(std::ostream &output, const TextureAtlas &ta) {
		Value tmpValue;
		DefaultSerializer::serialize(ta, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}
}
