#include "TextureAtlas.h"

#include "TextureInformation.h"

namespace RedBox {
	TextureAtlas::TextureAtlas() : textureInformation(NULL), frameLists() {
	}

	TextureAtlas::TextureAtlas(TexturePointer newTexture) :
		textureInformation(newTexture.pointer), frameLists() {
	}

	TextureAtlas::TextureAtlas(const TextureAtlas &src) :
		textureInformation(src.textureInformation), frameLists(src.frameLists) {
	}

	TextureAtlas &TextureAtlas::operator=(const TextureAtlas &src) {
		if (this != &src) {
			textureInformation = src.textureInformation;
			frameLists = src.frameLists;
		}

		return *this;
	}

	TextureAtlas::FrameListMap::mapped_type &TextureAtlas::operator[](const TextureAtlas::FrameListMap::key_type &name) {
		return frameLists[name];
	}

	TextureAtlas::FrameListMap &TextureAtlas::getFrameLists() {
		return frameLists;
	}

	const TextureAtlas::FrameListMap &TextureAtlas::getFrameLists() const {
		return frameLists;
	}

	TextureInformation *TextureAtlas::getTextureInformation() const {
		return textureInformation;
	}

	void TextureAtlas::setTextureInformation(TexturePointer newTexture) {
		textureInformation = newTexture.pointer;
	}
}
