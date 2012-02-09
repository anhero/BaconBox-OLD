#include "Tileset.h"

#include "TextureInformation.h"

namespace RedBox {
	const Vector2 Tileset::DEFAULT_TILE_SIZE = Vector2(32.0f, 32.0f);

	Tileset::Tileset() : Texturable(), TileMapEntity(),
		tileSize(DEFAULT_TILE_SIZE), tileSpacing(0.0f), margin(0.0f),
		tileOffset(), dirty(true), tileTextureCoordinates() {
	}

	Tileset::Tileset(TexturePointer newTexture,
	                 const std::string newName,
	                 const Vector2 &newTileSize,
	                 float newTileSpacing,
	                 float newMargin,
	                 const Vector2 &newTileOffset) : Texturable(newTexture),
		TileMapEntity(newName), tileSize(newTileSize),
		tileSpacing(newTileSpacing), margin(newMargin),
		tileOffset(newTileOffset), dirty(true), tileTextureCoordinates() {
	}

	Tileset::Tileset(const Tileset &src) : Texturable(src), TileMapEntity(src),
		tileSize(src.tileSize), tileSpacing(src.tileSpacing),
		margin(src.margin), tileOffset(src.tileOffset), dirty(false),
		tileTextureCoordinates() {
		if (src.dirty) {
			prepareTextureCoordinates();

		} else {
			tileTextureCoordinates = src.tileTextureCoordinates;
		}
	}

	Tileset::~Tileset() {
	}

	Tileset &Tileset::operator=(const Tileset &src) {
		this->Texturable::operator=(src);
		this->TileMapEntity::operator=(src);

		if (this != &src) {
			tileSize = src.tileSize;
			tileSpacing = src.tileSpacing;
			margin = src.margin;
			tileOffset = src.tileOffset;

			if (src.dirty) {
				prepareTextureCoordinates();

			} else {
				tileTextureCoordinates = src.tileTextureCoordinates;
				dirty = false;
			}
		}

		return *this;
	}

	void Tileset::setTextureInformation(TexturePointer newTexture) {
		this->Texturable::setTextureInformation(newTexture);
		dirty = true;
	}

	const Vector2 &Tileset::getTileSize() const {
		return tileSize;
	}

	void Tileset::setTileSize(const Vector2 &newTileSize) {
		tileSize = newTileSize;
		dirty = true;
	}

	void Tileset::setTileSize(float newTileWidth, float newTileHeight) {
		tileSize.setXY(newTileWidth, newTileHeight);
		dirty = true;
	}

	float Tileset::getTileWidth() const {
		return tileSize.getX();
	}

	void Tileset::setTileWidth(float newTileWidth) {
		tileSize.setX(newTileWidth);
		dirty = true;
	}

	float Tileset::getTileHeight() const {
		return tileSize.getY();
	}

	void Tileset::setTileHeight(float newTileHeight) {
		tileSize.setY(newTileHeight);
		dirty = true;
	}

	float Tileset::getTileSpacing() const {
		return tileSpacing;
	}

	void Tileset::setTileSpacing(float newTileSpacing) {
		tileSpacing = newTileSpacing;
		dirty = true;
	}

	float Tileset::getMargin() const {
		return margin;
	}

	void Tileset::setMargin(float newMargin) {
		margin = newMargin;
		dirty = true;
	}

	const Vector2 &Tileset::getTileOffset() const {
		return tileOffset;
	}

	void Tileset::setTileOffset(const Vector2 &newTileOffset) {
		tileOffset = newTileOffset;
		dirty = true;
	}

	void Tileset::setTileOffset(float newXTileOffset, float newYTileOffset) {
		tileOffset.setXY(newXTileOffset, newYTileOffset);
		dirty = true;
	}

	float Tileset::getXTileOffset() const {
		return tileOffset.getX();
	}

	void Tileset::setXTileOffset(float newXTileOffset) {
		tileOffset.setX(newXTileOffset);
		dirty = true;
	}

	float Tileset::getYTileOffset() const {
		return tileOffset.getY();
	}

	void Tileset::setYTileOffset(float newYTileOffset) {
		tileOffset.setY(newYTileOffset);
		dirty = true;
	}

	bool Tileset::loadTextureCoordinates(unsigned int tileId,
	                                     TextureCoordinates &textureCoordinates) {
		if (dirty) {
			prepareTextureCoordinates();
		}

		return loadTextureCoordinates(tileId, textureCoordinates);
	}

	bool Tileset::loadTextureCoordinates(unsigned int tileId,
	                                     TextureCoordinates &textureCoordinates) const {
		// We calculate the index of the tile in the vector of tile texture
		// coordinates.
		TileCoordinates::size_type index = tileId - firstTileId;

		// We make sure the tile set's texture coordinates are ready and that
		// the index of the tile is valid.
		bool result = !dirty && index < tileTextureCoordinates.size();

		if (result) {
			// We get the texture coordinates.
			textureCoordinates = tileTextureCoordinates[index];
		}

		return result;
	}

	void Tileset::prepareTextureCoordinates() {
		// We make sure we have a valid texture information.
		if (getTextureInformation()) {
			// We clear the current texture coordinates.
			tileTextureCoordinates.clear();

			// We calculate the upper left corner and lower right corner
			// to take into account the margin.
			Vector2 upperLeftCorner(margin / static_cast<float>(getTextureInformation()->poweredWidth),
			                        margin / static_cast<float>(getTextureInformation()->poweredHeight));
			Vector2 lowerRightCorner((static_cast<float>(getTextureInformation()->imageWidth) - margin) / static_cast<float>(getTextureInformation()->poweredWidth),
			                         (static_cast<float>(getTextureInformation()->imageHeight) - margin) / static_cast<float>(getTextureInformation()->poweredHeight));

			// We make sure the corners make sense.
			if (upperLeftCorner.getX() < lowerRightCorner.getX() &&
			    upperLeftCorner.getY() < lowerRightCorner.getY()) {

				float realTileSpacing = tileSpacing / static_cast<float>(getTextureInformation()->poweredWidth);

				Vector2 realOffset = upperLeftCorner;
				Vector2 realTileSize = tileSize / Vector2(static_cast<float>(getTextureInformation()->poweredWidth), static_cast<float>(getTextureInformation()->poweredHeight));

				// We make sure there is enough room for at least one tile...
				if (realOffset.getX() + realTileSize.getX() < lowerRightCorner.getX()) {
					while (realOffset.getY() + realTileSize.getY() < lowerRightCorner.getY()) {

						// We load the texture coordinates.
						tileTextureCoordinates.push_back(TextureCoordinates(4, realOffset));
						tileTextureCoordinates.back()[1].addToX(realTileSize.getX());
						tileTextureCoordinates.back()[2].addToY(realTileSize.getY());
						tileTextureCoordinates.back()[3].addToXY(realTileSize);

						// We increase the offset to the next tile's upper left
						// corner.
						realOffset.addToX(realTileSize.getX() + realTileSpacing);

						if (realOffset.getX() + realTileSize.getX() > lowerRightCorner.getX()) {
							realOffset.setX(upperLeftCorner.getX());
							realOffset.addToY(realTileSize.getY() + realTileSpacing);
						}
					}
				}
			}
		}
	}
}
