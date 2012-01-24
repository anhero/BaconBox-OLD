#include "TextureAtlas.h"

#include "TextureInformation.h"

namespace RedBox {
	TextureAtlas::TextureAtlas() : textureInformation(NULL),
		spriteDefinitions() {
	}

	TextureAtlas::TextureAtlas(TexturePointer newTexture) :
		textureInformation(newTexture.pointer), spriteDefinitions() {
	}

	TextureAtlas::TextureAtlas(const TextureAtlas &src) :
		textureInformation(src.textureInformation),
		spriteDefinitions(src.spriteDefinitions) {
	}

	TextureAtlas &TextureAtlas::operator=(const TextureAtlas &src) {
		if (this != &src) {
			textureInformation = src.textureInformation;
			spriteDefinitions = src.spriteDefinitions;
		}

		return *this;
	}

	TextureAtlas::SpriteMap::mapped_type &TextureAtlas::operator[](const TextureAtlas::SpriteMap::key_type &name) {
		return spriteDefinitions[name];
	}

	TextureAtlas::SpriteMap &TextureAtlas::getSpriteDefinitions() {
		return spriteDefinitions;
	}

	const TextureAtlas::SpriteMap &TextureAtlas::getSpriteDefinitions() const {
		return spriteDefinitions;
	}

	TextureInformation *TextureAtlas::getTextureInformation() const {
		return textureInformation;
	}

	void TextureAtlas::setTextureInformation(TexturePointer newTexture) {
		textureInformation = newTexture.pointer;
	}
}
