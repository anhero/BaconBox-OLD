#include "TextureMappable.h"

#include "Console.h"
#include "Vector2.h"
#include "TextureCoordinates.h"
#include "VerticesArray.h"
#include "TextureInformation.h"

namespace RedBox {
	void TextureMappable::loadTextureCoordinates(TexturePointer texture,
	                                             const VerticesArray &vertices,
	                                             const Vector2 &offset,
	                                             TextureCoordinates *textureCoordinates) {
		// We make sure the texture coordinates container is valid.
		if (textureCoordinates) {
			// We make sure the texture information is valid.
			if (texture.pointer) {
				// We make sure the texture's size is valid.
				if (texture.pointer->imageWidth > 0u &&
				    texture.pointer->imageHeight > 0u &&
				    texture.pointer->poweredWidth > 0u &&
				    texture.pointer->poweredHeight > 0u) {
					// We make sure the offset is valid.
					if (offset.getX() >= 0.0f && offset.getY() >= 0.0f) {
						// We resize the texture coordinates container so it can
						// contain all the coordinates.
						textureCoordinates->resize(vertices.getNbVertices());
						// We calculate the real offset to use to map the
						// vertices on the texture.
						Vector2 realOffset = offset - vertices.getMinimumXY();

						// We get the powered size of the texture
						Vector2 poweredSize(static_cast<float>(texture.pointer->poweredWidth),
						                    static_cast<float>(texture.pointer->poweredHeight));

						VerticesArray::ConstIterator i = vertices.getBegin();
						TextureCoordinates::iterator i2 = textureCoordinates->begin();

						// We load all texture coordinates from the vertices.
						while (i != vertices.getEnd() && i2 != textureCoordinates->end()) {
							*i2 = (*i + realOffset) / poweredSize;
							++i;
							++i2;
						}

					} else {
						Console::println("Tried to load texture coordinates with a negative offset.");
						Console::printTrace();
					}

				} else {
					Console::println("Unable to load the texture coordinates because the texture to use has a size of (0, 0)");
					Console::printTrace();
				}

			} else {
				Console::println("Unable to load the texture coordinates because the given texture information is NULL.");
				Console::printTrace();
			}

		} else {
			Console::println("Unable to load the texture coordinates because the given texture coordinates container is NULL.");
			Console::printTrace();
		}
	}

	TextureMappable::TextureMappable() : Texturable() {
	}

	TextureMappable::TextureMappable(TexturePointer newTexture) :
		Texturable(newTexture) {
	}

	TextureMappable::TextureMappable(const TextureMappable &src) :
		Texturable(src) {
	}

	TextureMappable::~TextureMappable() {
	}

	TextureMappable &TextureMappable::operator=(const TextureMappable &src) {
		this->Texturable::operator=(src);
		return *this;
	}
}
