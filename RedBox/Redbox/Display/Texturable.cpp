#include "Texturable.h"

#include "ResourceManager.h"

namespace RedBox {
	Texturable::Texturable() : textureInformation(NULL) {
	}

	Texturable::Texturable(const std::string &newTextureKey) :
		textureInformation(ResourceManager::getTexture(newTextureKey)) {
	}

	Texturable::Texturable(const TextureInformation *newTextureInformation) :
		textureInformation(newTextureInformation) {
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

	const TextureInformation *Texturable::getTextureInformation() const {
		return textureInformation;
	}

	void Texturable::setTextureInformation(const std::string &newTextureKey) {
		textureInformation = ResourceManager::getTexture(newTextureKey);
	}

	void Texturable::setTextureInformation(const TextureInformation *newTextureInformation) {
		textureInformation = newTextureInformation;
	}
}
