#include "BaconBox/Display/Inanimate.h"

#include "BaconBox/Display/VertexArray.h"
#include "BaconBox/Display/FrameDetails.h"

namespace BaconBox {
	Inanimate::Inanimate(TexturePointer newTexture) :
		TextureMappable(newTexture), textureCoordinates() {
	}

	Inanimate::Inanimate(TexturePointer newTexture,
	                     const VertexArray &vertices, const Vector2 &offset) :
		TextureMappable(newTexture),
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

	TextureCoordinates &Inanimate::getTextureCoordinates() {
		return textureCoordinates;
	}

	void Inanimate::loadTextureCoordinates(const VertexArray &vertices,
	                                       const Vector2 &offset) {
		TextureMappable::loadTextureCoordinates(getTextureInformation(),
		                                        vertices, offset,
		                                        &textureCoordinates);
	}

	void Inanimate::loadTextureCoordinates(const BaconBox::VertexArray &vertices,
	                                       const BaconBox::FrameDetails &details) {
		TextureMappable::loadTextureCoordinates(getTextureInformation(),
		                                        vertices,
		                                        details,
		                                        &textureCoordinates);
	}

	void Inanimate::loadTextureCoordinates(TexturePointer newTexture,
	                                       const VertexArray &vertices,
	                                       const Vector2 &offset) {
		setTextureInformation(newTexture);
		loadTextureCoordinates(vertices, offset);
	}
}
