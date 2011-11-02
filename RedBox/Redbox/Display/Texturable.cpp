#include "Texturable.h"

namespace RedBox {
	Texturable::Texturable(TexturePointer newTexture) :
		textureInformation(newTexture.pointer) {
	}

	Texturable::Texturable(const Texturable &src) :
		textureInformation(src.textureInformation) {
	}

	Texturable::~Texturable() {
	}

	Texturable &Texturable::operator=(const Texturable &src) {
		if (this != &src) {
			textureInformation = src.textureInformation;
		}

		return *this;
	}

	TextureInformation *Texturable::getTextureInformation() const {
		return textureInformation;
	}

	void Texturable::setTextureInformation(TexturePointer newTexture) {
		textureInformation = newTexture.pointer;
	}
}
