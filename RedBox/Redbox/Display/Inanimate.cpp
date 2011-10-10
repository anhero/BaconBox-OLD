#include "Inanimate.h"

#include "VerticesArray.h"

namespace RedBox {
	Inanimate::Inanimate() : TextureMappable(), textureCoordinates() {
	}

	Inanimate::Inanimate(const std::string &newTextureKey) :
		TextureMappable(newTextureKey), textureCoordinates() {
	}

	Inanimate::Inanimate(const TextureInformation *newTextureInformation) :
		TextureMappable(newTextureInformation), textureCoordinates() {
	}

	Inanimate::Inanimate(const std::string &newTextureKey,
	                     const VerticesArray &vertices, const Vector2 &offset) :
		TextureMappable(newTextureKey), textureCoordinates(vertices.getNbVertices()) {
		loadTextureCoordinates(vertices, offset);
	}

	Inanimate::Inanimate(const TextureInformation *newTextureInformation,
	                     const VerticesArray &vertices,
	                     const Vector2 &offset) :
		TextureMappable(newTextureInformation),
		textureCoordinates(vertices.getNbVertices()) {
		loadTextureCoordinates(vertices, offset);
	}

	Inanimate::Inanimate(const Inanimate &src) : TextureMappable(src),
		textureCoordinates(src.textureCoordinates) {
	}

	Inanimate::~Inanimate() {
	}

	Inanimate &Inanimate::operator=(const Inanimate &src) {
		this->TextureMappable::operator=(src);

		if (this != &src) {
			textureCoordinates = src.textureCoordinates;
		}

		return *this;
	}

	const TextureCoordinates &Inanimate::getCurrentTextureCoordinates() const {
		return textureCoordinates;
	}

	const TextureCoordinates &Inanimate::getTextureCoordinates() const {
		return textureCoordinates;
	}

	void Inanimate::loadTextureCoordinates(const VerticesArray &vertices, const Vector2 &offset) {
		TextureMappable::loadTextureCoordinates(getTextureInformation(),
		                                        vertices, offset,
		                                        &textureCoordinates);
	}

	void Inanimate::loadTextureCoordinates(const std::string &newTextureKey,
	                                       const VerticesArray &vertices,
	                                       const Vector2 &offset) {
		setTextureInformation(newTextureKey);
		loadTextureCoordinates(vertices, offset);
	}

	void Inanimate::loadTextureCoordinates(const TextureInformation *newTextureInformation,
	                                       const VerticesArray &vertices,
	                                       const Vector2 &offset) {
		setTextureInformation(newTextureInformation);
		loadTextureCoordinates(vertices, offset);
	}
}
